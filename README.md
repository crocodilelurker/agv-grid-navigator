# AGV Grid Navigator

A simple **autonomous guided vehicle (AGV)** built on an ESP32. You draw a room as a grid on your phone, mark the obstacles, and the robot drives the best path from Start to Goal. You can also type or draw your own path.

**v1 (this repo):** a static map drawn in the web page. The page plans the path and the robot follows it.
**v2 (not planned yet):** the robot detects obstacles itself and maps its own path as it moves.

## How it works

1. The ESP32 creates its own Wi-Fi network called **`AGV-Robot`** and serves the web page at **`http://192.168.4.1`**.
2. In the page you set the grid size or the room size in cm, with 1 cell = **30 cm**. Then you mark obstacles, the Start cell, the way the robot faces and the Goal cell.
3. The page finds the best path using A* search. The path is the shortest one with the fewest turns, because turns are the least accurate move.
4. You can use the auto path, or a **custom path** that you type (for example `FFRFLF`) or draw cell by cell.
5. **Go** sends the path to the robot as letters. The robot drives it, and the page shows live progress. **Stop** works at any time.

| Letter | Move |
|---|---|
| `F` | forward one cell (30 cm) |
| `R` | spin 90° right on the spot |
| `L` | spin 90° left on the spot |

## Hardware

- ESP32 development board, with the Arduino IDE and **ESP32 Arduino Core 3.x**
- A 4-wheel chassis with 4 DC motors, two on each side
- 2 × BTS7960 motor drivers, one for the left side and one for the right
- A battery, with ground shared between the ESP32 and both drivers
- **No sensors or encoders.** Every move is timed, so positions are approximate and the error grows on long paths.

| Driver | RPWM | LPWM | R_EN / L_EN |
|---|---|---|---|
| Right BTS7960 | GPIO 23 | GPIO 22 | 3.3V |
| Left BTS7960 | GPIO 25 | GPIO 21 | 3.3V |

## Calibration (current values)

| What | Value |
|---|---|
| Straight-drive speeds | right 186 / left 180 (PWM 0–255) |
| Forward 1 cell (30 cm) | 300 ms |
| Spin 90° right / left | 245 ms / 245 ms, at speed 180 |
| Pause after every move | 300 ms |

These values change slightly with battery charge and floor surface. Re-tune them if the robot drifts. The full calibration history is in [`codes/README.md`](codes/README.md).

## Folder structure

```
├── README.md            ← this file
├── PREV.md              ← notes from the earliest work (hardware and what was learned)
├── sketch_nov24a.ino    ← early test sketch (same as codes/v01)
├── codes/               ← every version of the robot code, kept as history
│   ├── README.md        ← what each version does, what changed, test results
│   ├── v00_base_straight_drive/
│   ├── v01_forward20_pivot_right/
│   ├── v02_one_cell_30cm/
│   ├── v03_spin_right_90/
│   ├── v04_spin_90_check_both/
│   ├── v05_command_runner_square/
│   └── v06_wifi_web_control/     ← latest: Wi-Fi and web control
└── web/
    ├── index.html       ← the web page (a single file, works offline)
    ├── README.md        ← page usage, HTTP protocol, map format
    └── make_header.py   ← packs index.html into the sketch as index_html.h
```

## Quick start

1. Open `codes/v06_wifi_web_control/v06_wifi_web_control.ino` in the Arduino IDE and upload it to the ESP32.
2. Join the Wi-Fi network **`AGV-Robot`** (password `agv12345`) from your phone or laptop.
3. Open **`http://192.168.4.1`**.
4. Draw the map. Put the robot in the middle of the Start cell, facing the arrow, and press **Go**.

**If you change `web/index.html`**, rebuild the packed page and upload the sketch again:

```bash
python3 web/make_header.py codes/v06_wifi_web_control
```

You can also open `web/index.html` straight from your computer to plan paths without the robot.

## Robot HTTP API

| Request | What it does |
|---|---|
| `GET /` | sends the web page |
| `POST /run` | the body is the path, e.g. `FFRFFLF`. Replies `OK n steps`, `BUSY` (409) or `ERR bad command` (400) |
| `POST /stop` | stops the motors immediately |
| `GET /status` | returns JSON such as `{"state":"running","step":3,"total":7}` |

Full details are in [`web/README.md`](web/README.md).

## Safety

- Test in a clear area and keep a hand near the power switch.
- If the phone loses its connection, the robot finishes the path it already received.
- The robot cannot see obstacles. It only avoids the ones marked on the map.

## Status

- [x] Straight driving, 30 cm cell and 90° spin turns calibrated
- [x] Command runner with no `delay()` while driving
- [x] Web page: grid editor, A* planner, custom paths, live progress
- [x] Wi-Fi access point and web server on the ESP32 (v06)
- [ ] v06 tested on the real robot
