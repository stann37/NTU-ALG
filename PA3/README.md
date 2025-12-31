# Algorithms-Spring-24-PA3
This repository contains my solution to PA3 for the Algorithms course at National Taiwan University, Spring 2024.

## Problem Description
**Cycle breaking** is a fundamental technique in graph theory used to resolve resource deadlock or simplify problem instances. Given a simple graph that may contain cycles, the objective is to remove a minimal set of edges to make the graph **acyclic**, minimizing the total weight (cost) of the removed edges.

### Types of Graphs Handled
1. **Unweighted Undirected Graphs**
2. **Weighted Undirected Graphs**
3. **Weighted Directed Graphs**

For each type of graph, the approach varies due to computational complexity:
- **Unweighted undirected graphs** can be solved optimally in polynomial time.
- **Weighted directed graphs** present a **NP-hard** problem, known as the **minimum feedback arc set** problem.

### Approach
1. **Unweighted Undirected Graphs**
- Special case of Weighted Undirected Graphs
2. **Weighted Undirected Graphs**
- Reverse Kruskal
3. **Weighted Directed Graphs**
- Approximation algorithm: Handle the graph as if it is undirected, then add non-negative edges back to the graph in a descending order of edge weight if it does not introduce cycles.
