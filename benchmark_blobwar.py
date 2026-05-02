#!/usr/bin/env python3
import argparse
import csv
import itertools
import os
import pathlib
import re
import subprocess
import time
from collections import defaultdict


ALGOS = {
    "glouton": "./launchStrategy_glouton",
    "minimax": "./launchStrategy_minimax",
    "alphabeta0": "./launchStrategy_alphabeta0",
    "alphabeta_final": "./launchStrategy",
}

SAVE_RE = re.compile(r"SAVE MOVE:\s*(\d+),(\d+)\s*to\s*(\d+),(\d+)")
TRACE_RE = re.compile(r"BW_TRACE\s+(.*)")


def parse_args():
    parser = argparse.ArgumentParser(description="Run Blobwar AI benchmarks and generate CSV/graphs.")
    parser.add_argument("--timeout", type=float, default=2.0, help="Timeout per AI move in seconds.")
    parser.add_argument("--games-per-pair", type=int, default=1, help="Repetitions for each ordered matchup.")
    parser.add_argument("--max-turns", type=int, default=300, help="Draw limit in played turns.")
    parser.add_argument("--map", default="standard", help="Board map name from data/boards.")
    parser.add_argument("--output-dir", default="benchmark/results", help="Directory for CSV and PNG files.")
    parser.add_argument("--algos", default=",".join(ALGOS.keys()), help="Comma-separated algo names.")
    parser.add_argument("--no-build", action="store_true", help="Skip make -B before running.")
    return parser.parse_args()


def load_holes(map_name):
    path = pathlib.Path("data") / "boards" / map_name
    lines = path.read_text().splitlines()
    if len(lines) != 8 or any(len(line) < 8 for line in lines):
        raise ValueError(f"invalid board file: {path}")
    return [[lines[x][y] == "x" for y in range(8)] for x in range(8)]


def initial_blobs(holes):
    blobs = [[-1 for _ in range(8)] for _ in range(8)]
    for x, y, player in [(0, 0, 0), (7, 0, 0), (0, 7, 1), (7, 7, 1)]:
        if holes[x][y]:
            raise ValueError("standard initial position is on a hole")
        blobs[x][y] = player
    return blobs


def serialize_holes(holes):
    return "".join("O" if holes[x][y] else "X" for x in range(8) for y in range(8))


def serialize_blobs(blobs):
    chars = []
    for x in range(8):
        for y in range(8):
            owner = blobs[x][y]
            if owner == 0:
                chars.append("r")
            elif owner == 1:
                chars.append("b")
            else:
                chars.append("x")
    return "".join(chars)


def inside(x, y):
    return 0 <= x < 8 and 0 <= y < 8


def valid_moves(blobs, holes, player):
    moves = []
    for ox in range(8):
        for oy in range(8):
            if blobs[ox][oy] != player:
                continue
            for nx in range(max(0, ox - 2), min(7, ox + 2) + 1):
                for ny in range(max(0, oy - 2), min(7, oy + 2) + 1):
                    if nx == ox and ny == oy:
                        continue
                    if holes[nx][ny] or blobs[nx][ny] != -1:
                        continue
                    moves.append((ox, oy, nx, ny))
    return moves


def apply_move(blobs, move, player):
    ox, oy, nx, ny = move
    dist = max(abs(nx - ox), abs(ny - oy))
    if dist == 2:
        blobs[ox][oy] = -1
    blobs[nx][ny] = player

    for dx in range(-1, 2):
        for dy in range(-1, 2):
            x = nx + dx
            y = ny + dy
            if inside(x, y) and blobs[x][y] != -1 and blobs[x][y] != player:
                blobs[x][y] = player


def score(blobs):
    counts = [0, 0]
    for x in range(8):
        for y in range(8):
            if blobs[x][y] in (0, 1):
                counts[blobs[x][y]] += 1
    return counts


def winner_from_score(blobs):
    s0, s1 = score(blobs)
    if s0 > s1:
        return 0
    if s1 > s0:
        return 1
    return -1


def parse_trace(output):
    traces = TRACE_RE.findall(output)
    if not traces:
        return {"depth": 0, "nodes": 0, "cutoffs": 0}

    data = {}
    for token in traces[-1].split():
        if "=" not in token:
            continue
        key, value = token.split("=", 1)
        data[key] = value

    return {
        "depth": int(data.get("depth", 0)),
        "nodes": int(data.get("nodes", 0)),
        "cutoffs": int(data.get("cutoffs", 0)),
    }


def parse_saved_move(output):
    saves = SAVE_RE.findall(output)
    if not saves:
        return None
    return tuple(int(v) for v in saves[-1])


