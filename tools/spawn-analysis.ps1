# Deterministic spawn/geometry analysis.
#
# Reproduces the engine's tile placement math from the same constants the C++
# uses, and reports where the player spawn lands relative to the tile grid.
# No need to build or run the game.
#
#   TextureManager.h : TILE_LENGTH 80
#   TileManager.cpp  : tileX = col * (TILE_LENGTH - 6)   <- overlap 6
#   LevelOne.cpp     : player->SetPosition({1500, 1500})
#
# World data is resolution-independent: positions and dimensions are in fixed
# world units and are never scaled by the window. Resolution is handled purely
# by Camera2D::zoom. So this analysis has no window-size input at all - and that
# is the point. If a future change reintroduces resolution-dependent world
# coordinates, this script's assumptions break and the answer stops matching
# the game's own [LEVEL]/[TILES] log output.

$ErrorActionPreference = "Stop"

$TILE_LENGTH = 80
$OVERLAP     = 6
$STEP        = $TILE_LENGTH - $OVERLAP   # 74 world units
$SPAWN       = @{ x = 1500.0; y = 1500.0 }

$levelPath = Join-Path $PSScriptRoot "..\Levels\map_level_one.txt"
$lines = Get-Content $levelPath

Write-Output "Level: $((Resolve-Path $levelPath).Path)"
Write-Output "Rows: $($lines.Count)   (row 0 is an empty line -> empty tile row)"
Write-Output "Tile step: $STEP world units (TILE_LENGTH $TILE_LENGTH - overlap $OVERLAP)"
Write-Output "Player spawn: ($($SPAWN.x), $($SPAWN.y)) world units"
Write-Output ""

$maxCols = ($lines | ForEach-Object { $_.Length } | Measure-Object -Maximum).Maximum
Write-Output ("Tile grid extent: x 0 .. {0:N0}   y 0 .. {1:N0}" -f ($maxCols*$STEP), ($lines.Count*$STEP))

$col = [math]::Floor($SPAWN.x / $STEP)
$row = [math]::Floor($SPAWN.y / $STEP)
Write-Output "Spawn maps to grid cell: col $col, row $row"

$rowStr  = $lines[$row]
$cellCh  = if ($col -lt $rowStr.Length) { $rowStr[$col] } else { '0' }
$cellDesc = switch ("$cellCh") { "0" { "EMPTY" } "1" { "DIRT (solid)" } "2" { "GRASS (solid)" } default { "type $cellCh" } }
Write-Output "Cell at spawn: '$cellCh' = $cellDesc"

$floorRow = $null
for ($r = $row; $r -lt $lines.Count; $r++) {
    $s = $lines[$r]
    if ($col -lt $s.Length -and $s[$col] -ne '0') { $floorRow = $r; break }
}

if ($null -eq $floorRow) {
    Write-Output "RESULT: no solid tile below spawn in column $col - player would fall forever"
    exit 1
}

$floorY = $floorRow * $STEP
Write-Output ("First solid tile below spawn: row {0} (world y = {1:N1})" -f $floorRow, $floorY)
Write-Output ("RESULT: player lands after falling {0:N1} world units" -f ($floorY - $SPAWN.y))
Write-Output ""
Write-Output "Cross-check against the running game - these must agree:"
Write-Output '  Select-String -Path $env:TEMP\lob-run.log -Pattern "\[LEVEL\]|\[TILES\]"'
