from __future__ import annotations

import argparse
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable


WORDS = ("dad", "bad", "bed", "had", "saw", "see", "sad", "bee")
START = "bad"
GOAL = "see"


@dataclass
class SearchNode:
    node_id: int
    word: str
    parent: int | None
    depth: int
    children: list[int] = field(default_factory=list)


@dataclass
class Event:
    text: str
    visible_nodes: tuple[int, ...]
    active_stack: tuple[int, ...]
    solution_nodes: tuple[int, ...] = ()


def ordered_word_edge(a: str, b: str) -> tuple[str, str]:
    return (a, b) if a <= b else (b, a)


def differs_by_one_letter(a: str, b: str) -> bool:
    return len(a) == len(b) and sum(c1 != c2 for c1, c2 in zip(a, b)) == 1


def build_transition_graph(words: Iterable[str]) -> dict[str, list[str]]:
    ordered = tuple(words)
    return {
        word: [other for other in ordered if other != word and differs_by_one_letter(word, other)]
        for word in ordered
    }


def transition_edges(graph: dict[str, list[str]]) -> list[tuple[str, str]]:
    seen: set[tuple[str, str]] = set()
    edges: list[tuple[str, str]] = []
    for a, neighbors in graph.items():
        for b in neighbors:
            key = ordered_word_edge(a, b)
            if key not in seen:
                seen.add(key)
                edges.append((a, b))
    return edges


def path_from_node(nodes: list[SearchNode], node_id: int) -> tuple[int, ...]:
    path: list[int] = []
    current: int | None = node_id
    while current is not None:
        path.append(current)
        current = nodes[current].parent
    return tuple(reversed(path))


def recursive_dfs_with_cycle_check(
    graph: dict[str, list[str]],
) -> tuple[list[SearchNode], list[Event], tuple[int, ...]]:
    nodes: list[SearchNode] = [SearchNode(0, START, None, 0)]
    events: list[Event] = []
    solution: tuple[int, ...] = ()

    def add_event(text: str, stack: tuple[int, ...], solution_nodes: tuple[int, ...] = ()) -> None:
        events.append(
            Event(
                text=text,
                visible_nodes=tuple(node.node_id for node in nodes),
                active_stack=stack,
                solution_nodes=solution_nodes,
            )
        )

    def add_child(parent_id: int, word: str) -> int:
        child_id = len(nodes)
        parent = nodes[parent_id]
        nodes.append(SearchNode(child_id, word, parent_id, parent.depth + 1))
        parent.children.append(child_id)
        return child_id

    def dfs(node_id: int, path_words: tuple[str, ...], stack: tuple[int, ...]) -> bool:
        nonlocal solution
        current_word = nodes[node_id].word
        add_event(f"Check {current_word}", stack)

        if current_word == GOAL:
            solution = stack
            add_event("Goal found: " + " -> ".join(nodes[i].word for i in stack), stack, solution)
            return True

        for neighbor in graph[current_word]:
            if neighbor in path_words:
                add_event(f"Cycle check: skip {current_word} -> {neighbor}", stack)
                continue

            child_id = add_child(node_id, neighbor)
            child_stack = stack + (child_id,)
            add_event(f"Generate {current_word} -> {neighbor}", child_stack)
            if dfs(child_id, path_words + (neighbor,), child_stack):
                return True
            add_event(f"Backtrack from {neighbor} to {current_word}", stack)

        return False

    dfs(0, (START,), (0,))
    return nodes, events, solution


def layout_transition_graph(words: tuple[str, ...]) -> dict[str, tuple[float, float]]:
    # Fixed coordinates keep the drawing readable and deterministic.
    return {
        "dad": (-2.0, 1.2),
        "bad": (-0.7, 1.2),
        "bed": (0.7, 1.2),
        "bee": (2.0, 0.55),
        "see": (3.25, 0.55),
        "had": (-2.0, -0.25),
        "sad": (-0.7, -0.25),
        "saw": (0.7, -0.25),
    }


def layout_search_tree(nodes: list[SearchNode]) -> dict[int, tuple[float, float]]:
    positions: dict[int, tuple[float, float]] = {}
    next_leaf_x = 0

    def visit(node_id: int) -> float:
        nonlocal next_leaf_x
        node = nodes[node_id]
        if not node.children:
            x = float(next_leaf_x)
            next_leaf_x += 1
        else:
            child_xs = [visit(child_id) for child_id in node.children]
            x = sum(child_xs) / len(child_xs)
        positions[node_id] = (x, -float(node.depth))
        return x

    visit(0)
    return positions


