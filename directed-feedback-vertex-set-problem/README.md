# 🚴 Single Vertex Feedback Set Solver

This C++ program solves the specific case of the **Directed Feedback Vertex Set (DFVS)** problem where the goal is to find a **single** vertex whose removal makes the entire directed graph acyclic.

## 💡 Problem Overview

The **Feedback Vertex Set (FVS)** problem involves finding the smallest set of vertices that, when removed, eliminates all cycles in a graph. Since we are dealing with a directed graph, this is the **Directed FVS** problem.

This code provides a solution for graphs where the minimum size of the FVS is **1** (i.e., $k=1$). It finds that specific node, if it exists, and identifies a cycle that was broken by its removal.

---

## ⚙️ Algorithm

The solution employs a trial-and-error approach combined with Depth First Search (DFS):

1.  **Iterative Exclusion:** The `main` function iterates through every vertex (from $0$ to $N-1$) and temporarily treats it as the "excluded" node.
2.  **Cycle Detection (DFS):** For the remaining graph ($G \setminus \{exclude\}$), the `grafo_ciclico` function performs a DFS-based cycle detection, which is standard for directed graphs.
    * It uses `visited` to track visited nodes.
    * It uses `in_stack` to track nodes currently in the recursion path. A cycle is detected when a neighbor $v$ is reached that is both **visited** and **in\_stack** (a "back edge").
3.  **Path Reconstruction:** If a cycle is detected, the path is stored in `final_cycle_path`.
4.  **Solution Found:** If a vertex's exclusion results in a completely **acyclic** graph, that vertex is the solution (`result`), and the program terminates the search.

---

## 📁 Usage

The program uses standard file I/O operations (`fstream`).

### Input Format (`input.txt`)

The input file must contain the graph definition:

| Line | Format | Description |
| :--- | :--- | :--- |
| **1** | `N M` | $\mathbf{N}$ (number of vertices, $0$ to $N-1$) and $\mathbf{M}$ (number of directed edges). |
| **2 to M+1** | `from to` | A single directed edge from vertex `from` to vertex `to`. |

**Example Input:**