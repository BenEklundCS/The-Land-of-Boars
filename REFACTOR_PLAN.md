# The Land of Boars — Refactor Plan

Working doc. Append findings, tick boxes as things land. Phases are ordered but
not rigid; the point is to always know what's done and what's next.

---

## Hard constraints

- **NOTHING gets pushed to GitHub.** Local branches and local commits are fine.
  No `git push`, no remote branch deletes, no PRs — unless explicitly asked.
- `master` on GitHub is clean and matches local `master`. The ECS work only ever
  lived on `engine_architecture_refactor`. **The revert required zero remote
  action**, and there is nothing on the remote that needs undoing.

---

## Status at a glance

| Phase | What | State |
|---|---|---|
| 0 | Stabilize the baseline so it builds and runs | ✅ done |
| 1 | Revert the AI refactor | ✅ done |
| 2 | Spec the refactor — what do I want and why | ⬜ not started |
| 3 | Characterization tests on the stable seam | ⬜ not started |
| 4 | Port to the new architecture, keep tests green | ⬜ not started |
| 5 | Build 3 levels | ⬜ blocked — see Phase 5 |

---

## Phase 0 — Stabilize the baseline ✅

Goal: `master` builds, runs, and is observable. Prerequisite for everything else.

- [x] Preserve the uncommitted ECS work (`AttackSystem`/`CombatSystem`, ~388
      lines) as a local commit on `engine_architecture_refactor` — it existed
      nowhere in git and any checkout would have destroyed it
