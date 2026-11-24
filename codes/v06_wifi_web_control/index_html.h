// AUTO-GENERATED from web/index.html by web/make_header.py
// Do not edit by hand - edit web/index.html and run the script again.
#pragma once

const char INDEX_HTML[] PROGMEM = R"AGVHTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>AGV Path Planner</title>
<link rel="icon" href="data:,"><!-- stops a favicon request -->
<style>
  /* ---------- Colours (light mode first, dark mode below) ---------- */
  :root {
    --bg: #f3f4f7;  --card: #ffffff;  --text: #1d2330;  --muted: #5f6b7a;
    --line: #cfd5de; --input: #ffffff;
    --free: #ffffff; --wall: #2f3440;
    --start: #1f9d55; --goal: #d93d30;
    --path: #ffd75e; --path-text: #5a4300;
    --turn: #f59e0b; --here: #2563eb;
    --cpath: #a5d8ff; --cpath-text: #0b3d66; --cturn: #3b82f6;
    --accent: #2563eb; --accent-text: #ffffff;
    --ok: #15803d; --err: #c62828; --warn: #a16207;
    --danger: #c62828;
  }
  @media (prefers-color-scheme: dark) {
    :root {
      --bg: #12151b;  --card: #1c2029;  --text: #e6e9ef;  --muted: #9aa4b2;
      --line: #3a414e; --input: #262b36;
      --free: #262b36; --wall: #b7bfcc;
      --start: #22a35a; --goal: #e0473a;
      --path: #8a6d10; --path-text: #fff3c4;
      --turn: #c27406; --here: #60a5fa;
      --cpath: #1d4e7a; --cpath-text: #d6ecff; --cturn: #2f6fd6;
      --accent: #3b82f6; --accent-text: #ffffff;
      --ok: #4ade80; --err: #f87171; --warn: #facc15;
      --danger: #dc2626;
    }
  }

  /* ---------- Page layout ---------- */
  * { box-sizing: border-box; }
  [hidden] { display: none !important; }   /* make the hidden attribute always win */
  body {
    margin: 0; background: var(--bg); color: var(--text);
    font: 15px/1.4 system-ui, -apple-system, "Segoe UI", Roboto, sans-serif;
  }
  header { padding: 12px 16px 4px; }
  h1 { font-size: 20px; margin: 0; }
  h2 { font-size: 16px; margin: 0 0 10px; }
  .layout { display: grid; grid-template-columns: minmax(0, 1fr); gap: 12px; padding: 12px; max-width: 1200px; margin: 0 auto; }
  @media (min-width: 900px) {
    .layout { grid-template-columns: minmax(0, 3fr) minmax(320px, 2fr); align-items: start; }
  }
  .side { display: grid; gap: 12px; min-width: 0; }
  .card { background: var(--card); border: 1px solid var(--line); border-radius: 10px; padding: 12px; min-width: 0; }
  .row { display: flex; flex-wrap: wrap; gap: 8px; align-items: center; margin-bottom: 8px; }
  .muted { color: var(--muted); font-size: 13px; }
  label { display: inline-flex; align-items: center; gap: 6px; }

  /* ---------- Form controls ---------- */
  input, textarea, button { font: inherit; color: inherit; }
  input[type=number], input[type=text], textarea {
    background: var(--input); border: 1px solid var(--line); border-radius: 6px; padding: 6px 8px;
  }
  input[type=number] { width: 72px; }
  input[type=text] { flex: 1; min-width: 0; }
  textarea { width: 100%; min-height: 120px; font-family: ui-monospace, Menlo, Consolas, monospace; font-size: 12px; }
  button {
    min-height: 40px; padding: 6px 14px; border-radius: 8px; cursor: pointer;
    border: 1px solid var(--line); background: var(--input);
  }
  button:disabled { opacity: 0.45; cursor: not-allowed; }
  button.primary { background: var(--accent); color: var(--accent-text); border-color: var(--accent); }
  button.danger  { background: var(--danger); color: #fff; border-color: var(--danger); }
  button.big { font-size: 18px; font-weight: 600; min-width: 110px; }
  .seg { display: inline-flex; border: 1px solid var(--line); border-radius: 8px; overflow: hidden; }
  .seg { flex-wrap: wrap; }
  .seg button { border: 0; border-radius: 0; border-right: 1px solid var(--line); min-width: 44px; padding: 6px 9px; }
  .seg button:last-child { border-right: 0; }
  .seg button.active { background: var(--accent); color: var(--accent-text); }

  /* ---------- The grid ---------- */
  #gridWrap { width: 100%; overflow: auto; padding: 4px 0; }
  #grid {
    display: grid; gap: 1px; margin: 0 auto; width: max-content;
    background: var(--line); border: 2px solid var(--line);
    touch-action: none;   /* drag-paint on phones without scrolling */
    user-select: none; -webkit-user-select: none;
  }
  .cell {
    background: var(--free); display: flex; align-items: center; justify-content: center;
    font-weight: 700; line-height: 1; cursor: pointer; position: relative;
  }
  .cell span { pointer-events: none; display: inline-block; }
  .cell.wall  { background: var(--wall); }
  .cell.path  { background: var(--path); color: var(--path-text); }
  .cell.turn  { background: var(--turn); color: #fff; }
  .cell.start { background: var(--start); color: #fff; }
  .cell.goal  { background: var(--goal); color: #fff; }
  /* custom path: blue cells; problems: red stripes */
  .cell.cpath { background: var(--cpath); color: var(--cpath-text); }
  .cell.cturn { background: var(--cturn); color: #fff; }
  .cell.bad {
    background-image: repeating-linear-gradient(45deg, transparent 0 4px, var(--err) 4px 8px);
    box-shadow: inset 0 0 0 2px var(--err);
  }
  .cell.end::before {
    content: ""; position: absolute; inset: 3px; border: 2px dashed var(--accent); border-radius: 4px;
  }
  .cell.here::after {
    content: ""; position: absolute; inset: 1px; border: 3px solid var(--here); border-radius: 4px;
  }

  /* ---------- Legend ---------- */
  .legend { display: flex; flex-wrap: wrap; gap: 6px 14px; margin-top: 10px; font-size: 13px; }
  .legend i {
    display: inline-block; width: 16px; height: 16px; border-radius: 3px;
    border: 1px solid var(--line); vertical-align: -3px; margin-right: 4px;
  }

  /* ---------- Output ---------- */
  #cmd {
    display: block; padding: 10px; border-radius: 8px; background: var(--input);
    border: 1px solid var(--line); font: 18px/1.3 ui-monospace, Menlo, Consolas, monospace;
    word-break: break-all; letter-spacing: 1px; min-height: 44px; user-select: all;
  }
  .stats { display: grid; grid-template-columns: auto 1fr; gap: 2px 12px; margin: 10px 0; font-size: 14px; }
  .stats dt { color: var(--muted); }
  .stats dd { margin: 0; font-weight: 600; }
  .msg { min-height: 1.4em; font-size: 14px; margin: 6px 0 0; }
  .msg.ok { color: var(--ok); }  .msg.err { color: var(--err); }  .msg.warn { color: var(--warn); }
  progress { width: 100%; height: 14px; }
  details summary { cursor: pointer; font-weight: 600; }
  #customText { min-height: 60px; font-size: 16px; text-transform: uppercase; }
</style>
</head>
<body>

<header>
  <h1>AGV Path Planner</h1>
  <div class="muted">Draw the room, then send the path to the robot.</div>
</header>

<main class="layout">

  <!-- ===== GRID + EDITING ===== -->
  <section class="card">
    <div class="row">
      <span class="muted">Tap mode:</span>
      <div class="seg" id="modeButtons">
        <button data-mode="wall" class="active">Obstacle</button>
        <button data-mode="start">Start</button>
        <button data-mode="goal">Goal</button>
        <button data-mode="erase">Erase</button>
        <button data-mode="draw" title="Draw a custom path">Draw</button>
      </div>
    </div>
    <div class="row">
      <span class="muted">Start facing:</span>
      <div class="seg" id="headingButtons">
        <button data-heading="0">N &uarr;</button>
        <button data-heading="1">E &rarr;</button>
        <button data-heading="2">S &darr;</button>
        <button data-heading="3">W &larr;</button>
      </div>
      <button id="clearBtn">Clear all</button>
    </div>

    <div id="gridWrap"><div id="grid"></div></div>

    <div class="legend">
      <span><i style="background:var(--free)"></i>Free</span>
      <span><i style="background:var(--wall)"></i>Obstacle</span>
      <span><i style="background:var(--start)"></i>Start (arrow = facing)</span>
      <span><i style="background:var(--goal)"></i>Goal</span>
      <span><i style="background:var(--path)"></i>Path (arrow = way out)</span>
      <span><i style="background:var(--turn)"></i>Robot turns here</span>
      <span><i style="background:var(--cpath)"></i>Custom path</span>
      <span><i style="background:var(--cturn)"></i>Custom turn</span>
      <span><i style="box-shadow:inset 0 0 0 2px var(--err);background:repeating-linear-gradient(45deg,transparent 0 3px,var(--err) 3px 6px)"></i>Problem</span>
      <span><i style="border:2px dashed var(--accent)"></i>Route end</span>
      <span><i style="border:3px solid var(--here)"></i>Robot now</span>
    </div>
    <p class="muted">Top of the grid is North. Tap a cell to place. Drag to paint or erase obstacles.
      Tap the Start cell again (in Start mode) to rotate it.
      Draw mode: tap (or drag over) cells next to the route end to build a custom path; tap the last cell to undo.</p>
  </section>

  <div class="side">

    <!-- ===== PATH OUTPUT ===== -->
    <section class="card">
      <h2>Path</h2>
      <div class="row">
        <div class="seg" id="sourceButtons">
          <button data-source="auto" class="active">Auto (best path)</button>
          <button data-source="custom">Custom</button>
        </div>
      </div>
      <code id="cmd">-</code>
      <div class="row" style="margin-top:8px">
        <button id="copyBtn">Copy commands</button>
        <label id="penaltyBox">Turn penalty <input type="number" id="penaltyInput" min="0" max="20" step="0.5" value="2"></label>
      </div>
      <!-- Custom path: type letters, or use Draw mode on the grid (both stay in sync) -->
      <div id="customBox" hidden>
        <label for="customText" class="muted">Your commands (F, R, L - spaces and commas are ignored):</label>
        <textarea id="customText" spellcheck="false" autocomplete="off" autocapitalize="characters" placeholder="e.g. FFRFFLF"></textarea>
        <div class="row" style="margin-top:8px">
          <button id="undoBtn">Undo</button>
          <button id="clearPathBtn">Clear path</button>
          <button id="useAutoBtn">Copy best path here</button>
        </div>
        <p id="drawNote" class="msg"></p>
      </div>
      <p id="planMsg" class="msg"></p>
      <dl class="stats">
        <dt>Forward moves</dt><dd id="statForward">0</dd>
        <dt>90&deg; turns</dt><dd id="statTurns">0</dd>
        <dt>Total moves</dt><dd id="statMoves">0</dd>
        <dt>Estimated time</dt><dd id="statTime">0 s</dd>
      </dl>
      <p class="muted">F = forward one cell, R = spin right 90&deg;, L = spin left 90&deg;.
        A higher turn penalty makes the planner avoid turns (turns are the least accurate move).</p>
    </section>

    <!-- ===== ROBOT CONTROL ===== -->
    <section class="card">
      <h2>Robot</h2>
      <div class="row">
        <label for="addrInput" class="muted">Robot address</label>
        <input type="text" id="addrInput" placeholder="(empty = this page's robot)" autocomplete="off" autocapitalize="off" spellcheck="false">
      </div>
      <p id="addrHint" class="muted"></p>
      <div class="row">
        <button id="goBtn" class="primary big">Go</button>
        <button id="stopBtn" class="danger big">Stop</button>
        <button id="statusBtn">Check robot</button>
      </div>
      <p id="robotMsg" class="msg"></p>
      <div id="progressBox" hidden>
        <progress id="progressBar" max="1" value="0"></progress>
        <div id="progressText" class="muted"></div>
      </div>
    </section>

    <!-- ===== MAP SIZE ===== -->
    <section class="card">
      <h2>Map size</h2>
      <div class="row">
        <label>Rows <input type="number" id="rowsInput" min="2" max="30" value="6"></label>
        <label>Columns <input type="number" id="colsInput" min="2" max="30" value="6"></label>
      </div>
      <div class="row">
        <label>Cell size <input type="number" id="cellInput" min="1" max="500" value="30"> cm</label>
      </div>
      <p class="muted">Cell size must match how far the robot drives in one F move (CELL_TIME).</p>
      <div class="row">
        <span class="muted">Or from room size:</span>
        <label>Width <input type="number" id="roomW" min="1" placeholder="cm"></label>
        <label>Length <input type="number" id="roomL" min="1" placeholder="cm"></label>
        <button id="roomBtn">Apply</button>
      </div>
      <p id="sizeMsg" class="msg"></p>
    </section>

    <!-- ===== SAVE / LOAD ===== -->
    <section class="card">
      <details>
        <summary>Save / load map</summary>
        <p class="muted">The map is saved in this browser automatically. Use these to move a map to another device.</p>
        <textarea id="jsonBox" spellcheck="false" placeholder="Map JSON appears here"></textarea>
        <div class="row" style="margin-top:8px">
          <button id="exportBtn">Show map JSON</button>
          <button id="importBtn">Load JSON from box</button>
          <button id="downloadBtn">Download file</button>
          <button id="fileBtn" type="button">Open file</button>
          <input type="file" id="fileInput" accept=".json,.txt,application/json,text/plain" hidden>
        </div>
        <p id="ioMsg" class="msg"></p>
      </details>
    </section>

  </div>
</main>

<script>
"use strict";

/* =====================================================================
   1. SETTINGS - change these to match the robot firmware
   ===================================================================== */
const CELL_TIME  = 300;  // ms the robot drives to move forward one cell (30 cm)
const SPIN_TIME  = 245;  // ms the robot spins for one 90 degree turn
const PAUSE_TIME = 300;  // ms the robot waits (stopped) after EVERY move

const MIN_SIZE = 2;              // smallest grid allowed (rows or columns)
const MAX_SIZE = 30;             // biggest grid allowed
const REQUEST_TIMEOUT_MS = 4000; // give up on /run and /stop after this long
const STATUS_TIMEOUT_MS  = 2000; // give up on /status after this long
const POLL_EVERY_MS      = 1000; // how often to ask the robot for progress
const STORAGE_KEY = "agv-map-v1";       // localStorage key for the map
const ADDR_KEY    = "agv-robot-addr";   // localStorage key for the robot address


/* =====================================================================
   2. PATH PLANNER + CUSTOM PATH HELPERS (pure logic, no web page code - easy to test)
   Headings: 0 = N (up), 1 = E (right), 2 = S (down), 3 = W (left).
   A "map" object looks like:
     { rows, cols, walls: [[true/false...]...], start: {r,c} or null,
       goal: {r,c} or null, heading: 0..3, turnPenalty: number }
   ===================================================================== */
// PLANNER-START
const HEADING_NAMES = ["N", "E", "S", "W"];
const ROW_STEP = [-1, 0, 1, 0];   // how the row changes when moving forward
const COL_STEP = [0, 1, 0, -1];   // how the column changes when moving forward

function turnRight(h) { return (h + 1) % 4; }
function turnLeft(h)  { return (h + 3) % 4; }

// True if (r, c) is inside the grid and not an obstacle.
function isFree(map, r, c) {
  return r >= 0 && r < map.rows && c >= 0 && c < map.cols && !map.walls[r][c];
}

// Priority queue (binary heap): pop() always returns the "smallest" item.
class MinHeap {
  constructor(isLess) { this.items = []; this.isLess = isLess; }
  get size() { return this.items.length; }
  push(item) {
    const a = this.items;
    a.push(item);
    let i = a.length - 1;
    while (i > 0) {                       // bubble the new item up
      const parent = (i - 1) >> 1;
      if (!this.isLess(a[i], a[parent])) break;
      [a[i], a[parent]] = [a[parent], a[i]];
      i = parent;
    }
  }
  pop() {
    const a = this.items;
    const top = a[0];
    const last = a.pop();
    if (a.length > 0) {                   // move the last item to the top and sink it down
      a[0] = last;
      let i = 0;
      while (true) {
        const left = 2 * i + 1, right = left + 1;
        let smallest = i;
        if (left < a.length && this.isLess(a[left], a[smallest])) smallest = left;
        if (right < a.length && this.isLess(a[right], a[smallest])) smallest = right;
        if (smallest === i) break;
        [a[i], a[smallest]] = [a[smallest], a[i]];
        i = smallest;
      }
    }
    return top;
  }
}

// Clean up runs of turns: "LL" becomes "RR" (a U-turn is always RR),
// "RRR" becomes "L", "RL" disappears. Only happens with a turn penalty of 0.
function simplifyTurns(moves) {
  return moves.replace(/[RL]+/g, run => {
    let net = 0;
    for (const ch of run) net += (ch === "R") ? 1 : -1;
    net = ((net % 4) + 4) % 4;            // 0..3 quarter turns to the right
    return ["", "R", "RR", "L"][net];
  });
}

// Play the commands from the start and list the robot's pose after each one.
// poses[0] is the start; poses[i] is where the robot is after i commands.
function simulate(start, heading, commands) {
  let pose = { r: start.r, c: start.c, h: heading };
  const poses = [pose];
  for (const cmd of commands) {
    if (cmd === "F") pose = { r: pose.r + ROW_STEP[pose.h], c: pose.c + COL_STEP[pose.h], h: pose.h };
    else if (cmd === "R") pose = { r: pose.r, c: pose.c, h: turnRight(pose.h) };
    else if (cmd === "L") pose = { r: pose.r, c: pose.c, h: turnLeft(pose.h) };
    poses.push(pose);
  }
  return poses;
}

// Count moves and estimate how long the robot will take.
function commandStats(commands) {
  let forward = 0, right = 0, left = 0;
  for (const cmd of commands) {
    if (cmd === "F") forward++;
    else if (cmd === "R") right++;
    else if (cmd === "L") left++;
  }
  const turns = right + left;
  const moves = forward + turns;
  const timeMs = forward * CELL_TIME + turns * SPIN_TIME + moves * PAUSE_TIME;
  return { forward, right, left, turns, moves, timeMs };
}

// A* search over (row, col, heading).
// Moves: F (forward one cell, cost 1), R / L (spin 90 degrees in place, cost = turnPenalty).
// Returns { ok, commands, poses, cost, message }.
function planPath(map) {
  const { rows, cols, start, goal } = map;
  if (!start && !goal) return { ok: false, message: "Place a Start and a Goal cell." };
  if (!start) return { ok: false, message: "Place a Start cell." };
  if (!goal)  return { ok: false, message: "Place a Goal cell." };
  if (!isFree(map, start.r, start.c)) return { ok: false, message: "Start is outside the grid or on an obstacle." };
  if (!isFree(map, goal.r, goal.c))   return { ok: false, message: "Goal is outside the grid or on an obstacle." };
  if (start.r === goal.r && start.c === goal.c) {
    return { ok: true, commands: "", poses: [{ r: start.r, c: start.c, h: map.heading }], cost: 0,
             message: "The robot is already at the goal." };
  }

  const penalty = Math.max(0, Number(map.turnPenalty) || 0);
  const stateCount = rows * cols * 4;
  const keyOf = (r, c, h) => (r * cols + c) * 4 + h;     // one number per (row, col, heading)
  const bestCost = new Array(stateCount).fill(Infinity); // cheapest known cost to reach each state
  const cameFrom = new Array(stateCount).fill(-1);       // previous state on that cheapest route
  const moveUsed = new Array(stateCount).fill("");       // the move that got us here (F/R/L)
  const finished = new Array(stateCount).fill(false);    // true once a state is fully handled

  // Estimate of the remaining cost: straight-line grid distance (never too high).
  const estimate = (r, c) => Math.abs(r - goal.r) + Math.abs(c - goal.c);

  // Lowest (cost so far + estimate) first; on a tie, prefer the state that got further.
  const open = new MinHeap((a, b) => (a.f !== b.f) ? a.f < b.f : a.g > b.g);
  const startKey = keyOf(start.r, start.c, map.heading);
  bestCost[startKey] = 0;
  open.push({ r: start.r, c: start.c, h: map.heading, g: 0, f: estimate(start.r, start.c) });

  while (open.size > 0) {
    const cur = open.pop();
    const key = keyOf(cur.r, cur.c, cur.h);
    if (finished[key]) continue;          // already handled via a cheaper route
    finished[key] = true;

    // Reached the goal cell (any heading is fine): walk back to build the command string.
    if (cur.r === goal.r && cur.c === goal.c) {
      let moves = "";
      for (let k = key; k !== startKey; k = cameFrom[k]) moves = moveUsed[k] + moves;
      const commands = simplifyTurns(moves);
      return { ok: true, commands, poses: simulate(start, map.heading, commands), cost: cur.g, message: "" };
    }

    const options = [
      { move: "F", r: cur.r + ROW_STEP[cur.h], c: cur.c + COL_STEP[cur.h], h: cur.h, cost: 1 },
      { move: "R", r: cur.r, c: cur.c, h: turnRight(cur.h), cost: penalty },
      { move: "L", r: cur.r, c: cur.c, h: turnLeft(cur.h),  cost: penalty },
    ];
    for (const next of options) {
      if (!isFree(map, next.r, next.c)) continue;   // wall or off the grid
      const nextKey = keyOf(next.r, next.c, next.h);
      const g = cur.g + next.cost;
      if (g < bestCost[nextKey]) {
        bestCost[nextKey] = g;
        cameFrom[nextKey] = key;
        moveUsed[nextKey] = next.move;
        open.push({ r: next.r, c: next.c, h: next.h, g, f: g + estimate(next.r, next.c) });
      }
    }
  }
  return { ok: false, message: "No path found: obstacles block every way to the goal." };
}

// ---------- Custom path helpers ----------

// Clean up typed commands: upper case, ignore spaces / commas / new lines.
// Returns { commands: "FFRL", invalid: "X2" } (invalid = any other characters, each listed once).
function normalizeCommands(text) {
  let commands = "", invalid = "";
  for (const ch of String(text || "").toUpperCase()) {
    if (ch === "F" || ch === "R" || ch === "L") commands += ch;
    else if (/[\s,]/.test(ch)) continue;
    else if (!invalid.includes(ch)) invalid += ch;
  }
  return { commands, invalid };
}

// Play the commands from Start and list every problem.
// problems: [{ step, kind: "off" | "wall", r, c }]  (step counts from 1)
// For "off", (r, c) is the cell the robot drives off the grid from.
function checkRoute(map, commands) {
  const poses = simulate(map.start, map.heading, commands);
  const inside = p => p.r >= 0 && p.r < map.rows && p.c >= 0 && p.c < map.cols;
  const problems = [];
  for (let i = 1; i < poses.length; i++) {
    if (commands[i - 1] !== "F") continue;           // turns stay in the same cell
    const p = poses[i], prev = poses[i - 1];
    if (!inside(p)) {
      if (inside(prev)) problems.push({ step: i, kind: "off", r: prev.r, c: prev.c });
    } else if (map.walls[p.r][p.c]) {
      problems.push({ step: i, kind: "wall", r: p.r, c: p.c });
    }
  }
  const end = poses[poses.length - 1];
  const endsOnGoal = !!map.goal && end.r === map.goal.r && end.c === map.goal.c;
  return { poses, problems, endsOnGoal };
}

// Heading (0-3) that leads from cell a to the next-door cell b, or -1 if b is not next door.
function directionBetween(a, b) {
  for (let h = 0; h < 4; h++) {
    if (a.r + ROW_STEP[h] === b.r && a.c + COL_STEP[h] === b.c) return h;
  }
  return -1;
}

// Turns needed to go from heading `from` to heading `to`: "", "R", "RR" or "L".
function turnsBetween(from, to) {
  return ["", "R", "RR", "L"][(to - from + 4) % 4];
}

// Turn a drawn route (list of cells, first = Start) into commands.
// Returns null if two cells in a row are not next to each other.
function cellsToCommands(heading, cells) {
  let h = heading, commands = "";
  for (let i = 1; i < cells.length; i++) {
    const d = directionBetween(cells[i - 1], cells[i]);
    if (d < 0) return null;
    commands += turnsBetween(h, d) + "F";
    h = d;
  }
  return commands;
}

// Remove the last cell of a route: its F plus the turns just before / after it.
function undoLastCell(commands) {
  return commands.includes("F") ? commands.replace(/[RL]*F[RL]*$/, "") : "";
}

// The cells a route visits, in order (poses after each F, plus the start).
function routeCells(commands, poses) {
  return poses.filter((p, i) => i === 0 || commands[i - 1] === "F");
}
// PLANNER-END


/* =====================================================================
   3. MAP DATA - the one place the current map lives
   ===================================================================== */
function emptyWalls(rows, cols) {
  const walls = [];
  for (let r = 0; r < rows; r++) walls.push(new Array(cols).fill(false));
  return walls;
}

function defaultMap() {
  return { rows: 6, cols: 6, cellCm: 30, walls: emptyWalls(6, 6),
           start: { r: 5, c: 0 }, goal: { r: 0, c: 5 }, heading: 0, turnPenalty: 2,
           pathSource: "auto", customText: "" };
}

function clampSize(n) {
  n = Math.round(Number(n));
  if (!isFinite(n)) n = 6;
  return Math.min(MAX_SIZE, Math.max(MIN_SIZE, n));
}

function sameCell(a, b) { return a && b && a.r === b.r && a.c === b.c; }

let map = defaultMap();
let plan = { ok: false, message: "" };   // result of the latest planPath()
let custom = null;                       // result of the latest checkCustom()

// Change the grid size, keeping obstacles / start / goal that still fit.
function resizeMap(rows, cols) {
  rows = clampSize(rows);
  cols = clampSize(cols);
  const walls = emptyWalls(rows, cols);
  for (let r = 0; r < Math.min(rows, map.rows); r++)
    for (let c = 0; c < Math.min(cols, map.cols); c++)
      walls[r][c] = map.walls[r][c];
  const fits = p => p && p.r < rows && p.c < cols;
  map.rows = rows;
  map.cols = cols;
  map.walls = walls;
  if (!fits(map.start)) map.start = null;
  if (!fits(map.goal)) map.goal = null;
  buildGrid();
  mapChanged();
}

// Map <-> plain JSON data (used for localStorage and export/import).
// Obstacles are stored as text rows: "#" = obstacle, "." = free.
function mapToData() {
  return {
    version: 1,
    rows: map.rows, cols: map.cols, cellCm: map.cellCm,
    heading: HEADING_NAMES[map.heading], turnPenalty: map.turnPenalty,
    start: map.start ? [map.start.r, map.start.c] : null,
    goal: map.goal ? [map.goal.r, map.goal.c] : null,
    grid: map.walls.map(row => row.map(w => (w ? "#" : ".")).join("")),
    pathSource: map.pathSource,      // "auto" or "custom"
    customPath: map.customText,      // the custom commands as typed
  };
}

function mapFromData(d) {
  if (!d || typeof d !== "object") throw new Error("That is not a map.");
  if (!isFinite(Number(d.rows)) || !isFinite(Number(d.cols))) throw new Error("Map needs numbers for rows and cols.");
  const rows = clampSize(d.rows), cols = clampSize(d.cols);
  const walls = emptyWalls(rows, cols);
  if (Array.isArray(d.grid)) {
    d.grid.forEach((line, r) => {
      if (r >= rows || typeof line !== "string") return;
      for (let c = 0; c < Math.min(cols, line.length); c++) walls[r][c] = (line[c] === "#");
    });
  }
  const toCell = p => (Array.isArray(p) && Number.isInteger(p[0]) && Number.isInteger(p[1]) &&
                       p[0] >= 0 && p[0] < rows && p[1] >= 0 && p[1] < cols) ? { r: p[0], c: p[1] } : null;
  const start = toCell(d.start), goal = toCell(d.goal);
  if (start) walls[start.r][start.c] = false;
  if (goal) walls[goal.r][goal.c] = false;
  const heading = Math.max(0, HEADING_NAMES.indexOf(String(d.heading).toUpperCase()));
  const penalty = Number(d.turnPenalty);
  const cellCm = Number(d.cellCm);
  return {
    rows, cols, walls, start, goal, heading,
    turnPenalty: (isFinite(penalty) && penalty >= 0) ? penalty : 2,
    cellCm: (isFinite(cellCm) && cellCm > 0) ? cellCm : 30,
    // Older map files have no custom path: fall back to Auto and an empty path.
    pathSource: d.pathSource === "custom" ? "custom" : "auto",
    customText: typeof d.customPath === "string" ? d.customPath.slice(0, 2000) : "",
  };
}


/* =====================================================================
   4. DRAWING THE GRID
   ===================================================================== */
const $ = id => document.getElementById(id);
const gridEl = $("grid");
let cellEls = [];          // cellEls[r][c] = the <div> for that cell
let robotPoses = null;     // poses of the path last sent to the robot
let robotStep = null;      // how many commands the robot has finished (from /status)

// Arrow pointing in heading h (rotating one arrow avoids emoji look-alikes on phones).
function arrowHtml(symbol, h) {
  return '<span style="transform:rotate(' + (h * 90) + 'deg)">' + symbol + "</span>";
}

// Create the cell <div>s. Only needed when the grid size changes.
function buildGrid() {
  gridEl.innerHTML = "";
  cellEls = [];
  for (let r = 0; r < map.rows; r++) {
    const rowEls = [];
    for (let c = 0; c < map.cols; c++) {
      const div = document.createElement("div");
      div.className = "cell";
      div.dataset.r = r;
      div.dataset.c = c;
      gridEl.appendChild(div);
      rowEls.push(div);
    }
    cellEls.push(rowEls);
  }
  layoutGrid();
}

// Pick a cell size in pixels so the whole grid fits on screen.
function layoutGrid() {
  const wrapWidth = $("gridWrap").clientWidth - 6;
  const maxHeight = Math.max(240, window.innerHeight * 0.7);
  let size = Math.floor(Math.min(wrapWidth / map.cols, maxHeight / map.rows, 60));
  size = Math.max(size, 12);
  gridEl.style.gridTemplateColumns = "repeat(" + map.cols + ", " + size + "px)";
  gridEl.style.gridAutoRows = size + "px";
  gridEl.style.fontSize = Math.round(size * 0.55) + "px";
}

// Paint every cell from the map and the active path (auto or custom).
function render() {
  const route = activeRoute();
  const isCustom = map.pathSource === "custom";
  // Which cells are on the path, and which way the robot leaves each one.
  const exitHeading = {};   // "r,c" -> heading when driving out
  const turnCells = {};     // "r,c" -> true if the robot turns there
  const badCells = {};      // "r,c" -> true for custom-path problems
  for (let i = 0; i < route.commands.length && i < route.poses.length; i++) {
    const p = route.poses[i];
    if (route.commands[i] === "F") exitHeading[p.r + "," + p.c] = p.h;
    else turnCells[p.r + "," + p.c] = true;
  }
  route.problems.forEach(pr => { badCells[pr.r + "," + pr.c] = true; });
  // In custom mode, outline the cell where the route ends (where drawing continues).
  const last = route.poses[route.poses.length - 1];
  const endKey = (isCustom && last) ? last.r + "," + last.c : "";
  let here = null;
  if (robotPoses && robotStep !== null && robotStep < robotPoses.length) here = robotPoses[robotStep];

  for (let r = 0; r < map.rows; r++) {
    for (let c = 0; c < map.cols; c++) {
      const key = r + "," + c;
      let cls = "cell", html = "";
      if (map.walls[r][c]) {
        cls += " wall";
      } else if (sameCell(map.start, { r, c })) {
        cls += " start";
        html = arrowHtml("&#9650;", map.heading);           // triangle = robot facing
      } else if (sameCell(map.goal, { r, c })) {
        cls += " goal";
        html = "G";
      } else if (key in exitHeading || turnCells[key]) {
        if (isCustom) cls += turnCells[key] ? " cturn" : " cpath";
        else cls += turnCells[key] ? " turn" : " path";
        if (key in exitHeading) html = arrowHtml("&uarr;", exitHeading[key]);
      }
      if (badCells[key]) cls += " bad";
      if (key === endKey) cls += " end";
      if (here && here.r === r && here.c === c) cls += " here";
      const el = cellEls[r][c];
      if (el.className !== cls) el.className = cls;
      if (el.innerHTML !== html) el.innerHTML = html;
    }
  }

  // Keep the buttons and inputs in step with the map.
  document.querySelectorAll("#headingButtons button").forEach(b =>
    b.classList.toggle("active", Number(b.dataset.heading) === map.heading));
  $("rowsInput").value = map.rows;
  $("colsInput").value = map.cols;
  $("cellInput").value = map.cellCm;
  if (document.activeElement !== $("penaltyInput")) $("penaltyInput").value = map.turnPenalty;
  document.querySelectorAll("#sourceButtons button").forEach(b =>
    b.classList.toggle("active", b.dataset.source === map.pathSource));
  $("customBox").hidden = !isCustom;
  $("penaltyBox").hidden = isCustom;
  if (document.activeElement !== $("customText")) $("customText").value = map.customText;
}


/* =====================================================================
   5. EDITING WITH TAP / CLICK / DRAG (pointer events = mouse + touch)
   ===================================================================== */
let editMode = "wall";      // "wall" | "start" | "goal" | "erase" | "draw"
let painting = false;       // true while a finger / mouse button is held down
let paintValue = true;      // obstacle mode: true = adding obstacles, false = removing
let lastCellKey = "";
let drawing = false;        // draw mode: finger / mouse is down
let pendingUndo = false;    // draw mode: pressed on the route end - undo if it was only a tap

function cellAt(x, y) {
  const el = document.elementFromPoint(x, y);
  const cell = el && el.closest(".cell");
  if (!cell || !gridEl.contains(cell)) return null;
  return { r: Number(cell.dataset.r), c: Number(cell.dataset.c) };
}

function applyTool(r, c, firstTap) {
  const here = { r, c };
  if (editMode === "wall") {
    if (sameCell(map.start, here) || sameCell(map.goal, here)) return;   // never cover start/goal
    map.walls[r][c] = paintValue;
  } else if (editMode === "erase") {
    map.walls[r][c] = false;
    if (sameCell(map.start, here)) map.start = null;
    if (sameCell(map.goal, here)) map.goal = null;
  } else if (editMode === "start") {
    if (!firstTap) return;
    if (sameCell(map.start, here)) {
      map.heading = turnRight(map.heading);                 // tap start again = rotate
    } else {
      map.walls[r][c] = false;
      if (sameCell(map.goal, here)) map.goal = null;
      map.start = here;
    }
  } else if (editMode === "goal") {
    if (!firstTap) return;
    map.walls[r][c] = false;
    if (sameCell(map.start, here)) map.start = null;
    map.goal = here;
  }
  mapChanged();
}

// ---- Draw mode: build the custom path by tapping cells next to the route end ----
function setDrawNote(kind, text) { $("drawNote").className = "msg " + kind; $("drawNote").textContent = text; }

// Replace the custom path (also used by the text box buttons).
function setCustomPath(text) {
  map.customText = text;
  $("customText").value = text;
  mapChanged();
}

// The current custom route: cleaned-up commands, poses and visited cells.
function customRouteNow() {
  const commands = normalizeCommands(map.customText).commands;
  const poses = simulate(map.start, map.heading, commands);
  return { commands, poses, cells: routeCells(commands, poses) };
}

// Try to extend the route to (r, c). Returns true if it did.
function drawTo(r, c) {
  const route = customRouteNow();
  const end = route.poses[route.poses.length - 1];
  const dir = directionBetween(end, { r, c });
  if (dir < 0) { setDrawNote("warn", "Tap a cell right next to the route end (dashed outline)."); return false; }
  if (map.walls[r][c]) { setDrawNote("warn", "That cell is an obstacle."); return false; }
  setDrawNote("", "");
  setCustomPath(route.commands + turnsBetween(end.h, dir) + "F");
  return true;
}

function undoDraw() {
  setDrawNote("", "");
  setCustomPath(undoLastCell(normalizeCommands(map.customText).commands));
}

function drawPointerDown(cell) {
  if (map.pathSource !== "custom") { map.pathSource = "custom"; mapChanged(); }
  if (!map.start) { setDrawNote("err", "Place a Start cell first - the path starts there."); return; }
  const route = customRouteNow();
  drawing = true;
  // Pressing on the route end: undo if this turns out to be a tap, keep drawing if it is a drag.
  pendingUndo = route.commands.length > 0 && sameCell(route.cells[route.cells.length - 1], cell);
  if (!pendingUndo && !sameCell(route.cells[route.cells.length - 1], cell)) drawTo(cell.r, cell.c);
}

function drawPointerMove(cell) {
  pendingUndo = false;
  const cells = customRouteNow().cells;
  if (cells.length >= 2 && sameCell(cells[cells.length - 2], cell)) undoDraw();   // dragged back = undo
  else if (directionBetween(cells[cells.length - 1], cell) >= 0) drawTo(cell.r, cell.c);
}

gridEl.addEventListener("pointerdown", e => {
  if (e.pointerType === "mouse" && e.button !== 0) return;  // left mouse button only
  const cell = cellAt(e.clientX, e.clientY);
  if (!cell) return;
  e.preventDefault();
  try { gridEl.setPointerCapture(e.pointerId); } catch (err) { /* not important */ }
  lastCellKey = cell.r + "," + cell.c;
  if (editMode === "draw") { drawPointerDown(cell); return; }
  painting = (editMode === "wall" || editMode === "erase");
  if (editMode === "wall") paintValue = !map.walls[cell.r][cell.c];   // first cell decides add/remove
  applyTool(cell.r, cell.c, true);
});

gridEl.addEventListener("pointermove", e => {
  if (!painting && !drawing) return;
  const cell = cellAt(e.clientX, e.clientY);
  if (!cell) return;
  const key = cell.r + "," + cell.c;
  if (key === lastCellKey) return;
  lastCellKey = key;
  if (drawing) drawPointerMove(cell);
  else applyTool(cell.r, cell.c, false);
});

gridEl.addEventListener("pointerup", () => {
  if (drawing && pendingUndo) undoDraw();   // it was a tap on the last cell
  drawing = false;
  pendingUndo = false;
  painting = false;
});
["pointercancel", "lostpointercapture"].forEach(type =>
  gridEl.addEventListener(type, () => { painting = false; drawing = false; pendingUndo = false; }));

document.querySelectorAll("#modeButtons button").forEach(btn => {
  btn.addEventListener("click", () => {
    editMode = btn.dataset.mode;
    document.querySelectorAll("#modeButtons button").forEach(b => b.classList.toggle("active", b === btn));
    if (editMode === "draw" && map.pathSource !== "custom") { map.pathSource = "custom"; mapChanged(); }
  });
});

document.querySelectorAll("#headingButtons button").forEach(btn => {
  btn.addEventListener("click", () => { map.heading = Number(btn.dataset.heading); mapChanged(); });
});

$("clearBtn").addEventListener("click", () => {
  if (!confirm("Remove all obstacles, the start and the goal?")) return;
  map.walls = emptyWalls(map.rows, map.cols);
  map.start = null;
  map.goal = null;
  map.customText = "";
  mapChanged();
});


/* =====================================================================
   6. RE-PLAN AND SHOW THE RESULT (runs after every map change)
   ===================================================================== */
function mapChanged() {
  plan = planPath(map);
  custom = checkCustom();
  render();
  showPlan();
  saveToBrowser();
}

// Check the custom path (typed or drawn) against the current map.
function checkCustom() {
  const { commands, invalid } = normalizeCommands(map.customText);
  if (!map.start) return { commands, invalid, noStart: true, poses: [], problems: [], endsOnGoal: false };
  return Object.assign({ commands, invalid, noStart: false }, checkRoute(map, commands));
}

// The path that Go would send right now: { commands, poses, problems }.
function activeRoute() {
  if (map.pathSource === "custom") return custom;
  return plan.ok ? { commands: plan.commands, poses: plan.poses, problems: [] }
                 : { commands: "", poses: [], problems: [] };
}

// Can the custom path be sent? (Problems are allowed, but Go asks first.)
function customSendable() {
  return !custom.noStart && !custom.invalid && custom.commands.length > 0;
}

// One sentence about the first custom-path problem.
function describeProblems(problems) {
  const p = problems[0];
  let text = "Step " + p.step + (p.kind === "off" ? " drives off the grid" : " drives into an obstacle");
  if (problems.length > 1) text += " (+" + (problems.length - 1) + " more problem" + (problems.length > 2 ? "s" : "") + ")";
  return text + ". Marked in red.";
}

function showCustomMessage(msg) {
  const goalNote = !map.goal ? "" : custom.endsOnGoal ? " Ends on the Goal." : " Does not end on the Goal.";
  if (custom.noStart) { msg.className = "msg err"; msg.textContent = "Place a Start cell - the custom path starts there."; }
  else if (custom.invalid) { msg.className = "msg err"; msg.textContent = "Not allowed: " + custom.invalid.split("").join(" ") + "  - use only F, R and L."; }
  else if (!custom.commands) { msg.className = "msg warn"; msg.textContent = "Type commands, or pick Draw mode and tap cells from the Start."; }
  else if (custom.problems.length) { msg.className = "msg err"; msg.textContent = "Warning: " + describeProblems(custom.problems) + goalNote; }
  else { msg.className = "msg ok"; msg.textContent = "Custom path stays on the grid." + goalNote; }
}

function showPlan() {
  const msg = $("planMsg");
  const isCustom = map.pathSource === "custom";
  const commands = activeRoute().commands;
  $("cmd").textContent = commands || "-";
  const s = commandStats(commands);
  $("statForward").textContent = s.forward + "  (" + (s.forward * map.cellCm) + " cm)";
  $("statTurns").textContent = s.turns + "  (R " + s.right + ", L " + s.left + ")";
  $("statMoves").textContent = s.moves;
  $("statTime").textContent = (s.timeMs / 1000).toFixed(1) + " s";
  if (isCustom) showCustomMessage(msg);
  else if (!plan.ok) { msg.className = "msg err"; msg.textContent = plan.message; }
  else if (plan.message) { msg.className = "msg warn"; msg.textContent = plan.message; }
  else { msg.className = "msg ok"; msg.textContent = "Path found."; }
  $("goBtn").disabled = !canGo();
  $("copyBtn").disabled = !commands;
}

function canGo() {
  return map.pathSource === "custom" ? customSendable() : (plan.ok && plan.commands.length > 0);
}

// ---- Path source toggle and custom path box ----
document.querySelectorAll("#sourceButtons button").forEach(btn => {
  btn.addEventListener("click", () => { map.pathSource = btn.dataset.source; mapChanged(); });
});
$("customText").addEventListener("input", () => { map.customText = $("customText").value; mapChanged(); });
$("undoBtn").addEventListener("click", undoDraw);
$("clearPathBtn").addEventListener("click", () => { setDrawNote("", ""); setCustomPath(""); });
$("useAutoBtn").addEventListener("click", () => {
  if (plan.ok) { setDrawNote("", ""); setCustomPath(plan.commands); }
  else setDrawNote("warn", "There is no best path to copy: " + plan.message);
});

$("penaltyInput").addEventListener("input", () => {
  const v = Number($("penaltyInput").value);
  if (isFinite(v) && v >= 0) { map.turnPenalty = v; mapChanged(); }
});

// Copy text. navigator.clipboard only works on https or a local file, so on the
// robot's plain http page we fall back to the older "select + copy" trick.
async function copyText(text) {
  try {
    if (navigator.clipboard && window.isSecureContext) { await navigator.clipboard.writeText(text); return true; }
  } catch (err) { /* try the fallback below */ }
  const ta = document.createElement("textarea");
  ta.value = text;
  ta.setAttribute("readonly", "");
  ta.style.position = "fixed";
  ta.style.opacity = "0";
  document.body.appendChild(ta);
  ta.select();
  ta.setSelectionRange(0, text.length);
  let ok = false;
  try { ok = document.execCommand("copy"); } catch (err) { ok = false; }
  ta.remove();
  return ok;
}

$("copyBtn").addEventListener("click", async () => {
  const btn = $("copyBtn");
  const ok = await copyText(activeRoute().commands || "");
  btn.textContent = ok ? "Copied!" : "Copy failed - select the text";
  setTimeout(() => { btn.textContent = "Copy commands"; }, 1500);
});


/* =====================================================================
   7. TALKING TO THE ROBOT (HTTP: POST /run, POST /stop, GET /status)
   ===================================================================== */
const openedAsFile = location.protocol === "file:";

// Build the full URL. Empty address = same place this page came from (the ESP32).
function robotUrl(path) {
  let base = $("addrInput").value.trim();
  if (base && !/^https?:\/\//i.test(base)) base = "http://" + base;
  return base.replace(/\/+$/, "") + path;
}

// fetch() with a time limit. Returns { ok, status, text } or throws on network trouble.
async function robotRequest(path, options, timeoutMs) {
  if (openedAsFile && !$("addrInput").value.trim()) {
    throw new Error("NEED_ADDRESS");
  }
  const controller = new AbortController();
  const timer = setTimeout(() => controller.abort(), timeoutMs);
  try {
    const res = await fetch(robotUrl(path), Object.assign({ cache: "no-store", signal: controller.signal }, options));
    const text = (await res.text()).trim();
    return { ok: res.ok, status: res.status, text };
  } finally {
    clearTimeout(timer);
  }
}

function explainError(err) {
  if (err.message === "NEED_ADDRESS") return "This page is opened as a file: type http://192.168.4.1 in Robot address.";
  if (err.name === "AbortError") return "The robot did not answer in time. Are you connected to the robot's Wi-Fi?";
  return "Could not reach the robot. Not connected to the robot's Wi-Fi?";
}

function setRobotMsg(kind, text) {
  const el = $("robotMsg");
  el.className = "msg " + kind;
  el.textContent = text;
}

$("goBtn").addEventListener("click", async () => {
  if (!canGo()) { setRobotMsg("err", "There is no path to send."); return; }
  const route = activeRoute();
  // A custom path with problems might crash the robot: ask first.
  if (route.problems.length &&
      !confirm("Custom path problem: " + describeProblems(route.problems) + "\n\nSend it to the robot anyway?")) {
    setRobotMsg("warn", "Not sent.");
    return;
  }
  const commands = route.commands;
  const poses = route.poses;
  setRobotMsg("", "Sending " + commands + " ...");
  $("goBtn").disabled = true;
  try {
    const res = await robotRequest("/run",
      { method: "POST", headers: { "Content-Type": "text/plain" }, body: commands },
      REQUEST_TIMEOUT_MS);
    if (res.ok) {
      setRobotMsg("ok", "Robot accepted the path" + (res.text ? ": " + res.text : "."));
      robotPoses = poses;
      startPolling();
    } else {
      setRobotMsg("err", "Robot refused (HTTP " + res.status + ")" + (res.text ? ": " + res.text : "."));
    }
  } catch (err) {
    setRobotMsg("err", explainError(err));
  } finally {
    $("goBtn").disabled = !canGo();
  }
});

$("stopBtn").addEventListener("click", async () => {
  setRobotMsg("", "Sending stop ...");
  try {
    const res = await robotRequest("/stop", { method: "POST" }, REQUEST_TIMEOUT_MS);
    if (res.ok) setRobotMsg("ok", "Robot stopped" + (res.text ? ": " + res.text : "."));
    else setRobotMsg("err", "Stop failed (HTTP " + res.status + ")" + (res.text ? ": " + res.text : "."));
    if (polling) fetchStatus().then(showStatus).catch(() => {}); else startPolling();   // refresh progress now
  } catch (err) {
    setRobotMsg("err", explainError(err) + " If it is still moving, switch it off.");
  }
});

$("statusBtn").addEventListener("click", async () => {
  setRobotMsg("", "Checking ...");
  try {
    const s = await fetchStatus();
    setRobotMsg("ok", "Connected. Robot is " + (s.state || "unknown") + ".");
    showStatus(s);
  } catch (err) {
    setRobotMsg("err", err.message === "BAD_STATUS" ? "Robot answered, but /status was not valid JSON." : explainError(err));
  }
});

// ---- Live progress from GET /status (optional; fails quietly) ----
let polling = false;
let pollFailures = 0;

async function fetchStatus() {
  const res = await robotRequest("/status", { method: "GET" }, STATUS_TIMEOUT_MS);
  if (!res.ok) throw new Error("BAD_STATUS");
  try { return JSON.parse(res.text); } catch (err) { throw new Error("BAD_STATUS"); }
}

function startPolling() {
  pollFailures = 0;
  if (polling) return;
  polling = true;
  pollOnce();
}

async function pollOnce() {
  try {
    const s = await fetchStatus();
    pollFailures = 0;
    showStatus(s);
    if (s.state !== "running") { polling = false; return; }   // robot finished - stop asking
  } catch (err) {
    pollFailures++;
    if (pollFailures >= 3) {                                  // give up quietly
      polling = false;
      $("progressText").textContent = "Live progress not available.";
      return;
    }
  }
  setTimeout(pollOnce, POLL_EVERY_MS);
}

function showStatus(s) {
  const step = Number(s.step), total = Number(s.total);
  const haveNumbers = isFinite(step) && isFinite(total) && total > 0;
  $("progressBox").hidden = false;
  $("progressBar").max = haveNumbers ? total : 1;
  $("progressBar").value = haveNumbers ? Math.min(step, total) : 0;
  let text = "Robot: " + (s.state || "unknown");
  if (haveNumbers) text += " - step " + step + " of " + total;
  $("progressText").textContent = text;
  // Show where the robot should be now (only if the robot runs the path we sent).
  robotStep = (s.state === "running" && haveNumbers && robotPoses && total === robotPoses.length - 1) ? step : null;
  render();
}

$("addrInput").addEventListener("change", () => {
  try { localStorage.setItem(ADDR_KEY, $("addrInput").value.trim()); } catch (err) { /* no storage */ }
});


/* =====================================================================
   8. MAP SIZE CONTROLS
   ===================================================================== */
$("rowsInput").addEventListener("change", () => resizeMap($("rowsInput").value, map.cols));
$("colsInput").addEventListener("change", () => resizeMap(map.rows, $("colsInput").value));

$("cellInput").addEventListener("change", () => {
  const v = Number($("cellInput").value);
  if (isFinite(v) && v > 0) map.cellCm = v;
  mapChanged();
});

$("roomBtn").addEventListener("click", () => {
  const w = Number($("roomW").value), l = Number($("roomL").value);
  const msg = $("sizeMsg");
  if (!(w > 0 && l > 0)) { msg.className = "msg err"; msg.textContent = "Enter the room width and length in cm."; return; }
  // Only whole cells count (a part-cell at the edge is too small).
  const cols = Math.floor(w / map.cellCm), rows = Math.floor(l / map.cellCm);
  resizeMap(rows, cols);
  let text = "Room " + w + " x " + l + " cm = " + map.cols + " columns x " + map.rows + " rows of " + map.cellCm + " cm.";
  if (cols !== map.cols || rows !== map.rows) text += " (Limited to " + MIN_SIZE + "-" + MAX_SIZE + " cells per side.)";
  msg.className = "msg ok";
  msg.textContent = text;
});


/* =====================================================================
   9. SAVE / LOAD (browser storage + JSON export / import)
   ===================================================================== */
function saveToBrowser() {
  try { localStorage.setItem(STORAGE_KEY, JSON.stringify(mapToData())); } catch (err) { /* no storage - fine */ }
}

function loadFromBrowser() {
  try {
    const text = localStorage.getItem(STORAGE_KEY);
    if (text) map = mapFromData(JSON.parse(text));
  } catch (err) { map = defaultMap(); }
  try { $("addrInput").value = localStorage.getItem(ADDR_KEY) || ""; } catch (err) { /* no storage */ }
}

function setIoMsg(kind, text) { $("ioMsg").className = "msg " + kind; $("ioMsg").textContent = text; }

function mapJsonText() { return JSON.stringify(mapToData(), null, 2); }

function importText(text) {
  try {
    map = mapFromData(JSON.parse(text));
    buildGrid();
    mapChanged();
    setIoMsg("ok", "Map loaded (" + map.rows + " x " + map.cols + ").");
  } catch (err) {
    setIoMsg("err", "Could not load map: " + err.message);
  }
}

$("exportBtn").addEventListener("click", () => {
  $("jsonBox").value = mapJsonText();
  setIoMsg("ok", "Copy this text to save the map.");
});
$("importBtn").addEventListener("click", () => importText($("jsonBox").value));

$("downloadBtn").addEventListener("click", () => {
  const blob = new Blob([mapJsonText()], { type: "application/json" });
  const a = document.createElement("a");
  a.href = URL.createObjectURL(blob);
  a.download = "agv-map.json";
  document.body.appendChild(a);
  a.click();
  a.remove();
  setTimeout(() => URL.revokeObjectURL(a.href), 1000);
});

$("fileBtn").addEventListener("click", () => $("fileInput").click());
$("fileInput").addEventListener("change", () => {
  const file = $("fileInput").files[0];
  if (!file) return;
  const reader = new FileReader();
  reader.onload = () => { $("jsonBox").value = reader.result; importText(reader.result); };
  reader.onerror = () => setIoMsg("err", "Could not read that file.");
  reader.readAsText(file);
  $("fileInput").value = "";
});


/* =====================================================================
   10. START UP
   ===================================================================== */
loadFromBrowser();
$("addrHint").textContent = openedAsFile
  ? "Opened as a local file: join the robot's Wi-Fi and type http://192.168.4.1 above."
  : "Leave empty when this page is served by the robot.";
buildGrid();
mapChanged();
window.addEventListener("resize", layoutGrid);
</script>
</body>
</html>

)AGVHTML";
