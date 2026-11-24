# AGV web interface (`index.html`)

One self-contained page (HTML + CSS + JavaScript, no internet needed, about 53 KB).
The ESP32 serves it from its own Wi-Fi access point at `http://192.168.4.1`.

## What it does

1. You draw the room as a grid (1 cell = 30 cm): obstacles, a **Start** cell (with the way the robot faces) and a **Goal** cell.
2. The page finds the best path (A* search) and turns it into a command string such as `FFRFFLF`.
3. Or you make your **own path** (Custom): type the letters, or draw the route on the grid.
4. **Go** sends the active path (Auto or Custom) to the robot. **Stop** stops it. While it runs, the page shows its progress.

| Command | Meaning |
|---|---|
| `F` | drive forward one cell (30 cm) |
| `R` | spin 90° right on the spot |
| `L` | spin 90° left on the spot |

A U-turn is always sent as `RR`. Top of the grid is North. Facing North, `R` makes the robot face East.

Turns are the least accurate move (no sensors), so each turn costs extra in the planner (**Turn penalty**, default 2 = one turn "costs" the same as 2 cells).
A higher penalty gives paths with fewer turns, even if they are a bit longer.

## How to use

**On a phone (normal use)**
1. Switch on the robot. Join its Wi-Fi network. If the phone says "no internet", choose to stay connected. If the page can't reach the robot, turn off mobile data.
2. Open `http://192.168.4.1` in the browser.
3. Pick a mode (Obstacle / Start / Goal / Erase) and tap cells. Drag to paint or erase several obstacles.
   In Start mode, tap the Start cell again to rotate it, or use the N/E/S/W buttons.
4. Put the robot in the middle of the Start cell, facing the arrow's direction.
5. Leave **Robot address** empty and press **Go**.

**On a laptop, testing from a file**
Open `index.html` by double-clicking it. Everything except Go/Stop works without the robot.
To drive the robot, join its Wi-Fi and type `http://192.168.4.1` in **Robot address**.
(If your browser blocks a local file from talking to the robot, use the page served by the robot instead.)

**Custom path (your own route)**
1. In the Path box, switch from **Auto (best path)** to **Custom**. (Picking **Draw** mode does this for you.)
2. Either **type** the letters in the box, e.g. `ff r ffl f`. Lower case, spaces, commas and new lines are fine;
   the page sends only the upper-case letters (`FFRFFLF`). Any other character is shown as an error, and Go stays off.
3. Or **draw** it: choose **Draw** mode and tap the cells one by one, starting next to the Start cell
   (you can also drag your finger along them). The page works out the turns for you, using the way the robot faces at that point:
   a cell to the right becomes `RF`, a cell behind becomes `RRF`.
   Tap the last cell again (or press **Undo**) to remove it. Drag back one cell to undo while drawing. **Clear path** removes the whole route.
   **Copy best path here** copies the Auto path into the box so you can change it.
4. The typed box and the drawing always match. The custom route is drawn in **blue** (the Auto path is yellow).
5. If the route drives off the grid or into an obstacle, that cell gets **red stripes** and a warning appears.
   Go still works, but asks you to confirm first. The page also says whether the route ends on the Goal.
   A custom path needs a Start cell, but a Goal is optional.
6. The custom path is stored as commands, starting from Start. If you move the Start cell or change its heading,
   the route moves with it.

**Map size:** set rows/columns (2 to 30), or type the room width and length in cm and press Apply
(columns = width ÷ cell size, rows = length ÷ cell size, rounded down). Resizing keeps everything that still fits.

**Saving:** the map (including the custom path and the Auto/Custom choice) is saved in the browser automatically. Under *Save / load map* you can copy it as JSON text,
download it as a file, or load it back (useful for moving a map between phone and laptop).

## HTTP protocol (for the ESP32 firmware)

`{addr}` is empty when the robot serves the page, or e.g. `http://192.168.4.1` when testing from a file.

### `GET /`
Return `index.html` with `Content-Type: text/html`.

### `POST /run` - start a path
- Request: `Content-Type: text/plain`, body = the command string only, e.g. `FFRFFLF`
  (only the letters `F`, `R`, `L`, no spaces or newline). On a 30 x 30 grid a path can be a few hundred letters long.
  Custom paths are sent exactly the same way. A custom path can be any mix of F/R/L, including back-to-back turns such as `LL`,
  and one the user confirmed even though it leaves the grid.
- Response (plain text, the page shows it to the user):

| Situation | Status | Body (example) |
|---|---|---|
| accepted, robot starts moving | `200` | `OK 7 steps` |
| empty body or a letter that is not F/R/L | `400` | `ERR bad command` |
| already running a path | `409` | `BUSY` |

**Reply straight away, then drive.** The page gives up after 4 seconds. Drive with a `millis()` timer
(not long `delay()` calls), so the robot can still answer `/stop` and `/status` while it moves.

### `POST /stop` - stop now
- Request: no body.
- Robot stops the motors at once and forgets the rest of the path.
- Response: `200`, plain text, e.g. `STOPPED`.

### `GET /status` - progress (optional)
- Response: `200`, `Content-Type: application/json`:
  ```json
  {"state":"running","step":3,"total":7}
  ```
  - `state`: `"idle"` or `"running"` (any other word is just shown to the user).
  - `step`: how many commands are **finished** (0 to `total`).
  - `total`: number of commands in the current path.
- The page asks once a second while the robot is running and stops asking when `state` is not `"running"`.
  If `/status` is missing it gives up quietly after 3 tries.

### CORS (needed only for testing from a local file)
Add this header to **every** response:
```
Access-Control-Allow-Origin: *
```
The page only sends "simple" requests (GET, and POST with `text/plain`), so the browser does not send an
`OPTIONS` pre-check. Answering `OPTIONS` with `204` is harmless if you want to be safe.

## Timing constants (must match the firmware)

At the top of the `<script>` in `index.html` (only used for the time estimate):

| Constant | Value | Meaning |
|---|---|---|
| `CELL_TIME` | 300 ms | drive time for one `F` (30 cm) |
| `SPIN_TIME` | 245 ms | spin time for one `R` or `L` (90°) |
| `PAUSE_TIME` | 300 ms | stop after **every** move |

Estimated time = F × CELL_TIME + turns × SPIN_TIME + (all moves) × PAUSE_TIME.
If you re-tune the robot, change these numbers too. The page uses one `SPIN_TIME` for both directions.
If left and right spins end up different, the estimate will be a little off.

## Map JSON format

```json
{
  "version": 1, "rows": 3, "cols": 5, "cellCm": 30,
  "heading": "N", "turnPenalty": 2,
  "start": [2, 0], "goal": [0, 4],
  "grid": [".....", ".###.", "....."],
  "pathSource": "auto", "customPath": ""
}
```
`start`/`goal` are `[row, column]` counted from the top-left (0, 0). In `grid`, `#` is an obstacle and `.` is free.
`pathSource` is `"auto"` or `"custom"`, and `customPath` is the custom commands as typed.
Older files without these two fields still load (as Auto with an empty custom path).

## Putting the page on the ESP32

The simplest way is to paste the whole file into the sketch as a raw string:
```cpp
const char INDEX_HTML[] PROGMEM = R"rawliteral(
...paste index.html here...
)rawliteral";
```
and send it from the `/` handler. (Storing it in LittleFS also works.)
