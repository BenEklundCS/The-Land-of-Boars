# Visual debug harness for The Land of Boars.
# Launches the game, optionally drives input, captures PNG frames, then exits.
#
# Usage:
#   .\capture.ps1 -Script "wait:3000,key:RIGHT:1200,shot:move,key:SPACE:200,shot:jump"
#
# Script steps (comma separated):
#   wait:<ms>              sleep
#   shot:<name>            capture a PNG frame
#   key:<KEY>:<holdMs>     hold a key down for holdMs, then release
#   tap:<KEY>              quick press+release
param(
    [string]$Script  = "wait:4000,shot:boot",
    [string]$OutDir  = "$PSScriptRoot\frames",
    [int]$BootWaitMs = 4000,
    [string]$LogPath = ""   # capture the game's TraceLog output to a file
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W {
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
    [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern uint MapVirtualKey(uint uCode, uint uMapType);
    [DllImport("user32.dll")] public static extern bool MoveWindow(IntPtr h, int x, int y, int w, int ht, bool repaint);
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int cx, int cy, uint flags);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, IntPtr pid);
    [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
    [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
    [DllImport("user32.dll")] public static extern void mouse_event(uint flags, uint dx, uint dy, uint data, UIntPtr extra);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@

# Virtual-key codes for the keys this game uses.
$VK = @{
    "LEFT" = 0x25; "UP" = 0x26; "RIGHT" = 0x27; "DOWN" = 0x28
    "SPACE" = 0x20; "A" = 0x41; "D" = 0x44; "W" = 0x57; "S" = 0x53
    "ESC" = 0x1B; "ENTER" = 0x0D; "F1" = 0x70; "TAB" = 0x09
}
$KEYUP = 0x0002
$EXTENDED = 0x0001
# Arrow keys, navigation keys and right-hand modifiers are "extended" keys.
# Without KEYEVENTF_EXTENDEDKEY their scancodes resolve to the numpad
# equivalents, so the game never sees KEY_LEFT/KEY_RIGHT at all and any
# movement test silently does nothing.
$EXTENDED_KEYS = @("LEFT", "UP", "RIGHT", "DOWN", "INS", "DEL", "HOME", "END", "PGUP", "PGDN")

function Send-Key([string]$name, [bool]$up) {
    $code = $VK[$name.ToUpper()]
    $flags = 0
    if ($EXTENDED_KEYS -contains $name.ToUpper()) { $flags = $flags -bor $EXTENDED }
    if ($up) { $flags = $flags -bor $KEYUP }
    # A real scancode is REQUIRED. raylib sits on GLFW, which resolves keys from
    # the scancode in the window message, not the virtual-key code. Passing
    # bScan=0 makes GLFW report GLFW_KEY_UNKNOWN and the game sees nothing at
    # all - input appears to be sent successfully while doing nothing.
    $scan = [W]::MapVirtualKey([uint32]$code, 0)  # MAPVK_VK_TO_VSC
    [W]::keybd_event($code, [byte]$scan, $flags, [UIntPtr]::Zero)
}

# Must run before any window/cursor coordinate work, otherwise Windows
# virtualizes our coords and clicks land in the wrong place on scaled displays.
[void][W]::SetProcessDPIAware()

$repo = "C:\Users\luke4\CLionProjects\The Land of Boars\The-Land-of-Boars"
$exe  = "$repo\cmake-build-debug\The_Land_of_Boars.exe"
if (-not (Test-Path $exe)) { throw "Executable not found: $exe" }
if (-not (Test-Path $OutDir)) { New-Item -ItemType Directory -Path $OutDir | Out-Null }

# Run from cmake-build-debug so the game's relative "../Levels/..." paths resolve.
$startArgs = @{ FilePath = $exe; WorkingDirectory = "$repo\cmake-build-debug"; PassThru = $true }
if ($LogPath) {
    $startArgs.RedirectStandardOutput = $LogPath
    $startArgs.RedirectStandardError  = "$LogPath.err"
}
$proc = Start-Process @startArgs
Write-Output "launched pid=$($proc.Id)"
Start-Sleep -Milliseconds $BootWaitMs

$proc.Refresh()
if ($proc.HasExited) { throw "Game exited immediately with code $($proc.ExitCode) - it crashed on startup." }

$h = $proc.MainWindowHandle
if ($h -eq [IntPtr]::Zero) { throw "No window handle - game window never appeared." }
[void][W]::ShowWindow($h, 9)   # SW_RESTORE
# The game creates a window larger than the display, anchored off-screen at a
# negative origin. Pin it to (0,0) so bitmap coords == screen coords.
$r0 = New-Object W+RECT
[void][W]::GetWindowRect($h, [ref]$r0)
Write-Output "window rect before move: ($($r0.L),$($r0.T)) $($r0.R-$r0.L)x$($r0.B-$r0.T)"
[void][W]::MoveWindow($h, 0, 0, ($r0.R-$r0.L), ($r0.B-$r0.T), $true)
Start-Sleep -Milliseconds 600
[void][W]::GetWindowRect($h, [ref]$r0)
Write-Output "window rect after move:  ($($r0.L),$($r0.T)) $($r0.R-$r0.L)x$($r0.B-$r0.T)"

# SetForegroundWindow alone is unreliable from a background process (Windows
# foreground lock), and CopyFromScreen grabs whatever is on top - so without
# this we photograph the IDE instead of the game. Pin topmost AND steal focus
# by attaching to the current foreground thread's input queue.
function ForceFront {
    [void][W]::SetWindowPos($h, [IntPtr](-1), 0, 0, 0, 0, 0x0043)  # HWND_TOPMOST | NOSIZE|NOMOVE|SHOWWINDOW
    $fg = [W]::GetForegroundWindow()
    $tidFg = [W]::GetWindowThreadProcessId($fg, [IntPtr]::Zero)
    $tidMe = [W]::GetCurrentThreadId()
    [void][W]::AttachThreadInput($tidMe, $tidFg, $true)
    [void][W]::BringWindowToTop($h)
    [void][W]::SetForegroundWindow($h)
    [void][W]::AttachThreadInput($tidMe, $tidFg, $false)
    Start-Sleep -Milliseconds 150
}

function Grab([string]$name) {
    ForceFront
    $r = New-Object W+RECT
    [void][W]::GetWindowRect($h, [ref]$r)
    $w = $r.R - $r.L; $ht = $r.B - $r.T
    if ($w -le 0 -or $ht -le 0) { Write-Output "  !! bad window rect for $name"; return }
    $bmp = New-Object System.Drawing.Bitmap $w, $ht
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($r.L, $r.T, 0, 0, $bmp.Size)
    $path = Join-Path $OutDir "$name.png"
    $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
    Write-Output "  shot -> $path"
}

ForceFront

foreach ($step in $Script.Split(",")) {
    $parts = $step.Trim().Split(":")
    # Input only reaches the game if it genuinely holds focus; without this the
    # click/key silently goes to whatever window Windows thinks is active.
    if ($parts[0].ToLower() -in @("click","key","tap","move")) { ForceFront }
    switch ($parts[0].ToLower()) {
        "wait" { Start-Sleep -Milliseconds ([int]$parts[1]) }
        "shot" { Grab $parts[1] }
        "move" {
            $r = New-Object W+RECT
            [void][W]::GetWindowRect($h, [ref]$r)
            [void][W]::SetCursorPos(($r.L + [int]$parts[1]), ($r.T + [int]$parts[2]))
            Write-Output "  cursor -> window($($parts[1]),$($parts[2]))"
        }
        "click" {
            # coords are relative to the captured window bitmap
            $r = New-Object W+RECT
            [void][W]::GetWindowRect($h, [ref]$r)
            $sx = $r.L + [int]$parts[1]; $sy = $r.T + [int]$parts[2]
            [void][W]::SetCursorPos($sx, $sy)
            Start-Sleep -Milliseconds 250
            [W]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero)  # LEFTDOWN
            Start-Sleep -Milliseconds 90
            [W]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero)  # LEFTUP
            Write-Output "  click at window($($parts[1]),$($parts[2])) screen($sx,$sy)"
        }
        "tap" {
            Send-Key $parts[1] $false
            Start-Sleep -Milliseconds 60
            Send-Key $parts[1] $true
            Write-Output "  tap $($parts[1])"
        }
        "key" {
            $hold = [int]$parts[2]
            $fg = [W]::GetForegroundWindow()
            Write-Output ("  [focus check] game hwnd={0} foreground={1} match={2}" -f $h, $fg, ($fg -eq $h))
            Send-Key $parts[1] $false
            Start-Sleep -Milliseconds $hold
            Send-Key $parts[1] $true
            Write-Output "  held $($parts[1]) for ${hold}ms"
        }
    }
}

Start-Sleep -Milliseconds 300
if (-not $proc.HasExited) { $proc.Kill(); Write-Output "game closed" }