- [x] Confirm `build/` (331 MB) stays out of any commit
- [x] Fix the dependency drift that broke the build (see Findings #1)
- [x] Build `master` clean
- [x] Stand up visual debugging — launch, drive input, capture frames
- [x] Restore the usable window size (see Findings #2)
- [x] Fix the player spawn desync that the window change exposed (Findings #5)
- [x] Add discrete geometry logging + static analysis tooling (Findings #5/#6)
- [x] Confirm attack works on master (Findings #3)
- [ ] Add a `.gitignore` for `build/` and `cmake-build-debug/` — there is none,
      which is why a 331 MB dir shows up as untracked

## Phase 1 — Revert the refactor ✅

The ECS work was mid-progress AI output with no human review. Reverting it.

- [x] Snapshot the loose work locally so nothing is lost
- [x] Switch to `master` (`88237d0`), working tree clean
- [x] Confirm the refactor remains fully recoverable on its branch

**Not a destructive revert.** Nothing was deleted. The refactor sits on
`engine_architecture_refactor` and can be read, diffed, or cherry-picked from
forever. "Revert" here just meant "go back to `master`".

### Worth cherry-picking from the refactor

Not all of it is slop — a couple of changes were deliberate fixes to real
problems:

- [x] `Window.h` — window size `2560x1440` → `1200x700`. **Applied to master.**
      2560x1440 is larger than a 1920x1080 display, so the window hung off-screen
- [ ] Review `CombatSystem.cpp` / `AttackSystem.cpp` for salvageable design
      before writing attack code from scratch in Phase 4

## Phase 2 — Spec the refactor ⬜

The single highest-value phase, and the one the original attempt skipped. The
existing ECS work has no stated "why" anywhere in the repo or commit messages.

- [ ] Write down what the refactor is actually *for*. Concretely: what can I
      build after it that I can't build now?
- [ ] Answer honestly whether ECS earns its place. A single-player platformer
      with ~4 monster types is squarely in the range where OOP is fine. If the
      answer is "no concrete benefit", **staying on `master` is a legitimate
      outcome of this phase**
- [ ] Let the goal pick the architecture, not the reverse. Phase 5 (three levels)
      is the real goal — scope the refactor to exactly what that needs
- [ ] Decide the scope cut and write it here before touching code

## Phase 3 — Characterization tests ⬜

Note the trap this phase has to avoid: `master`'s behavior lives in
`Player`/`GameObject`, which the refactor **deletes**. Tests written against
that API cannot port — they'd get rewritten against the ECS and would then just
assert whatever the new code already does. They'd feel like a safety net while
catching nothing.

So: **test the stable seam** — things true on both sides of the refactor.

- [ ] Stand up test infra — there is none today (no `tests/`, no Catch2, no
      CTest entry in `CMakeLists.txt`)
- [ ] `LevelLoader` round-trip: `Load → Save → Load` is identity. Zero raylib
      dependency, and it guards the format Phase 5 depends on
- [ ] Pure math / physics: gravity integration, AABB collision resolution
- [ ] **Golden-run harness** — fixed timestep, scripted input, dump player
      position/health every N frames, diff against a recorded baseline. Highest
      value-per-effort test for a game, and it survives the port because it only
      observes behavior, never the API

Deliberately **out of scope**: unit tests on `Player`, anything asserting on
"feel" (jump arcs, animation timing), coverage targets. Days of work, not weeks.

Coupling to work around: 37 `GetInstance()` calls and 58 raylib
texture/draw/`GetFrameTime()` calls inside `src/Game/`. Getting a headless test
binary to link is real work before the first assertion.

## Phase 4 — Port ⬜

- [ ] Port to the reduced spec from Phase 2
- [ ] Golden run stays green throughout
- [ ] Verify attack works (regression that motivated the revert — see Findings #3)

## Phase 5 — Three levels ⬜

**Blocked, and the constraint as originally stated is impossible.** "Three full
levels using existing mechanics, before any new code" cannot happen:

- `Levels/*.txt` stores **tiles only** — a grid of digits, one char per tile
  (`LevelLoader.cpp:30`)
- Every monster, coin, tree, platform, and the player spawn is **hardcoded C++**
  in `LevelOne.cpp:56-70`
- `Engine.cpp:27` hardcodes `LevelOne` as the only level. No level select, no
  transitions, no win condition

So this phase requires new code, unavoidably. That's fine — name it honestly:

- [ ] Data-driven entity spawns in the level format (`EntityFactory` already
      exposes the `Create*` calls a spawn table would drive)
- [ ] Level registry + transitions + a win condition
- [ ] Then generate 3 levels agentically

This ordering matters: agentic level authoring works well against a **data
format** and badly against hand-tuned C++ constructor calls. Building the format
is what makes the AI-authored content phase viable — they're the same task.

This is also the phase that proves whether the ECS was worth it. Data-driven
spawning is exactly what a component/factory architecture is good at.

---

## Findings log

**#1 — `CMakeLists.txt` pins raylib but floats imgui/rlImGui.** raylib is pinned
to `4.5.0`, but imgui used `GIT_TAG master` and rlImGui `GIT_TAG main`. Today's
rlImGui calls `IsTextureValid()`, a raylib **5.5+** API → build fails with
`'IsTextureValid' was not declared in this scope`. The January build only worked
because it had an old clone cached in `_deps`; **any fresh clone would have hit
this.** Fixed by pinning imgui to `v1.91.5` and rlImGui to `583d4fea` (Nov 2024),
contemporary with raylib 4.5. A latent bug, not caused by the refactor.

**#2 — The small window came from the refactor branch, not master.** `master` has
always been `2560x1440`; the refactor changed it to `1200x700`. On a 1920x1080
display the master size puts the window off-screen at origin `(-323,-206)`,
larger than the display. Cherry-picked `1200x700` onto master.

**#3 — Attack works on master; it was broken only on the refactor branch.**
✅ Confirmed. The regression came from the mid-port `AttackSystem`/`CombatSystem`,
not from anything on master. `InputManager.cpp:40` binds `KEY_A →
AttackCommand::Execute`.

**#5 — Player spawn was desynced from the tile grid at any non-base resolution.**
✅ Fixed. `LevelOne.cpp:28` did `player->SetPosition({1500, 1500})` — a raw world
coordinate. But `SetPosition` is a plain assignment that runs *after* the `Player`
ctor's `Scale()`, while tiles **are** scaled (`Tile.cpp:21`). So the tile grid
contracts toward the origin as the window shrinks (step 74 → 34.7/36.0 at
1200x700) while the player stays at (1500, 1500), landing in empty space:

| Window | Spawn cell | Floor below? | Result |
|---|---|---|---|
| 2560x1440 (base) | col 20, row 20 | row 24 | lands after 276 units |
| 1200x700 (before fix) | col 43, row 41 | **none in column 43** | falls forever |
| 1200x700 (after fix) | col 20, row 20 | row 24 | lands after 134 units |
| 1920x1080 (after fix) | col 20, row 20 | row 24 | lands after 207 units |

Fix: scale the spawn like every other positioned object. All resolutions now map
to the same grid cell. This was latent on master and only surfaced once the
window stopped being exactly 2560x1440 — **the class of bug to expect from any
hardcoded literal in this codebase**, since `Globals.h` states outright that all
hardcoded values are tuned for 2560x1440.

**#6 — `TileManager`'s constructor position is dead code.** `LevelOne.cpp` passes
`Vector2{-2000, 250}`, the ctor stores it in `position_`, and **nothing ever reads
it**. `CreateTiles` places tiles from world origin. Confirmed at runtime. Harmless
today, but it means the level's world offset is a lie — worth deleting or
honouring before Phase 5 builds a level pipeline on top of it.

**#4 — The refactor is further along than "mid" suggests.** 59 files,
+1830/-141, nine systems, a full component set, and `LevelOne.cpp` already spawns
everything through `EntityFactory`. Worth knowing before assuming a rewrite is
cheaper than a finish.

---

## Tooling

### Build

The stale `build/` dir is a **WSL/Linux** cache (`/usr/bin/c++`) and is not
usable on Windows. The working toolchain is CLion's MinGW + Ninja:

```powershell
$p = "C:\Users\luke4\CLionProjects\The Land of Boars\The-Land-of-Boars"
$c = "C:/Program Files/JetBrains/CLion 2025.3.2/bin"   # forward slashes matter
$env:PATH = "$c/mingw/bin;$c/ninja/win/x64;$env:PATH" -replace '/','\'

cmake -S $p -B "$p\cmake-build-debug" -G Ninja -DCMAKE_BUILD_TYPE=Debug `
  -DCMAKE_C_COMPILER="$c/mingw/bin/gcc.exe" `
  -DCMAKE_CXX_COMPILER="$c/mingw/bin/g++.exe"

cmake --build "$p\cmake-build-debug" --target The_Land_of_Boars
```

Compiler paths **must** use forward slashes — CMake treats `C:\Program` as an
invalid escape, and the bad value gets cached into `CMakeCache.txt`, so it
persists across retries until that file is deleted.

### Visual debugging

`tools/capture.ps1` launches the game, drives input, and writes PNG frames to
`tools/frames/`. Steps are comma-separated:

| Step | Effect |
|---|---|
| `wait:<ms>` | sleep |
| `shot:<name>` | capture a PNG frame |
| `move:<x>:<y>` | move cursor (window-relative coords) |
| `click:<x>:<y>` | click at window-relative coords |
| `key:<KEY>:<ms>` | hold a key, then release |
| `tap:<KEY>` | quick press + release |

```powershell
.\capture.ps1 -Script "wait:1500,click:598:505,wait:2000,key:RIGHT:1200,shot:run,tap:A,shot:attack"
```

Two non-obvious things it has to do, both learned the hard way:

- **Move the window to (0,0)** so window-relative coords equal screen coords
- **Force the window topmost and steal focus** via `AttachThreadInput`.
  `SetForegroundWindow` alone fails from a background process, and since capture
  reads a *screen region*, losing focus means photographing the IDE instead of
  the game

Useful coords at `1200x700`: **Start game button = `598:505`**. `KEY_D` toggles
the ImGui debug overlay (position, velocity, `isOnGround`, object counts) — but
it opens collapsed, so click the arrow at `79:101` to expand it.

### Deterministic analysis — prefer this over replaying

Replaying the game and reading screenshots is slow and non-deterministic. Two
better tools, both of which found the spawn bug faster than screenshots did:

**`tools/spawn-analysis.ps1`** reproduces the engine's tile math in isolation
(same constants: `TILE_LENGTH 80`, overlap 6, base 2560x1440) and reports which
grid cell a spawn maps to, whether that cell is solid, and where the nearest
floor is — at any window size, without building or running anything. It was used
to *prove the fix generalizes across resolutions before writing the code*.

**Discrete `TraceLog` geometry output.** The game now logs its own geometry on
startup, so positions can be read as numbers instead of inferred from pixels:

```
[LEVEL] player spawn: raw(1500.0, 1500.0) -> scaled(703.1, 729.2)  [scale 0.4688, 0.4861]
[TILES] grid 59x0, 3250 solid tiles
[TILES] solid world bounds: x 0.0 .. 5272.5   y 323.8 .. 2014.4
[TILES] NOTE position_ (-2000.0, 250.0) is stored but never applied to tile placement
```

Capture it without any of the GUI harness:

```powershell
$p = "C:\Users\luke4\CLionProjects\The Land of Boars\The-Land-of-Boars"
Start-Process "$p\cmake-build-debug\The_Land_of_Boars.exe" -WorkingDirectory "$p\cmake-build-debug" `
  -RedirectStandardOutput "$env:TEMP\lob-run.log"
Select-String -Path "$env:TEMP\lob-run.log" -Pattern "\[LEVEL\]|\[TILES\]"
```

The static analysis and the runtime log agreed to the decimal, which is the
signal that the model of the engine is correct.
