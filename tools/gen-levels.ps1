# Generates the tilemaps for levels 2 and 3 and reports their geometry.
#
# Level files are a grid of digits: 0 = empty, 1 = dirt, 2 = grass.
# World position of a tile is (col * STEP, row * STEP) with STEP = 74.
#
# The point of generating rather than hand-editing is that the script also
# prints the surface height at any column, so entity and goal placement can be
# derived from the geometry instead of guessed.

$ErrorActionPreference = "Stop"

$STEP = 74
# Deep enough that the solid bounds exceed the camera's ~1440-unit viewport.
# If the level is shorter than the view the camera centres on it instead of
# following the player, which frames the player high with dead dirt below.
$ROWS = 60
$COLS = 150

function New-Grid {
    $grid = @()
    for ($r = 0; $r -lt $ROWS; $r++) { $grid += ,(@('0') * $COLS) }
    return $grid
}

# Fill a column from surfaceRow down to the bottom: grass on top, dirt beneath.
function Set-Ground([array]$grid, [int]$col, [int]$surfaceRow) {
    for ($r = $surfaceRow; $r -lt $ROWS; $r++) {
        $grid[$r][$col] = if ($r -eq $surfaceRow) { '2' } else { '1' }
    }
}

function Set-Platform([array]$grid, [int]$col, [int]$row, [int]$width) {
    for ($c = $col; $c -lt [math]::Min($col + $width, $COLS); $c++) {
        $grid[$row][$c] = '2'
    }
}

function Save-Grid([array]$grid, [string]$path) {
    $lines = $grid | ForEach-Object { ($_ -join '') }
    # Match the existing level file, which opens with a blank line.
    Set-Content -Path $path -Value (@('') + $lines) -Encoding ascii
    Write-Output "wrote $path"
}

# ---------------------------------------------------------------- level two
# "The Gauntlet" - flat run broken by pits, with platforms to cross them.
$two = New-Grid
$surface = 24
$pits = @(@(28,5), @(48,6), @(70,5), @(92,7), @(115,5))

for ($c = 0; $c -lt $COLS; $c++) {
    $inPit = $false
    foreach ($p in $pits) { if ($c -ge $p[0] -and $c -lt ($p[0] + $p[1])) { $inPit = $true } }
    if (-not $inPit) { Set-Ground $two $c $surface }
}
# A platform hanging over each pit so every gap is crossable.
foreach ($p in $pits) {
    Set-Platform $two ($p[0] + 1) ($surface - 4) ([math]::Max($p[1] - 2, 2))
}
Save-Grid $two (Join-Path $PSScriptRoot "..\Levels\map_level_two.txt")

# -------------------------------------------------------------- level three
# "The Ascent" - a staircase climbing from the start to a high finish.
$three = New-Grid
$stepWidth = 9
for ($c = 0; $c -lt $COLS; $c++) {
    # NOTE: not $step - PowerShell variable names are case-insensitive, so that
    # would silently overwrite the global $STEP.
    $stepIndex = [math]::Floor($c / $stepWidth)
    $row = 30 - $stepIndex
    if ($row -lt 10) { $row = 10 }   # flatten out at the top
    Set-Ground $three $c $row
}
Save-Grid $three (Join-Path $PSScriptRoot "..\Levels\map_level_three.txt")

# ------------------------------------------------------------------ report
function Get-SurfaceRow([array]$grid, [int]$col) {
    for ($r = 0; $r -lt $ROWS; $r++) { if ($grid[$r][$col] -ne '0') { return $r } }
    return -1
}

Write-Output ""
Write-Output "STEP=$STEP  ROWS=$ROWS  COLS=$COLS   (world width $($COLS*$STEP), height $($ROWS*$STEP))"
foreach ($pair in @(@('two',$two), @('three',$three))) {
    $name = $pair[0]; $g = $pair[1]
    Write-Output ""
    Write-Output "--- level $name surface profile ---"
    foreach ($c in @(2, 10, 40, 75, 110, 140, 148)) {
        $r = Get-SurfaceRow $g $c
        if ($r -ge 0) {
            Write-Output ("  col {0,3} (x {1,6}) -> surface row {2,2} (y {3,5})" -f $c, ($c*$STEP), $r, ($r*$STEP))
        } else {
            Write-Output ("  col {0,3} (x {1,6}) -> NO GROUND (pit)" -f $c, ($c*$STEP))
        }
    }
    $endCol = 145
    $endRow = Get-SurfaceRow $g $endCol
    Write-Output ("  suggested goal: x {0}  y {1}  (sits on surface at col {2})" -f ($endCol*$STEP), (($endRow*$STEP) - 380), $endCol)
}
