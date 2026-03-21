<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=1&height=250&section=header&text=Abstract%20Data%20Types&fontSize=60&fontAlignY=35&desc=A%20High-Performance%20C%2B%2B%20Library&descAlignY=55&descSize=20" width="100%" />

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](#)
[![Build: Passing](https://img.shields.io/badge/Build-Passing-2ea44f?style=for-the-badge&logo=githubactions&logoColor=white)](#)
[![Architecture: Contracts](https://img.shields.io/badge/Architecture-Contracts-5a32fa?style=for-the-badge&logo=codeforces&logoColor=white)](#)

<br>
<i>A handcrafted, rigorously benchmarked C++17 library. Built for speed. Designed for CMSC 123.</i>
<br><br>

</div>

---

## 🚀 The Data Structures

We rejected the standard textbook code. Every structure here is strictly bound by **abstract interfaces** and benchmarked at scale to prove its mathematical time complexity.

|  Abstract Type |  Our Implementation |  Highlights & Twists |  Dev |
| :--- | :--- | :--- | :--- |
| **FIFO Queue** | `SLList` | Tail-pointer optimized for instant $O(1)$ enqueues. | Dexter |
| **FILO Stack** | `ArrayStack` | Dynamic memory scaling and ghost scrubbing. | Dexter |
| **Unsorted Set** | `Chained HashTable` | Custom hash routing with linked-node collisions. | Dexter |
| **Sorted Set**| `SkipList` | Randomized height layers for rapid $O(\log n)$ jumps. | Janelle |
| **Bi-Directional List** | `DLList` | Complete spatial node traversal and pooling. | Janelle |
| **Graph** | `Adjacency Matrix` | Instant edge lookups and matrix-based routing. | Janelle |
| **Sorted Set**| `Red-Black Tree` | Self-balancing rotations and strict color rules. | Diane |
| **Double-Ended Queue** | `ArrayDeque` | Circular array arithmetic and wrap-around logic. | Diane |
| **Priority Queue**| `Heap` | Optimized tree-based extraction of min/max values. | Diane |

---

## 🗂️ The Interface-Driven Architecture

Instead of dumping all our code into single files, we built a highly modular pipeline. 

<table>
  <tr>
    <td width="50%" valign="top">
      <h3> The Contracts (<code>include/</code>)</h3>
      Pure virtual C++ base classes. These files act as the law, forcing our implementations to obey strict behavioral rules (e.g. <code>queue.h</code>, <code>deque.h</code>).
    </td>
    <td width="50%" valign="top">
      <h3> The Engines (<code>src/</code>)</h3>
      The raw C++ code where the algorithms actually live and manage memory (e.g. <code>sllist.h</code>, <code>chainedhashtable.h</code>).
    </td>
  </tr>
  <tr>
    <td width="50%" valign="top">
      <h3> The Crucible (<code>tests/</code>)</h3>
      Rigorous edge-case execution scripts. These prove that popping an empty queue throws the correct error rather than crashing the program.
    </td>
    <td width="50%" valign="top">
      <h3> The Stopwatch (<code>time_benchmark/</code>)</h3>
      <code>&lt;chrono&gt;</code> powered microsecond scripts. We use these to mathematically prove that our $O(1)$ methods actually run in $O(1)$ time.
    </td>
  </tr>
</table>

---

## 💻 Quickstart Execution

> **Prove it yourself:** Our benchmark scripts pause and wait for you to input `n` (the number of operations to test). 

```bash
# 1. Compile the Chained Hash Table benchmark
cd time_benchmark
g++ chainedhashtable.cpp -o hash_bench

# 2. Run it and input a number (like 10000) to test 10K operations
./hash_bench