def run_algo(algo, blobs, holes_serialized, player, timeout):
    command = [ALGOS[algo], serialize_blobs(blobs), holes_serialized, str(player)]
    started = time.perf_counter()
    env = os.environ.copy()
    env["BLOBWAR_BENCHMARK"] = "1"
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
    timed_out = False

    try:
        output, _ = proc.communicate(timeout=timeout)
    except subprocess.TimeoutExpired:
        timed_out = True
        proc.terminate()
        try:
            output, _ = proc.communicate(timeout=0.25)
        except subprocess.TimeoutExpired:
            proc.kill()
            output, _ = proc.communicate()

    elapsed_ms = (time.perf_counter() - started) * 1000.0
    trace = parse_trace(output)
    move = parse_saved_move(output)
    return move, trace, elapsed_ms, timed_out


def play_game(game_id, algo0, algo1, holes, timeout, max_turns, map_name):
    blobs = initial_blobs(holes)
    holes_serialized = serialize_holes(holes)
    algos_by_player = [algo0, algo1]
    move_rows = []
    current = 0
    turns = 0
    passes = 0
    invalid_by = ""

    while turns < max_turns:
        s0, s1 = score(blobs)
        if s0 == 0 or s1 == 0:
            break

        legal = valid_moves(blobs, holes, current)
        if not legal:
            passes += 1
            if passes >= 2:
                break
            current = 1 - current
            continue

        passes = 0
        algo = algos_by_player[current]
        move, trace, elapsed_ms, timed_out = run_algo(algo, blobs, holes_serialized, current, timeout)
        fallback = False

        if move not in legal:
            fallback = True
            if move is not None:
                invalid_by = algo
                break
            move = legal[0]

        apply_move(blobs, move, current)
        s0, s1 = score(blobs)
        move_rows.append({
            "game_id": game_id,
            "map": map_name,
            "turn": turns,
            "player": current,
            "algo": algo,
            "opponent_algo": algos_by_player[1 - current],
            "ox": move[0],
            "oy": move[1],
            "nx": move[2],
            "ny": move[3],
            "time_ms": f"{elapsed_ms:.3f}",
            "timeout": int(timed_out),
            "fallback": int(fallback),
            "depth": trace["depth"],
            "nodes": trace["nodes"],
            "cutoffs": trace["cutoffs"],
            "score0": s0,
            "score1": s1,
        })

        turns += 1
        current = 1 - current

    if invalid_by:
        winner = 1 - algos_by_player.index(invalid_by)
    else:
        winner = winner_from_score(blobs)

    s0, s1 = score(blobs)
    game_row = {
        "game_id": game_id,
        "map": map_name,
        "algo0": algo0,
        "algo1": algo1,
        "winner": winner,
        "winner_algo": "" if winner == -1 else algos_by_player[winner],
        "score0": s0,
        "score1": s1,
        "turns": turns,
        "invalid_by": invalid_by,
    }
    return game_row, move_rows


def write_csv(path, rows, fieldnames):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def mean(values):
    values = list(values)
    return sum(values) / len(values) if values else 0.0


