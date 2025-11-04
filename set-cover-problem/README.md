# 🚴 Directed Feedback Vertex Set (DFVS) Solver

This repository contains a C++ implementation designed to solve a specific instance of the **Directed Feedback Vertex Set (DFVS) Problem**.

The goal is to find a single vertex (node) in a directed graph whose removal is sufficient to make the entire graph acyclic (a Directed Acyclic Graph or DAG).

---

## 💡 Problem Description

The **Directed Feedback Vertex Set (DFVS)** problem asks for the minimum set of vertices whose deletion breaks every directed cycle in a graph.

This implementation solves the $\mathbf{k=1}$ version of this problem: we search for a *single* vertex whose removal guarantees an acyclic graph.

### Technical Details

* **Input:** A directed graph $G=(V, E)$.
* **Goal:** Find $v \in V$ such that $G \setminus \{v\}$ contains no cycles.
* **Method:** The solution employs a trial-and-error approach, where it iterates through every vertex, temporarily "excluding" it, and running a **Depth First Search (DFS)** cycle detection on the remaining graph.

---

## ⚙️ How It Works

The core logic is handled by two main components:

1.  **`struct nodo` / `typedef vector<nodo> grafo`**: Defines the graph structure using an adjacency list.
2.  **`bool grafo_ciclico(...)`**: This recursive function performs the cycle detection using DFS. It utilizes two boolean arrays to track the state of vertices:
    * `visited`: True if the vertex has been reached.
    * `in_stack`: True if the vertex is currently in the recursion stack (indicating the presence of a back edge, which signals a cycle).
3.  **`main()`**: The main loop iterates through every vertex as the potential one to exclude.
    * If excluding a vertex results in an acyclic graph, the solution is found.
    * If a cycle is still present, the path of that cycle is recorded.

### Data Structures Used

* `std::vector<nodo>`: Adjacency list representation of the graph.
* `std::vector<bool>` (`visited`, `in_stack`): Used for efficient cycle detection during DFS.
* `std::vector<int>` (`path`): Records the current path during DFS to reconstruct the cycle when found.

---

## 📂 Input/Output Format

The program reads from `input.txt` and writes the result to `output.txt`.

### Input (`input.txt`)

The first line contains two integers:
1.  **N**: The number of vertices (nodes), indexed from $0$ to $N-1$.
2.  **M**: The number of directed edges.

The next $M$ lines each contain two integers representing a directed edge:
* `from` `to`

**Example Input:**