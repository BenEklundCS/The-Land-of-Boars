# Deterministic spawn/geometry analysis.
#
# Reproduces the engine's tile placement math exactly, from the same constants
# the C++ uses, and reports where the player spawn lands relative to the tile
# grid. No need to run the game.
#
#   TextureManager.h : TILE_LENGTH 80
#   TileManager.cpp  : tileX = col * (TILE_LENGTH - 6)   <- overlap 6
#                      tileY = row * (TILE_LENGTH - 6)
#   Tile.cpp:21      : Scale()  -> position *= WINDOW_SCALE_FACTOR
#   Globals.h        : BASE 2560x1440
#   LevelOne.cpp:28  : player->SetPosition({1500, 1500})  <- raw, NOT scaled
#                      (SetPosition is a plain assignment and runs *after* the
#                       Player ctor already called Scale())

$ErrorActionPreference = "Stop"

$TILE_LENGTH = 80
$OVERLAP     = 6
$STEP        = $TILE_LENGTH - $OVERLAP   # 74
$BASE_W      = 2560
$BASE_H      = 1440
$SPAWN       = @{ x = 1500.0; y = 1500.0 }

$levelPath = Join-Path $PSScriptRoot "..\Levels\map_level_one.txt"
$lines = Get-Content $levelPath

Write-Output "Level: $((Resolve-Path $levelPath).Path)"
Write-Output "Rows: $($lines.Count)   (row 0 is an empty line -> empty tile row)"
Write-Output "Player spawn (raw, unscaled): ($($SPAWN.x), $($SPAWN.y))"
Write-Output ""

function Analyze([int]$winW, [int]$winH, [bool]$scaleSpawn = $false) {
    $fx = $winW / $BASE_W
    $fy = $winH / $BASE_H
    $stepX = $STEP * $fx
    $stepY = $STEP * $fy

    # Proposed fix: scale the spawn like every other positioned object.
    $SPAWN = if ($scaleSpawn) { @{ x = 1500.0*$fx; y = 1500.0*$fy } } else { $SPAWN }

    Write-Output "=============================================================="
    $tag = if ($scaleSpawn) { "  [WITH SCALED SPAWN FIX]" } else { "" }
    Write-Output " Window ${winW}x${winH}   scale = $([math]::Round($fx,4)) x, $([math]::Round($fy,4)) y$tag"
    Write-Output ("  spawn used: ({0:N1}, {1:N1})" -f $SPAWN.x, $SPAWN.y)
    Write-Output "=============================================================="
    Write-Output ("  tile step in world units: {0:N2} x, {1:N2} y" -f $stepX, $stepY)

    # Full extent of the tile grid in world space
    $maxCols = ($lines | ForEach-Object { $_.Length } | Measure-Object -Maximum).Maximum
    Write-Output ("  tile grid extent: x 0 .. {0:N0}   y 0 .. {1:N0}" -f ($maxCols*$stepX), ($lines.Count*$stepY))

    # Which cell does the spawn point fall in?
    $col = [math]::Floor($SPAWN.x / $stepX)
    $row = [math]::Floor($SPAWN.y / $stepY)
    Write-Output ("  spawn maps to grid cell: col {0}, row {1}" -f $col, $row)

    if ($row -lt 0 -or $row -ge $lines.Count) {
        Write-Output "  -> spawn row is OUTSIDE the grid vertically"
        Write-Output ""
        return
    }

    $rowStr = $lines[$row]
    $cellCh = if ($col -ge 0 -and $col -lt $rowStr.Length) { $rowStr[$col] } else { '0' }
    $cellDesc = switch ("$cellCh") { "0" { "EMPTY" } "1" { "DIRT (solid)" } "2" { "GRASS (solid)" } default { "type $cellCh" } }
    Write-Output "  cell at spawn: '$cellCh' = $cellDesc"

    # Walk down this column to find the first solid tile beneath the spawn.
    $floorRow = $null
    for ($r = [math]::Max($row,0); $r -lt $lines.Count; $r++) {
        $s = $lines[$r]
        if ($col -lt $s.Length -and $s[$col] -ne '0') { $floorRow = $r; break }
    }

    if ($null -eq $floorRow) {
        Write-Output "  -> NO SOLID TILE anywhere below the spawn in column $col"
        Write-Output "  -> player falls forever (matches observed velocity growth)"
    } else {
        $floorY = $floorRow * $stepY
        Write-Output ("  first solid tile below spawn: row {0}  (world y = {1:N1})" -f $floorRow, $floorY)
        if ($floorY -lt $SPAWN.y) {
            Write-Output ("  -> that surface is ABOVE the spawn ({0:N1} < {1:N1}) - player is BELOW the floor" -f $floorY, $SPAWN.y)
        } else {
            Write-Output ("  -> player would land on it after falling {0:N1} units" -f ($floorY - $SPAWN.y))
        }
    }

    # Where IS the solid ground in this row band, horizontally?
    $solidCols = @()
    if ($row -lt $lines.Count) {
        $s = $lines[$row]
        for ($c = 0; $c -lt $s.Length; $c++) { if ($s[$c] -ne '0') { $solidCols += $c } }
    }
    if ($solidCols.Count -gt 0) {
        $minC = ($solidCols | Measure-Object -Minimum).Minimum
        $maxC = ($solidCols | Measure-Object -Maximum).Maximum
        Write-Output ("  solid span on spawn row {0}: cols {1}..{2}  (world x {3:N0} .. {4:N0})" -f $row, $minC, $maxC, ($minC*$stepX), ($maxC*$stepX))
    } else {
        Write-Output "  spawn row $row has no solid tiles at all"
    }
    Write-Output ""
}

Analyze 2560 1440     # the base resolution everything was tuned for
Analyze 1200 700      # the size we are actually running - currently broken
Analyze 1200 700 $true   # same size, with the spawn scaled like everything else
Analyze 1920 1080 $true  # and a third resolution, to prove it generalizes