def generate_graphs(output_dir, algos, game_rows, move_rows):
    (output_dir / "matplotlib").mkdir(parents=True, exist_ok=True)
    os.environ.setdefault("MPLCONFIGDIR", str(output_dir / "matplotlib"))

    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        print("matplotlib is not installed; CSV files were generated but graphs were skipped.")
        return

    graph_dir = output_dir / "graphs"
    graph_dir.mkdir(parents=True, exist_ok=True)

    by_algo = {algo: [] for algo in algos}
    for row in move_rows:
        by_algo[row["algo"]].append(row)

    xs = list(range(len(algos)))

    avg_times = [mean(float(row["time_ms"]) for row in by_algo[algo]) for algo in algos]
    fig, ax = plt.subplots(figsize=(9, 5))
    ax.bar(xs, avg_times)
    ax.set_xticks(xs)
    ax.set_xticklabels(algos, rotation=20, ha="right")
    ax.set_ylabel("Temps moyen par coup (ms)")
    ax.set_title("Temps moyen par coup")
    fig.tight_layout()
    fig.savefig(graph_dir / "avg_time_per_move.png", dpi=160)
    plt.close(fig)

    avg_depths = [mean(int(row["depth"]) for row in by_algo[algo]) for algo in algos]
    max_depths = [max([int(row["depth"]) for row in by_algo[algo]] or [0]) for algo in algos]
    fig, ax = plt.subplots(figsize=(9, 5))
    ax.bar(xs, avg_depths)
    for x, value in zip(xs, max_depths):
        ax.text(x, avg_depths[x], f"max {value}", ha="center", va="bottom", fontsize=8)
    ax.set_xticks(xs)
    ax.set_xticklabels(algos, rotation=20, ha="right")
    ax.set_ylabel("Profondeur moyenne atteinte")
    ax.set_title("Profondeur atteinte")
    fig.tight_layout()
    fig.savefig(graph_dir / "depth_reached.png", dpi=160)
    plt.close(fig)

    avg_nodes = [mean(int(row["nodes"]) for row in by_algo[algo]) for algo in algos]
    avg_cutoffs = [mean(int(row["cutoffs"]) for row in by_algo[algo]) for algo in algos]
    fig, axes = plt.subplots(1, 2, figsize=(12, 5))
    axes[0].bar(xs, avg_nodes)
    axes[0].set_xticks(xs)
    axes[0].set_xticklabels(algos, rotation=20, ha="right")
    axes[0].set_ylabel("Noeuds moyens par coup")
    axes[0].set_title("Noeuds explores")
    axes[1].bar(xs, avg_cutoffs)
    axes[1].set_xticks(xs)
    axes[1].set_xticklabels(algos, rotation=20, ha="right")
    axes[1].set_ylabel("Coupures moyennes par coup")
    axes[1].set_title("Coupures alpha-beta")
    fig.tight_layout()
    fig.savefig(graph_dir / "nodes_and_cutoffs.png", dpi=160)
    plt.close(fig)

    points = defaultdict(float)
    games = defaultdict(int)
    for row in game_rows:
        a0 = row["algo0"]
        a1 = row["algo1"]
        winner = int(row["winner"])
        games[(a0, a1)] += 1
        games[(a1, a0)] += 1
        if winner == 0:
            points[(a0, a1)] += 1.0
        elif winner == 1:
            points[(a1, a0)] += 1.0
        else:
            points[(a0, a1)] += 0.5
            points[(a1, a0)] += 0.5

    matrix = []
    for row_algo in algos:
        line = []
        for col_algo in algos:
            if row_algo == col_algo:
                line.append(0.5)
            else:
                total = games[(row_algo, col_algo)]
                line.append(points[(row_algo, col_algo)] / total if total else 0.0)
        matrix.append(line)

    fig, ax = plt.subplots(figsize=(8, 7))
    image = ax.imshow(matrix, vmin=0.0, vmax=1.0, cmap="viridis")
    ax.set_xticks(xs)
    ax.set_xticklabels(algos, rotation=30, ha="right")
    ax.set_yticks(xs)
    ax.set_yticklabels(algos)
    ax.set_title("Win-rate ligne contre colonne")
    for i, row_algo in enumerate(algos):
        for j, _ in enumerate(algos):
            label = "-" if i == j else f"{matrix[i][j] * 100:.0f}%"
            ax.text(j, i, label, ha="center", va="center", color="white")
    fig.colorbar(image, ax=ax, label="Win-rate")
    fig.tight_layout()
    fig.savefig(graph_dir / "winrate_matrix.png", dpi=160)
    plt.close(fig)


def main():
    args = parse_args()
    selected_algos = [name.strip() for name in args.algos.split(",") if name.strip()]
    unknown = [name for name in selected_algos if name not in ALGOS]
    if unknown:
        raise SystemExit(f"Unknown algos: {', '.join(unknown)}")
    if len(selected_algos) < 2:
        raise SystemExit("Select at least two algos.")

    if not args.no_build:
        subprocess.run(["make", "-B"], check=True)

    output_dir = pathlib.Path(args.output_dir)
    holes = load_holes(args.map)
    game_rows = []
    move_rows = []
    game_id = 0

    for algo_a, algo_b in itertools.combinations(selected_algos, 2):
        for first, second in [(algo_a, algo_b), (algo_b, algo_a)]:
            for _ in range(args.games_per_pair):
                print(f"[game {game_id}] {first} vs {second}")
                game_row, rows = play_game(
                    game_id=game_id,
                    algo0=first,
                    algo1=second,
                    holes=holes,
                    timeout=args.timeout,
                    max_turns=args.max_turns,
                    map_name=args.map,
                )
                game_rows.append(game_row)
                move_rows.extend(rows)
                game_id += 1

    write_csv(
        output_dir / "blobwar_games.csv",
        game_rows,
        ["game_id", "map", "algo0", "algo1", "winner", "winner_algo", "score0", "score1", "turns", "invalid_by"],
    )
    write_csv(
        output_dir / "blobwar_moves.csv",
        move_rows,
        [
            "game_id", "map", "turn", "player", "algo", "opponent_algo",
            "ox", "oy", "nx", "ny", "time_ms", "timeout", "fallback",
            "depth", "nodes", "cutoffs", "score0", "score1",
        ],
    )
    generate_graphs(output_dir, selected_algos, game_rows, move_rows)
    print(f"Results written to {output_dir}")


if __name__ == "__main__":
    main()
