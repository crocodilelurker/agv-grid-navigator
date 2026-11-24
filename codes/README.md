# Code History

Every version of the AGV code is kept here, so we can always go back to one that worked.

## How this folder works

- Each version has its own folder: `vNN_short_name/vNN_short_name.ino`.
  The Arduino IDE needs the `.ino` file to sit in a folder with the same name, so you can open any version directly.
- Old versions are **never edited**. Any change becomes a new version with the next number.
- Each version gets an entry below saying what it does, what changed and what the test showed.

## Current calibration values

| What | Value | Status |
|---|---|---|
| Straight speeds | RIGHT 186 / LEFT 180 | Confirmed |
| 200 ms forward | 20 cm | Confirmed (v01) |
| 150 ms forward | 14.5 cm | Confirmed (PREV.md) |
| 1 cell = 30 cm forward | 300 ms | Confirmed (v02) |
| Pivot right 90° (R=0, L=180) | 460 ms | Confirmed (v01), being replaced by spin turn |
| Spin right 360°, one continuous spin | 950 ms | Confirmed (v03) |
| Spin right 90°, separate move | **245 ms** | Confirmed (v05). It was 238 in v04 |
| Spin left 90° (R=180, L=-180), separate move | **245 ms** | Confirmed (v05). It was 238 in v04 |
| Combined path (2×2-cell square) | works | Confirmed (v05) |
| Start delay after Go | 1000 ms | In use (v06) |
| Wi-Fi network | `AGV-Robot` / `agv12345` | In use (v06), at http://192.168.4.1 |
| Pause between moves | 300 ms | In use |

---

## v00_base_straight_drive

- **What it does:** Sets up the motor pins and PWM. It does not move the robot.
- **Source:** The "WORKING BASE CODE" section of `PREV.md`. An empty `loop()` was added so it compiles.
- **What we learned:**
  - The software reversal of the right side was removed. A positive value now means forward on both sides.
  - At 180/180 the robot drifted right. RIGHT = 186 and LEFT = 180 make it drive straight.
- **Status:** Tested and working.

## v01_forward20_pivot_right

- **What it does:** Forward 20 cm, pivot right 90°, forward 20 cm, pivot right 90°, stop. This is half a square.
- **Changed from v00:** Added `goForward()` and `sharpTurnRight()`, with tunable constants `FORWARD_TIME = 200`, `TURN_TIME = 460` and `PAUSE_TIME = 300`.
  - The turn is a pivot: the right side is stopped and the left side drives at 180.
  - TURN_TIME was changed from the first guess of 500 to 460.
- **Test result:** Forward is exactly 20 cm, and the turn is 90°.
- **Note:** The pivot turn moves the robot off the centre of its cell. On a 30 cm grid that adds up over several turns, so we are switching to a spin turn.
- **Status:** Tested and working. This is the same code as `../sketch_nov24a.ino`.

## v02_one_cell_30cm

- **What it does:** Drives forward one grid cell (30 cm) once, then stops.
- **Changed from v01:** The turns are removed. `FORWARD_TIME` is renamed `CELL_TIME` and set to 300 ms, estimated from 200 ms → 20 cm.
- **Test result:** Works as expected. The robot moves one cell (30 cm).
- **Status:** Tested and working.

## v03_spin_right_90

- **What it does:** One spin turn to the right (aiming for 90°), then stops.
- **Changed from v02:** The forward move is not called. Added `spinRight()`, which drives the right side backward and the left side forward at `SPIN_SPEED = 180` for `SPIN_TIME = 250` ms.
  - A spin turns the robot on the spot, so it stays in the centre of its cell.
  - 250 ms is a first guess. Both sides drive in a spin, so it should be quicker than the 460 ms pivot.
- **Test result:** The team changed SPIN_TIME to make one full circle. At 1000 ms the robot turned about 385° (≈25° too far). **At 950 ms it turned exactly 360°.**
- **Status:** Tested. 950 ms = 360° for one continuous spin. The `.ino` here still shows the original 250 ms.

## v04_spin_90_check_both

- **What it does:** 4 separate right spins, a 3 s wait, then 4 separate left spins. After each set of 4, the robot should face the direction it started in.
- **Changed from v03:**
  - `SPIN_TIME` is split into `SPIN_RIGHT_TIME` and `SPIN_LEFT_TIME`, both 238 ms (950 ÷ 4).
  - Added `spinLeft()`, the mirror of `spinRight()`.
- **Why this test:** Each separate turn has its own start-up delay and roll after stopping, so four 238 ms spins may not add up to one 950 ms spin. The path will be made of separate 90° turns, so that's what we need to check. Left also needs checking, because the motors may not be equally strong in reverse.
- **Test result:** 238 ms works for both right and left. The robot comes back to the start direction after 4 separate spins each way.
- **Status:** Tested and working.

## v05_command_runner_square

- **What it does:** Drives a path written as letters (`F` = forward 1 cell, `R` / `L` = spin 90°). The test path `FFRFFRFFRFFR` is a square of 2 cells (60 cm) per side that should end back at the start.
- **Changed from v04:**
  - Added a "command runner" (`startCommands()`, `updateRunner()` and `stopCommands()`) that reads the letters one by one.
  - It uses `millis()` instead of `delay()` while driving, so the ESP32 never freezes. The Wi-Fi version needs this so it can listen for Go and Stop while the robot is moving.
  - All the confirmed calibration values are collected at the top.
- **Why this test:** It's the first time forward moves and spins run together in one path. It also tests the runner that the Wi-Fi version will feed.
- **Test result:** At 238 ms the square was a little off. With **both spin times at 245 ms** it works well and comes back to the start.
- **Status:** Tested and working. The `.ino` here still shows 238. The confirmed value is 245.

## v06_wifi_web_control

- **What it does:** The robot creates its own Wi-Fi network (`AGV-Robot`, password `agv12345`) and serves the web page at `http://192.168.4.1`. When you press **Go**, it drives the path the page sends. **Stop** stops it at once.
- **Files in this folder:**
  - `v06_wifi_web_control.ino` is the sketch.
  - `index_html.h` is the web page, packed so the sketch can serve it. It's generated from `web/index.html` by `python3 web/make_header.py codes/v06_wifi_web_control`. Run that again whenever the page changes.
- **Changed from v05:**
  - Added a Wi-Fi network and a web server, using the `WiFi.h` and `WebServer.h` libraries that come with the ESP32 board package.
  - New web addresses:
    - `GET /` sends the page.
    - `POST /run` takes the path letters. It replies `OK n steps`, or `BUSY` if a path is already running, or `ERR bad command`.
    - `POST /stop` stops the robot.
    - `GET /status` returns progress as JSON.
  - The fixed `TEST_PATH` is removed. The path now comes from the page.
  - The robot waits 1 s after Go before moving (`START_DELAY`).
  - Spin times are 245 ms.
  - `loop()` now does two jobs: `server.handleClient()` answers the page and `updateRunner()` drives. Because nothing uses `delay()`, Stop works while the robot is moving.
- **Test result:** _waiting_
- **Status:** Testing.
