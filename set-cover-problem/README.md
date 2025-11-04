# ♟️ Minimum Set Cover Solver (Meeting Coverage)

This C++ program solves the **Minimum Set Cover Problem**, framed as finding the minimum number of members required to collectively cover all scheduled meetings.

Since the Minimum Set Cover Problem is **NP-hard**, the solution employs a hybrid approach: an exact method for small inputs and a highly effective approximation/heuristic strategy for large inputs.

---

## 💡 Problem Description

Given a set of **Meetings** (the Universe) and a collection of **Members** (each representing a set of meetings they attend), the goal is to find the **smallest possible subset of Members** such that every Meeting is attended by at least one selected Member.

* **Universe (Meetings):** `riunioni`
* **Sets (Members):** `tuttiMembri`

---

## 🧠 Algorithmic Strategy

The code dynamically selects an algorithm based on the problem size ($N$).

### 1. Small Instance (Optimal Solution)

If the total number of distinct members ($N$) is less than or equal to **15**, the code guarantees the absolutely optimal solution:

* **Method:** **Brute-Force Combinations (Iterative Exhaustive Search)**.
* **Process:** It iterates through all possible subset sizes $k = 1, 2, 3, \ldots$ and, for each size, it checks every combination of $k$ members using `std::next_permutation` on a boolean mask.
* **Guarantees:** The **Minimum Set Cover** is found because all possibilities are checked in increasing order of size.

### 2. Large Instance (Approximation & Heuristics)

For larger problems where the exhaustive search is too slow, the code uses a powerful approximation strategy:

* **Phase A: Greedy Approximation**
    * It iteratively selects the Member who covers the **maximum number of currently uncovered Meetings**. This is a classic greedy strategy known to provide an approximation solution (within a logarithmic factor of the optimum).
    * It uses a **Max-Heap (`std::priority_queue`)** with a **Lazy Update** mechanism to efficiently find the best unselected member in $O(\log N)$ time per step.

* **Phase B: Randomized Local Search (Optimization)**
    * After the greedy solution is found, the code attempts to refine and potentially reduce its size using a simple local search heuristic.
    * It repeatedly attempts to **randomly remove** a member or **randomly swap** a selected member with an unselected one, checking if the resulting set still covers all meetings and is smaller than the current best solution.

---

## ⚙️ Input/Output Format

The program reads problem data from `input.txt` and writes the resulting minimum set to `output.txt`.

### Input Format (`input.txt`)

The first line contains two integers:
1.  **N**: The total number of distinct members (Nodes/People).
2.  **M**: The total number of meetings to be covered.

The next $M$ lines define the meetings:
* The first number on the line is **C** (the count of members attending that meeting).
* This is followed by $\mathbf{C}$ space-separated Member IDs.

| Example `input.txt` | Description |
| :--- | :--- |
| `10 3` | 10 Members, 3 Meetings. |
| `2 5 8` | Meeting 1 is attended by Members 5 and 8. |
| `3 1 5 9` | Meeting 2 is attended by Members 1, 5, and 9. |
| `1 7` | Meeting 3 is attended by Member 7. |

### Output Format (`output.txt`)

The output contains one line with the result:

1.  The **minimum number of members** required to cover all meetings.
2.  The **IDs** of the selected members, sorted in ascending order.
3.  A final `#` character.

**Example Output (if Members 5, 7, and 9 are selected):**