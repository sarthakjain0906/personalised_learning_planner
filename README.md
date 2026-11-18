# Personalized Learning Path and Assessment Planner

## Project 48

The **Personalized Learning Path and Assessment Planner** is a C-based application that analyzes a student's performance in different topics and generates a personalized study plan.

The system uses student assessment scores, topic difficulty, prerequisite relationships, and available study hours to recommend what the student should study next.

The project also demonstrates important **Design and Analysis of Algorithms (DAA)** concepts using Merge Sort, Dijkstra's Algorithm, and 0/1 Knapsack.

---

## Features

The application provides the following features:

- Student profile creation
- Topic-wise assessment
- Weak and strong topic analysis
- Topic priority calculation
- Priority-based topic ranking
- Prerequisite knowledge graph
- Dependency analysis
- Personalized learning path generation
- Study-time optimization
- Shortest learning route
- Next recommended topic
- Re-assessment
- Adaptive study planning
- Overall progress dashboard

---

## Algorithms Used

### 1. Merge Sort

**Purpose:** Rank learning topics according to their priority.

Each topic receives a priority score based on the student's current score and topic difficulty.

The topics are then sorted from highest priority to lowest priority using Merge Sort.

**Time Complexity:**

```text
O(n log n)
```

**Use in Project:**

```text
Student Scores
      |
      v
Priority Calculation
      |
      v
Merge Sort
      |
      v
Priority Ranking
```

---

### 2. Dijkstra's Algorithm

**Purpose:** Find the shortest learning route between two topics.

Topics are represented as vertices in a graph, while learning dependencies are represented as weighted edges.

Dijkstra's Algorithm finds a minimum-cost route from the selected starting topic to the target topic.

**Time Complexity:**

```text
O(V^2)
```

for the adjacency-matrix implementation used in this project.

**Use in Project:**

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
   |
   v
Dijkstra Algorithm
```

---

### 3. 0/1 Knapsack

**Purpose:** Optimize the student's available study time.

Each topic has:

- Required study hours
- Priority value

The available study hours act as the Knapsack capacity.

The algorithm selects a combination of topics that provides maximum learning priority without exceeding the available study time.

**Time Complexity:**

```text
O(n * H)
```

where:

```text
n = number of topics
H = available study hours
```

**Example:**

If a student has:

```text
Available Study Time = 10 hours
```

the algorithm tries to select the best combination of topics whose total required time is at most 10 hours.

---

## Priority Calculation

Topic priority is calculated using:

```text
Weakness = 100 - Student Score

Difficulty Score = Difficulty * 20

Priority = 0.6 * Weakness + 0.4 * Difficulty Score
```

Therefore, topics where the student has a low score receive greater priority.

Difficult topics are also given additional importance.

---

## Knowledge Levels

The application classifies student performance as:

| Score | Knowledge Level |
|---|---|
| 80–100 | Strong |
| 60–79 | Good |
| 40–59 | Weak |
| Below 40 | Very Weak |

A topic with a score of **80 or above** is considered mastered.

---

## Prerequisite Graph

The project uses a graph to represent relationships between topics.

Example:

```text
Searching
    |
    v
Sorting
    |
    +--------------------> String Matching
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
Dijkstra Algorithm    Minimum Spanning Tree
```

This helps the application avoid recommending advanced topics without considering their prerequisites.

---

## Project Structure

A simple repository structure can be:

```text
personalised_learning_planner/
│
├── personalised_learning_planner.c
├── README.md
└── screenshots/
```

The main implementation is contained in:

```text
personalised_learning_planner.c
```

---

## Main Menu

When the application starts, the user gets the following main menu:

```text
======================================================================
                 PERSONALIZED LEARNING PATH PLANNER
======================================================================

Welcome, Student

Study Time: 10 Hours | Target Score: 80%

        [1]  STUDENT ANALYSIS

        [2]  PERSONALIZED PLANNER

        [3]  ADAPTIVE INTELLIGENCE

        [4]  PROGRESS DASHBOARD

        [5]  EXIT