def solution_word_edges(solution_words: tuple[str, ...]) -> set[tuple[str, str]]:
    edges: set[tuple[str, str]] = set()
    for a, b in zip(solution_words, solution_words[1:]):
        edges.add(ordered_word_edge(a, b))
    return edges


def import_matplotlib(show: bool):
    try:
        import matplotlib

        if not show:
            matplotlib.use("Agg")

        import matplotlib.animation as animation
        import matplotlib.pyplot as plt
    except ImportError as exc:
        raise SystemExit(
            "This script needs matplotlib. Install it with: python -m pip install matplotlib"
        ) from exc
    return plt, animation


def draw_node(ax, x: float, y: float, label: str, color: str, edgecolor: str = "#243447") -> None:
    ax.scatter([x], [y], s=1200, color=color, edgecolors=edgecolor, linewidths=1.5, zorder=3)
    ax.text(x, y, label, ha="center", va="center", fontsize=10, color="#111111", zorder=4)


def draw_line(ax, p1: tuple[float, float], p2: tuple[float, float], color: str, linewidth: float) -> None:
    ax.plot([p1[0], p2[0]], [p1[1], p2[1]], color=color, linewidth=linewidth, zorder=1)


def save_state_transition_graph(
    plt,
    graph: dict[str, list[str]],
    solution_words: tuple[str, ...],
    out_path: Path,
) -> None:
    positions = layout_transition_graph(WORDS)
    red_edges = solution_word_edges(solution_words)
    fig, ax = plt.subplots(figsize=(9, 4.7))

    for a, b in transition_edges(graph):
        edge_key = ordered_word_edge(a, b)
        color = "#d62828" if edge_key in red_edges else "#9aa3ad"
        width = 3.0 if edge_key in red_edges else 1.4
        draw_line(ax, positions[a], positions[b], color, width)

    for word in WORDS:
        if word == START:
            color = "#90be6d"
        elif word == GOAL:
            color = "#f9844a"
        elif word in solution_words:
            color = "#ffd166"
        else:
            color = "#e9ecef"
        draw_node(ax, *positions[word], word, color)

    ax.set_title("State transition graph (red edges = solution path)", fontsize=13)
    ax.text(
        -2.45,
        -1.05,
        "State: a word in D.  Start: bad.  Goal: see.  Operator: change one letter and stay in D.",
        fontsize=9,
        color="#333333",
    )
    ax.set_axis_off()
    ax.set_xlim(-2.6, 3.75)
    ax.set_ylim(-1.25, 1.75)
    fig.tight_layout()
    fig.savefig(out_path, dpi=200)
    plt.close(fig)


def draw_search_tree_frame(
    ax,
    nodes: list[SearchNode],
    positions: dict[int, tuple[float, float]],
    visible_nodes: set[int],
    active_stack: set[int],
    solution_nodes: set[int],
    message: str,
) -> None:
    ax.clear()

    for node in nodes:
        if node.node_id not in visible_nodes:
            continue
        for child_id in node.children:
            if child_id not in visible_nodes:
                continue
            if node.node_id in solution_nodes and child_id in solution_nodes:
                color, width = "#d62828", 3.0
            elif node.node_id in active_stack and child_id in active_stack:
                color, width = "#f77f00", 2.5
            else:
                color, width = "#b8c0c8", 1.2
            draw_line(ax, positions[node.node_id], positions[child_id], color, width)

    for node in nodes:
        if node.node_id not in visible_nodes:
            continue
        if node.node_id in solution_nodes:
            color = "#ffb3b3"
            edgecolor = "#d62828"
        elif node.node_id in active_stack:
            color = "#ffd166"
            edgecolor = "#f77f00"
        else:
            color = "#e9ecef"
            edgecolor = "#6c757d"
        x, y = positions[node.node_id]
        draw_node(ax, x, y, f"{node.node_id}\n{node.word}", color, edgecolor)

    xs = [x for x, _ in positions.values()]
    ys = [y for _, y in positions.values()]
    ax.set_title("Recursive DFS search tree with cycle checking", fontsize=13)
    ax.text(min(xs) - 0.6, max(ys) + 0.65, message, fontsize=9.5, color="#222222")
    ax.set_xlim(min(xs) - 0.8, max(xs) + 0.8)
    ax.set_ylim(min(ys) - 0.8, max(ys) + 0.95)
    ax.set_axis_off()


def save_search_tree_graph(
    plt,
    nodes: list[SearchNode],
    solution_nodes: tuple[int, ...],
    out_path: Path,
) -> None:
    positions = layout_search_tree(nodes)
    fig, ax = plt.subplots(figsize=(12, 6.8))
    draw_search_tree_frame(
        ax=ax,
        nodes=nodes,
        positions=positions,
        visible_nodes={node.node_id for node in nodes},
        active_stack=set(),
        solution_nodes=set(solution_nodes),
        message="Final search tree. Red nodes and edges form the found path.",
    )
    fig.tight_layout()
    fig.savefig(out_path, dpi=200)
    plt.close(fig)


