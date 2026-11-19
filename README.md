# Personalized Learning Path and Assessment Planner

## Project 48 – Design and Analysis of Algorithms

The **Personalized Learning Path and Assessment Planner** is a C-based application that analyzes a student's performance and generates a personalized learning plan.

The system uses assessment scores, topic difficulty, prerequisite relationships, available study hours, and algorithmic techniques to recommend what a student should study and in what order.

The updated implementation includes **five major DAA algorithms**:

- Merge Sort
- Dijkstra's Algorithm
- 0/1 Knapsack
- Sum of Subsets using Backtracking
- KMP String Matching

---

## 1. Project Objective

The main objective of this project is to create a personalized learning system that can:

- Analyze student performance.
- Identify weak and strong topics.
- Calculate topic priority.
- Represent prerequisite relationships using graphs.
- Generate personalized learning paths.
- Find minimum-cost learning routes.
- Optimize study plans according to available study hours.
- Find topic combinations for exact study hours.
- Search topics efficiently.
- Track student improvement through reassessment.

---

## 2. Technologies Used

- **Language:** C
- **Standard:** C17 compatible
- **Interface:** Command Line Interface (CLI)
- **Data Structure:** Structures, Arrays and Graphs
- **Graph Representation:** Adjacency Matrix
- **Programming Concepts:** Recursion, Dynamic Programming, Greedy Algorithms, Backtracking and String Matching

---

## 3. Course Topics

The current implementation contains eight learning topics:

| ID | Topic | Difficulty | Required Hours |
|---|---|---:|---:|
| 1 | Searching | 2 | 1 |
| 2 | Sorting | 3 | 2 |
| 3 | Greedy Algorithm | 3 | 2 |
| 4 | Dynamic Programming | 5 | 4 |
| 5 | Graph Basics | 4 | 3 |
| 6 | Dijkstra Algorithm | 4 | 3 |
| 7 | Minimum Spanning Tree | 4 | 3 |
| 8 | String Matching | 3 | 2 |

---

# 4. Algorithms Implemented

## 4.1 Merge Sort – Priority Ranking

Merge Sort is used to arrange topics according to their calculated priority.

The priority of a topic depends on:

- Student weakness – 60%
- Topic difficulty – 40%

Priority is calculated using:

```text
Weakness = 100 - Student Score

Difficulty Score = Difficulty × 20

Priority = 0.6 × Weakness + 0.4 × Difficulty Score
```

A topic with a higher priority should receive more attention.

### Complexity

```text
O(n log n)
```

---

## 4.2 Dijkstra's Algorithm – Shortest Learning Route

The topics and their prerequisites are represented using a **weighted directed graph**.

The edge weight represents the learning effort required to move from one topic to another.

Example:

```text
Searching
    |
    v
Sorting
    |
    v
Greedy Algorithm
    |
    v
Dynamic Programming
    |
    v
Graph Basics
   / \
  v   v
Dijkstra   Minimum Spanning Tree
```

Dijkstra's Algorithm finds the minimum-cost learning route between a starting topic and a target topic.

Example:

```text
Searching
   ->
Sorting
   ->
Greedy Algorithm
   ->
Dynamic Programming
   ->
Graph Basics
```

### Complexity

For the adjacency-matrix implementation:

```text
O(V²)
```

---

## 4.3 0/1 Knapsack – Optimized Study Plan

The 0/1 Knapsack algorithm creates an optimized study plan according to the student's available study hours.

The problem is mapped as:

```text
Knapsack Capacity = Available Study Hours

Item = Topic

Item Weight = Required Study Hours

Item Value = Topic Priority
```

The algorithm selects the combination of incomplete topics that provides the maximum learning value without exceeding the available study time.

### Complexity

```text
O(n × H)
```

Where:

```text
n = number of topics
H = available study hours
```

---

## 4.4 Sum of Subsets – Backtracking

The updated project includes a **Sum of Subsets Backtracking Algorithm**.

It is used to generate study plans whose total required study time is exactly equal to the hours entered by the student.

For every topic, the algorithm has two choices:

```text
Include Topic
      OR
Exclude Topic
```

If the selected topics exactly match the target study hours, the combination is displayed.

Example:

```text
Target Study Time = 5 Hours

Possible Plan:

Sorting             = 2 Hours
Graph Basics        = 3 Hours
--------------------------------
Total               = 5 Hours
```

Another possible combination could be:

```text
Searching           = 1 Hour
Dynamic Programming = 4 Hours
--------------------------------
Total               = 5 Hours
```

### Backtracking Process

```text
Choose Topic
     |
     v
Explore Combination
     |
     v
Target reached?
 /          \
Yes          No
 |            |
Print      Backtrack
              |
              v
        Try another choice
```

### Worst-Case Complexity

```text
O(2^n)
```

---

## 4.5 KMP String Matching – Topic Search

The **Knuth-Morris-Pratt (KMP)** algorithm is used for efficient topic searching.

The student can enter a keyword and the program searches all topic names.

Example:

```text
Enter Topic Keyword: Algorithm
```

Output:

```text
[3] Greedy Algorithm
[6] Dijkstra Algorithm
```

KMP uses an **LPS (Longest Proper Prefix which is also Suffix)** array to avoid unnecessary repeated character comparisons.

### Complexity

```text
O(n + m)
```

Where:

```text
n = text length
m = pattern length
```

---

# 5. Prerequisite Graph

The prerequisite relationships between topics are represented using an **Adjacency Matrix**.

Example:

```text
graph[0][1] = 2;
```

means:

```text
Searching -> Sorting
Learning Cost = 2
```

Current relationships include:

```text
Searching -> Sorting

Sorting -> Greedy Algorithm

Greedy Algorithm -> Dynamic Programming

Dynamic Programming -> Graph Basics

Graph Basics -> Dijkstra Algorithm

Graph Basics -> Minimum Spanning Tree

Sorting -> String Matching
```

A topic on the left should normally be understood before the topic on the right.

---

# 6. Student Assessment

The student enters an assessment score from:

```text
0 to 100
```

for every topic.

The system classifies performance as:

| Score | Status |
|---:|---|
| 80–100 | STRONG |
| 60–79 | GOOD |
| 40–59 | WEAK |
| 0–39 | VERY WEAK |

A topic with a score of **80 or above** is considered mastered.

---

# 7. Personalized Learning Path

The system generates a learning path based on prerequisite relationships.

Already mastered topics can be skipped.

For example, suppose:

```text
Searching = 90%
Sorting = 85%
Greedy Algorithm = 50%
Dynamic Programming = 40%
Graph Basics = 30%
```

If the target is **Graph Basics**, the generated path can be:

```text
Greedy Algorithm
       |
       v
Dynamic Programming
       |
       v
Graph Basics
```

Searching and Sorting are not included because they are already mastered.

---

# 8. Next Recommended Topic

The system recommends the next topic using:

```text
Topic not completed
        +
Prerequisites ready
        +
Highest priority
```

A direct prerequisite should have a score of at least:

```text
60%
```

before the dependent topic is considered ready.

---

# 9. Re-Assessment and Adaptive Learning

Students can take a reassessment after studying a topic.

The system stores:

```text
Previous Score
New Score
Score Change
```

Example:

```text
Previous Score : 40%
New Score      : 75%
Change         : +35%

Performance Improved!
```

After reassessment, priorities are recalculated automatically.

Therefore, the learning recommendations can change according to student improvement.

---

# 10. Main Menu

The main application contains four major modules:

```text
========================================================
       PERSONALIZED LEARNING PATH PLANNER
========================================================

[1] STUDENT ANALYSIS

[2] PERSONALIZED PLANNER

[3] ADAPTIVE INTELLIGENCE

[4] PROGRESS DASHBOARD

[5] EXIT
```

---

# 11. Student Analysis Module

```text
[1] View Topics

[2] Take Assessment

[3] Assessment Dashboard

[4] Weak / Strong Analysis

[5] Priority Ranking (Merge Sort)

[6] Prerequisite Graph

[7] Dependency Risk Detector

[8] Search Topic (KMP)

[9] Back
```

The **KMP Topic Search** is part of this module.

---

# 12. Personalized Planner Module

```text
[1] Personalized Learning Path

[2] Optimized Study Plan (0/1 Knapsack)

[3] Shortest Learning Route (Dijkstra)

[4] Next Recommended Topic

[5] Exact Study Hours (Backtracking)

[6] Back
```

The new **Sum of Subsets Backtracking** algorithm is available through the Exact Study Hours option.

---

# 13. Adaptive Intelligence Module

```text
[1] Re-Assessment

[2] View Updated Priority Ranking

[3] Generate Updated Study Plan

[4] Back
```

This module allows the system to update its recommendations when student performance changes.

---

# 14. Algorithm Summary

| Algorithm | Purpose | Complexity |
|---|---|---|
| Merge Sort | Rank topics according to priority | O(n log n) |
| Dijkstra | Find minimum-cost learning route | O(V²) |
| 0/1 Knapsack | Optimize topics within available hours | O(n × H) |
| Sum of Subsets | Find exact-hour study combinations | O(2^n) worst case |
| KMP | Search topic names efficiently | O(n + m) |

---

# 15. Difference Between Optimization Algorithms

### Dijkstra

Answers:

```text
"What is the minimum-cost learning route
from one topic to another?"
```

### 0/1 Knapsack

Answers:

```text
"Which topics should I study to maximize
learning value within my available hours?"
```

### Sum of Subsets

Answers:

```text
"Which combinations of topics require
exactly the number of hours I want to study?"
```

### Merge Sort

Answers:

```text
"Which topics should receive the highest priority?"
```

### KMP

Answers:

```text
"Which topic names contain the keyword
I am searching for?"
```

---

# 16. Compilation

Using GCC:

```bash
gcc main.c -o learning_planner
```

Run on Windows:

```bash
learning_planner.exe
```

or:

```bash
.\learning_planner.exe
```

On Linux/macOS:

```bash
./learning_planner
```

---

# 17. Suggested Project Structure

```text
personalised_learning_planner/
│
├── src/
│   └── main.c
│
├── README.md
│
└── .gitignore
```

---

# 18. GitHub Update

After modifying the project:

```bash
git status
git add .
git commit -m "Add KMP search and backtracking study planner"
git push origin main
```

---

# 19. Future Improvements

The project can later be extended with additional DAA algorithms such as:

- Quick Sort
- Binary Search
- Activity Selection
- Prim's Algorithm
- Kruskal's Algorithm
- Bellman-Ford
- Floyd-Warshall
- Longest Common Subsequence
- Ford-Fulkerson
- Rabin-Karp

These can be added as separate modules while keeping the existing personalized learning planner interface.

---

# 20. Conclusion

The **Personalized Learning Path and Assessment Planner** combines multiple Design and Analysis of Algorithms concepts in a practical educational application.

The system does not only analyze student scores. It also uses graph algorithms, sorting, dynamic programming, backtracking and string matching to generate personalized learning recommendations.

The current implementation demonstrates five major algorithms:

```text
Merge Sort
     +
Dijkstra
     +
0/1 Knapsack
     +
Sum of Subsets Backtracking
     +
KMP String Matching
```

Together, these algorithms help the system perform **priority ranking, route planning, study-time optimization, exact-hour planning and efficient topic searching**.