```

---

## Student Analysis

This section contains:

```text
1. View Topics
2. Take Assessment
3. Assessment Dashboard
4. Weak / Strong Analysis
5. Priority Ranking using Merge Sort
6. Prerequisite Graph
7. Dependency Risk Detector
```

The assessment scores are used to calculate the student's learning priorities.

---

## Personalized Planner

This section contains:

```text
1. Personalized Learning Path
2. Optimized Study Plan using 0/1 Knapsack
3. Shortest Learning Route using Dijkstra
4. Next Recommended Topic
```

This is the main recommendation component of the application.

---

## Adaptive Intelligence

After studying a topic, the student can take another assessment.

The new score is compared with the previous score.

Example:

```text
Previous Score : 45%
New Score      : 70%
Change         : +25%

Performance Improved!
```

The system recalculates topic priorities after the assessment.

This allows the learning plan to change according to student progress.

---

## Progress Dashboard

The dashboard displays:

- Average score
- Number of mastered topics
- Topic-wise progress
- Knowledge level

Example:

```text
Searching                 [################----] 80% STRONG
Sorting                   [############--------] 60% GOOD
Greedy Algorithm          [########------------] 40% WEAK
Dynamic Programming       [#####---------------] 25% VERY WEAK
```

---

## Technologies Used

- **Programming Language:** C
- **Data Structures:** Arrays, Structures and Graphs
- **Graph Representation:** Adjacency Matrix
- **Interface:** Menu-driven Command Line Interface
- **Algorithm Design Techniques:** Divide and Conquer, Greedy and Dynamic Programming

---

## Compilation

### GCC

Compile the program using:

```bash
gcc personalised_learning_planner.c -o planner
```

Run it on Linux/macOS using:

```bash
./planner
```

On Windows:

```bash
planner.exe
```

If using VS Code, make sure GCC/MinGW is installed and available in the system PATH.

---

## Algorithm Summary

| Algorithm | Technique | Application | Complexity |
|---|---|---|---|
| Merge Sort | Divide and Conquer | Topic priority ranking | O(n log n) |
| Dijkstra | Greedy / Graph | Shortest learning route | O(V²) |
| 0/1 Knapsack | Dynamic Programming | Study-time optimization | O(n × H) |

---

## Project Objective

The main objective of this project is to develop a simple learning analytics system that can:

1. Analyze student performance.
2. Identify weak and strong topics.
3. Understand prerequisite relationships.
4. Prioritize topics according to learning needs.
5. Generate a personalized learning path.
6. Optimize limited study time.
7. Track improvement through re-assessment.

---

## Example Workflow

```text
Create Student Profile
        |
        v
Take Assessment
        |
        v
Analyze Scores
        |
        v
Calculate Topic Priority
        |
        +----------------------+
        |                      |
        v                      v
   Merge Sort            Prerequisite Graph
        |                      |
        v                      v
Priority Ranking       Learning Dependencies
        |                      |
        +-----------+----------+
                    |
                    v
          Personalized Planner
             /             \
            v               v
       Dijkstra         0/1 Knapsack
            |               |
            v               v
     Learning Route    Optimized Study Plan
             \             /
              \           /
               v         v
              Re-Assessment
                    |
                    v
              Updated Plan
```

---

## Conclusion

The Personalized Learning Path and Assessment Planner demonstrates how classical algorithms can be applied to a practical educational problem.

Instead of using algorithms only as independent examples, this project connects them with real functions:

- **Merge Sort** ranks learning priorities.
- **Dijkstra's Algorithm** finds an efficient learning route.
- **0/1 Knapsack** optimizes limited study time.

The system continuously analyzes student performance and can update recommendations after re-assessment, making the learning plan more personalized and adaptive.

---

## Author

**Sarthak Jain**

Project: **Personalized Learning Path and Assessment Planner**

Language: **C**