def save_dfs_animation_html(
    plt,
    animation,
    nodes: list[SearchNode],
    events: list[Event],
    out_path: Path,
) -> None:
    positions = layout_search_tree(nodes)
    fig, ax = plt.subplots(figsize=(12, 6.8))

    def update(frame_index: int):
        event = events[frame_index]
        draw_search_tree_frame(
            ax=ax,
            nodes=nodes,
            positions=positions,
            visible_nodes=set(event.visible_nodes),
            active_stack=set(event.active_stack),
            solution_nodes=set(event.solution_nodes),
            message=f"Step {frame_index + 1}/{len(events)}: {event.text}",
        )
        return []

    ani = animation.FuncAnimation(fig, update, frames=len(events), interval=900, blit=False)
    html = ani.to_jshtml(fps=1)
    out_path.write_text(html, encoding="utf-8")
    plt.close(fig)


def maybe_save_gif(
    plt,
    animation,
    nodes: list[SearchNode],
    events: list[Event],
    out_path: Path,
) -> bool:
    try:
        from matplotlib.animation import PillowWriter
    except Exception:
        return False

    positions = layout_search_tree(nodes)
    fig, ax = plt.subplots(figsize=(12, 6.8))

    def update(frame_index: int):
        event = events[frame_index]
        draw_search_tree_frame(
            ax=ax,
            nodes=nodes,
            positions=positions,
            visible_nodes=set(event.visible_nodes),
            active_stack=set(event.active_stack),
            solution_nodes=set(event.solution_nodes),
            message=f"Step {frame_index + 1}/{len(events)}: {event.text}",
        )
        return []

    ani = animation.FuncAnimation(fig, update, frames=len(events), interval=900, blit=False)
    try:
        ani.save(out_path, writer=PillowWriter(fps=1))
    except Exception:
        plt.close(fig)
        return False
    plt.close(fig)
    return True


def print_answer(graph: dict[str, list[str]], nodes: list[SearchNode], solution_nodes: tuple[int, ...]) -> None:
    solution_words = tuple(nodes[i].word for i in solution_nodes)
    print("Model")
    print("  State set S = D = {" + ", ".join(WORDS) + "}")
    print(f"  Start state Ws = {START}")
    print(f"  Goal state Wt = {GOAL}")
    print("  Operator: change exactly one letter; the new word must still be in D.")
    print()
    print("Neighbor check order follows the dictionary order D:")
    for word in WORDS:
        print(f"  {word}: {', '.join(graph[word]) if graph[word] else '(none)'}")
    print()
    print("Recursive DFS with cycle checking gives:")
    print("  " + " -> ".join(solution_words))
    print(f"  Number of operations = {len(solution_words) - 1}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Word-ladder DFS visualization for bad -> see.")
    default_out = Path(__file__).resolve().parent / "question_outputs"
    parser.add_argument("--out", default=str(default_out), help="Output directory.")
    parser.add_argument("--show", action="store_true", help="Show figures interactively after saving.")
    parser.add_argument("--no-gif", action="store_true", help="Skip optional GIF export.")
    args = parser.parse_args()

    plt, animation = import_matplotlib(show=args.show)
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    graph = build_transition_graph(WORDS)
    nodes, events, solution_nodes = recursive_dfs_with_cycle_check(graph)
    if not solution_nodes:
        raise RuntimeError("No solution found.")
    solution_words = tuple(nodes[i].word for i in solution_nodes)

    save_state_transition_graph(
        plt,
        graph,
        solution_words,
        out_dir / "state_transition_graph.png",
    )
    save_search_tree_graph(
        plt,
        nodes,
        solution_nodes,
        out_dir / "dfs_search_tree.png",
    )
    save_dfs_animation_html(
        plt,
        animation,
        nodes,
        events,
        out_dir / "dfs_animation.html",
    )

    gif_saved = False
    if not args.no_gif:
        gif_saved = maybe_save_gif(
            plt,
            animation,
            nodes,
            events,
            out_dir / "dfs_animation.gif",
        )

    print_answer(graph, nodes, solution_nodes)
    print()
    print("Generated files:")
    print(f"  {out_dir / 'state_transition_graph.png'}")
    print(f"  {out_dir / 'dfs_search_tree.png'}")
    print(f"  {out_dir / 'dfs_animation.html'}")
    if gif_saved:
        print(f"  {out_dir / 'dfs_animation.gif'}")

    if args.show:
        plt.show()


if __name__ == "__main__":
    main()
