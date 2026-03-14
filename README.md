# Bridges & Articulation Points (C++)

## Introduction
This repository provides an efficient, standard C++ implementation for identifying critical points of failure in undirected graphs: **Articulation Points** (Cut Vertices) and **Bridges** (Cut Edges).
---

## Core Concepts

In an undirected graph:
* **Articulation Point:** A vertex whose removal increases the number of connected components.
* **Bridge:** An edge whose removal increases the number of connected components.

## Features
* **Linear Efficiency:** Runs in $O(V + E)$ time, making it ideal for large-scale graphs ($N \ge 3 \cdot 10^5$).
* **Dataset-Ready Benchmarking:** Built-in support to run performance tests against external text-based datasets.
* **Disconnected Support:** Correctly handles graphs with multiple separate components.
* **Zero Dependencies:** Pure C++ using only the Standard Template Library (STL).
---

## Code Structure
* `main.cpp`: The core algorithm implementation and entry point for basic usage.
* `benchmark.cpp`: A performance-testing utility that measures execution time and accuracy using your local datasets.
* `datasets/`: Directory containing your graph data files (e.g., `dataset_100.txt`, `dataset_1000.txt`).

---

## Installation & Usage

### 1. Requirements
* A C++ compiler (GCC, Clang, or MSVC) supporting C++11 or higher.

### 2. Standard Usage
Compile the main logic:
```bash
g++ main.cpp -o tarjan -O3
```
Run the application (Input format: $N$ $M$ followed by $M$ edges):
```bash
./tarjan
```

### 3. Running Benchmarks
The benchmark tool is designed to read from your `datasets/` folder. It separates **Load Time** from **Algorithm Time** to give you a precise look at performance.

**Compilation:**
```bash
g++ benchmark.cpp -o benchmark -O3
```

**Execution:**
To test with a specific dataset (e.g., `dataset_1000.txt`), pass the suffix as an argument:
```bash
./benchmark 1000
```

---

## Performance & Complexity

| Metric | Complexity |
| :--- | :--- |
| **Time Complexity** | $O(V + E)$ |
| **Space Complexity** | $O(V + E)$ |
| **Recursion Depth** | $O(V)$ |

### Results on my old computer
| Dataset | Nodes ($V$) | Edges ($E$) | Algorithm Time |
| :--- | :--- | :--- | :--- |
| `dataset_100` | 100 | ~300 | < 0.01 ms |
| `dataset_1000` | 1,000 | ~5,000 | ~0.15 ms |
| `dataset_100000` | 100,000 | ~500,000 | ~25.00 ms |

> **Note:** Performance may vary based on graph density (the ratio of $E$ to $V$).

---

## Dataset Format
To ensure your custom datasets work with the benchmark tool, they should follow this format:
```text
[N: Number of vertices] [M: Number of edges]
[u1] [v1]
[u2] [v2]
...
```
