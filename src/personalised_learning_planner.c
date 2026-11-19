#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOPICS 20
#define MAX_HOURS 100
#define INF 99999

/* ================= COLORS ================= */

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define BOLD   "\033[1m"

/* ================= STRUCTURES ================= */

typedef struct
{
    int id;
    char name[50];

    int difficulty;
    int requiredHours;

    int score;
    int previousScore;

    float priority;
    int completed;

} Topic;

typedef struct
{
    char name[50];
    int availableHours;
    int targetScore;

} Student;

/* ================= GLOBAL DATA ================= */

Topic topics[MAX_TOPICS];
Student student;

int topicCount = 8;
int assessmentTaken = 0;

int graph[MAX_TOPICS][MAX_TOPICS] = {0};

/* Used by Sum of Subsets */
int solutionCount = 0;

/* ============================================================
   BASIC UI
   ============================================================ */

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter()
{
    int c;

    printf("\n" CYAN "Press ENTER to continue..." RESET);

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    getchar();
}

void printLine()
{
    printf(CYAN
           "======================================================================\n"
           RESET);
}

void printHeader(const char title[])
{
    clearScreen();

    printLine();

    printf(BOLD CYAN
           "                 %s\n"
           RESET,
           title);

    printLine();
}

/* ============================================================
   PROGRESS BAR
   ============================================================ */

void progressBar(int score)
{
    int bars = score / 5;

    printf("[");

    for (int i = 0; i < 20; i++)
    {
        if (i < bars)
            printf("#");
        else
            printf("-");
    }

    printf("] %3d%%", score);
}

/* ============================================================
   STATUS
   ============================================================ */

void printStatus(int score)
{
    if (score >= 80)
        printf(GREEN "STRONG" RESET);

    else if (score >= 60)
        printf(CYAN "GOOD" RESET);

    else if (score >= 40)
        printf(YELLOW "WEAK" RESET);

    else
        printf(RED "VERY WEAK" RESET);
}

/* ============================================================
   INITIALIZE TOPICS
   ============================================================ */

void initializeTopics()
{
    topics[0] =
        (Topic){1, "Searching", 2, 1, 0, 0, 0, 0};

    topics[1] =
        (Topic){2, "Sorting", 3, 2, 0, 0, 0, 0};

    topics[2] =
        (Topic){3, "Greedy Algorithm", 3, 2, 0, 0, 0, 0};

    topics[3] =
        (Topic){4, "Dynamic Programming", 5, 4, 0, 0, 0, 0};

    topics[4] =
        (Topic){5, "Graph Basics", 4, 3, 0, 0, 0, 0};

    topics[5] =
        (Topic){6, "Dijkstra Algorithm", 4, 3, 0, 0, 0, 0};

    topics[6] =
        (Topic){7, "Minimum Spanning Tree", 4, 3, 0, 0, 0, 0};

    topics[7] =
        (Topic){8, "String Matching", 3, 2, 0, 0, 0, 0};
}

/* ============================================================
   PREREQUISITE GRAPH
   ============================================================ */

void initializeGraph()
{
    /*
       Searching -> Sorting
       Sorting -> Greedy
       Greedy -> DP
       DP -> Graph Basics
       Graph Basics -> Dijkstra
       Graph Basics -> MST
       Sorting -> String Matching

       Weight = learning effort
    */

    graph[0][1] = 2;
    graph[1][2] = 3;
    graph[2][3] = 4;
    graph[3][4] = 4;
    graph[4][5] = 3;
    graph[4][6] = 3;
    graph[1][7] = 2;
}

/* ============================================================
   FIND TOPIC
   ============================================================ */

int findTopicIndex(int id)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].id == id)
            return i;
    }

    return -1;
}

/* ============================================================
   PRIORITY CALCULATION
   ============================================================ */

void calculatePriority()
{
    for (int i = 0; i < topicCount; i++)
    {
        int weakness = 100 - topics[i].score;

        int difficultyScore =
            topics[i].difficulty * 20;

        topics[i].priority =
            0.6f * weakness +
            0.4f * difficultyScore;

        topics[i].completed =
            (topics[i].score >= 80);
    }
}

/* ============================================================
   STUDENT PROFILE
   ============================================================ */

void enterStudentDetails()
{
    printHeader("STUDENT PROFILE");

    printf("\nStudent Name          : ");

    scanf(" %49[^\n]", student.name);

    do
    {
        printf("Available Study Hours : ");
        scanf("%d", &student.availableHours);

    } while (student.availableHours <= 0 ||
             student.availableHours > MAX_HOURS);

    do
    {
        printf("Target Score          : ");
        scanf("%d", &student.targetScore);

    } while (student.targetScore < 0 ||
             student.targetScore > 100);

    printf("\n" GREEN
           "Profile Created Successfully!\n"
           RESET);

    waitForEnter();
}

/* ============================================================
   DISPLAY TOPICS
   ============================================================ */

void displayTopics()
{
    printHeader("COURSE TOPICS");

    printf("\n%-5s %-28s %-12s %-10s\n",
           "ID",
           "TOPIC",
           "DIFFICULTY",
           "HOURS");

    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < topicCount; i++)
    {
        printf("%-5d %-28s %-12d %-10d\n",
               topics[i].id,
               topics[i].name,
               topics[i].difficulty,
               topics[i].requiredHours);
    }

    waitForEnter();
}

/* ============================================================
   ASSESSMENT
   ============================================================ */

void takeAssessment()
{
    printHeader("STUDENT ASSESSMENT");

    printf("\nEnter score from 0 to 100 for each topic.\n\n");

    for (int i = 0; i < topicCount; i++)
    {
        do
        {
            printf("%-28s : ", topics[i].name);

            scanf("%d", &topics[i].score);

            if (topics[i].score < 0 ||
                topics[i].score > 100)
            {
                printf(RED
                       "Invalid score. Use 0-100.\n"
                       RESET);
            }

        } while (topics[i].score < 0 ||
                 topics[i].score > 100);

        topics[i].previousScore =
            topics[i].score;
    }

    assessmentTaken = 1;

    calculatePriority();

    printf("\n" GREEN
           "Assessment Completed Successfully!\n"
           RESET);

    waitForEnter();
}

/* ============================================================
   ASSESSMENT DASHBOARD
   ============================================================ */

void assessmentDashboard()
{
    printHeader("STUDENT ANALYSIS");

    printf("\nStudent      : " BOLD "%s" RESET "\n",
           student.name);

    printf("Target Score : %d%%\n\n",
           student.targetScore);

    for (int i = 0; i < topicCount; i++)
    {
        printf("%-25s ", topics[i].name);

        progressBar(topics[i].score);

        printf("  ");

        printStatus(topics[i].score);

        printf("\n");
    }

    waitForEnter();
}

/* ============================================================
   WEAK / STRONG ANALYSIS
   ============================================================ */

void weakStrongAnalysis()
{
    printHeader("WEAK / STRONG ANALYSIS");

    printf(GREEN "\nSTRONG TOPICS\n" RESET);

    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].score >= 80)
        {
            printf("  %-28s %d%%\n",
                   topics[i].name,
                   topics[i].score);
        }
    }

    printf(YELLOW
           "\nTOPICS NEEDING IMPROVEMENT\n"
           RESET);

    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].score < 80)
        {
            printf("  %-28s %d%%  ",
                   topics[i].name,
                   topics[i].score);

            printStatus(topics[i].score);

            printf("\n");
        }
    }

    waitForEnter();
}

/* ============================================================
   ALGORITHM 1
   MERGE SORT FOR PRIORITY RANKING
   ============================================================ */

void mergeTopics(Topic arr[],
                 int left,
                 int mid,
                 int right)
{
    Topic temp[MAX_TOPICS];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i].priority >=
            arr[j].priority)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0;
         i <= right;
         i++, k++)
    {
        arr[i] = temp[k];
    }
}

void mergeSortTopics(Topic arr[],
                     int left,
                     int right)
{
    if (left < right)
    {
        int mid =
            left + (right - left) / 2;

        mergeSortTopics(arr,
                        left,
                        mid);

        mergeSortTopics(arr,
                        mid + 1,
                        right);

        mergeTopics(arr,
                    left,
                    mid,
                    right);
    }
}

void priorityRanking()
{
    calculatePriority();

    Topic sorted[MAX_TOPICS];

    for (int i = 0; i < topicCount; i++)
        sorted[i] = topics[i];

    mergeSortTopics(sorted,
                    0,
                    topicCount - 1);

    printHeader(
        "TOPIC PRIORITY RANKING - MERGE SORT"
    );

    printf("\n%-6s %-28s %-10s %-12s\n",
           "RANK",
           "TOPIC",
           "SCORE",
           "PRIORITY");

    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < topicCount; i++)
    {
        printf("%-6d %-28s %-10d %-12.2f\n",
               i + 1,
               sorted[i].name,
               sorted[i].score,
               sorted[i].priority);
    }

    printf("\nAlgorithm Used : Merge Sort\n");
    printf("Time Complexity: O(n log n)\n");

    waitForEnter();
}

/* ============================================================
   DISPLAY PREREQUISITE GRAPH
   ============================================================ */

void displayPrerequisiteGraph()
{
    printHeader(
        "PREREQUISITE KNOWLEDGE GRAPH"
    );

    printf("\n");

    for (int i = 0; i < topicCount; i++)
    {
        for (int j = 0; j < topicCount; j++)
        {
            if (graph[i][j] != 0)
            {
                printf(
                    "%-28s ---> %-28s Cost: %d\n",
                    topics[i].name,
                    topics[j].name,
                    graph[i][j]
                );
            }
        }
    }

    printf(
        "\nA ---> B means A should be "
        "understood before B.\n"
    );

    waitForEnter();
}

/* ============================================================
   DEPENDENCY CHECK
   ============================================================ */

void checkDependencies(int target,
                       int visited[])
{
    for (int i = 0; i < topicCount; i++)
    {
        if (graph[i][target] != 0 &&
            !visited[i])
        {
            visited[i] = 1;

            checkDependencies(i,
                              visited);

            printf("%-28s %3d%%  ",
                   topics[i].name,
                   topics[i].score);

            printStatus(topics[i].score);

            printf("\n");
        }
    }
}

void dependencyRiskDetector()
{
    printHeader("DEPENDENCY RISK DETECTOR");

    for (int i = 0; i < topicCount; i++)
    {
        printf("[%d] %-28s %d%%\n",
               topics[i].id,
               topics[i].name,
               topics[i].score);
    }

    int id;

    printf("\nSelect Target Topic ID: ");
    scanf("%d", &id);

    int target = findTopicIndex(id);

    if (target == -1)
    {
        printf(RED
               "\nInvalid Topic ID.\n"
               RESET);

        waitForEnter();
        return;
    }

    int visited[MAX_TOPICS] = {0};

    printf("\nPrerequisites for %s:\n\n",
           topics[target].name);

    checkDependencies(target,
                      visited);

    waitForEnter();
}

/* ============================================================
   ALGORITHM 2
   DIJKSTRA SHORTEST LEARNING ROUTE
   ============================================================ */

int minimumDistance(int distance[],
                    int visited[])
{
    int minimum = INF;
    int index = -1;

    for (int i = 0; i < topicCount; i++)
    {
        if (!visited[i] &&
            distance[i] < minimum)
        {
            minimum = distance[i];
            index = i;
        }
    }

    return index;
}

void printDijkstraPath(int parent[],
                       int target)
{
    if (parent[target] == -1)
    {
        printf("%s",
               topics[target].name);

        return;
    }

    printDijkstraPath(
        parent,
        parent[target]
    );

    printf(" -> %s",
           topics[target].name);
}

void shortestLearningRoute()
{
    printHeader(
        "SHORTEST LEARNING ROUTE - DIJKSTRA"
    );

    printf("\nAvailable Topics:\n\n");

    for (int i = 0; i < topicCount; i++)
    {
        printf("[%d] %s\n",
               topics[i].id,
               topics[i].name);
    }

    int startID;
    int targetID;

    printf("\nStarting Topic ID : ");
    scanf("%d", &startID);

    printf("Target Topic ID   : ");
    scanf("%d", &targetID);

    int start =
        findTopicIndex(startID);

    int target =
        findTopicIndex(targetID);

    if (start == -1 || target == -1)
    {
        printf(RED
               "\nInvalid Topic ID.\n"
               RESET);

        waitForEnter();
        return;
    }

    int distance[MAX_TOPICS];
    int visited[MAX_TOPICS] = {0};
    int parent[MAX_TOPICS];

    for (int i = 0; i < topicCount; i++)
    {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[start] = 0;

    for (int count = 0;
         count < topicCount - 1;
         count++)
    {
        int u =
            minimumDistance(
                distance,
                visited
            );

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0;
             v < topicCount;
             v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][v]
                    < distance[v])
            {
                distance[v] =
                    distance[u] +
                    graph[u][v];

                parent[v] = u;
            }
        }
    }

    printf("\n");

    if (distance[target] == INF)
    {
        printf(RED
               "No learning route exists "
               "between these topics.\n"
               RESET);
    }
    else
    {
        printf(GREEN
               "Recommended Learning Route:\n\n"
               RESET);

        printDijkstraPath(
            parent,
            target
        );

        printf(
            "\n\nTotal Learning Cost : %d\n",
            distance[target]
        );

        printf(
            "Algorithm Used      : Dijkstra\n"
        );

        printf(
            "Complexity          : O(V^2)\n"
        );
    }

    waitForEnter();
}

/* ============================================================
   PERSONALIZED LEARNING PATH
   ============================================================ */

void buildLearningPath(int target,
                       int visited[],
                       int path[],
                       int *count)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (graph[i][target] != 0 &&
            !visited[i])
        {
            buildLearningPath(
                i,
                visited,
                path,
                count
            );
        }
    }

    if (!visited[target])
    {
        visited[target] = 1;

        if (!topics[target].completed)
        {
            path[*count] = target;
            (*count)++;
        }
    }
}

void personalizedLearningPath()
{
    calculatePriority();

    printHeader(
        "PERSONALIZED LEARNING PATH"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf("[%d] %-28s %d%%\n",
               topics[i].id,
               topics[i].name,
               topics[i].score);
    }

    int id;

    printf(
        "\nSelect Final Target Topic: "
    );

    scanf("%d", &id);

    int target =
        findTopicIndex(id);

    if (target == -1)
    {
        printf(RED
               "\nInvalid Topic.\n"
               RESET);

        waitForEnter();
        return;
    }

    int visited[MAX_TOPICS] = {0};
    int path[MAX_TOPICS];
    int count = 0;

    buildLearningPath(
        target,
        visited,
        path,
        &count
    );

    printHeader(
        "YOUR PERSONALIZED LEARNING PATH"
    );

    printf("\nStudent : %s\n",
           student.name);

    printf("Target  : %s\n\n",
           topics[target].name);

    if (count == 0)
    {
        printf(
            GREEN
            "Target and prerequisites are "
            "already mastered.\n"
            RESET
        );
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            int index = path[i];

            printf("%d. " BOLD "%s" RESET,
                   i + 1,
                   topics[index].name);

            printf(
                " | Score: %d%% | "
                "Priority: %.2f\n",
                topics[index].score,
                topics[index].priority
            );

            if (i < count - 1)
            {
                printf("        |\n");
                printf("        v\n");
            }
        }
    }

    waitForEnter();
}

/* ============================================================
   ALGORITHM 3
   0/1 KNAPSACK STUDY OPTIMIZER
   ============================================================ */

int maxValue(int a, int b)
{
    return (a > b) ? a : b;
}

void optimizedStudyPlan()
{
    calculatePriority();

    printHeader(
        "OPTIMIZED STUDY PLAN - 0/1 KNAPSACK"
    );

    int candidates[MAX_TOPICS];
    int candidateCount = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (!topics[i].completed)
        {
            candidates[candidateCount++] = i;
        }
    }

    if (candidateCount == 0)
    {
        printf(GREEN
               "\nAll topics are already mastered!\n"
               RESET);

        waitForEnter();
        return;
    }

    int hours =
        student.availableHours;

    int dp[MAX_TOPICS + 1]
          [MAX_HOURS + 1];

    memset(dp, 0, sizeof(dp));

    for (int i = 1;
         i <= candidateCount;
         i++)
    {
        int topicIndex =
            candidates[i - 1];

        int required =
            topics[topicIndex].requiredHours;

        int value =
            (int)topics[topicIndex].priority;

        for (int h = 0;
             h <= hours;
             h++)
        {
            if (required <= h)
            {
                dp[i][h] =
                    maxValue(
                        dp[i - 1][h],

                        value +
                        dp[i - 1]
                          [h - required]
                    );
            }
            else
            {
                dp[i][h] =
                    dp[i - 1][h];
            }
        }
    }

    int selected[MAX_TOPICS];
    int selectedCount = 0;

    int h = hours;

    for (int i = candidateCount;
         i > 0;
         i--)
    {
        if (dp[i][h] !=
            dp[i - 1][h])
        {
            int topicIndex =
                candidates[i - 1];

            selected[selectedCount++] =
                topicIndex;

            h -=
                topics[topicIndex]
                    .requiredHours;
        }
    }

    printf(
        "\nAvailable Study Time : %d Hours\n\n",
        hours
    );

    printf("%-28s %-10s %-12s\n",
           "TOPIC",
           "HOURS",
           "PRIORITY");

    printf(
        "--------------------------------------------------------------------\n"
    );

    int usedHours = 0;

    for (int i = selectedCount - 1;
         i >= 0;
         i--)
    {
        int index =
            selected[i];

        printf(
            "%-28s %-10d %-12.2f\n",
            topics[index].name,
            topics[index].requiredHours,
            topics[index].priority
        );

        usedHours +=
            topics[index].requiredHours;
    }

    printf(
        "--------------------------------------------------------------------\n"
    );

    printf("Hours Used      : %d/%d\n",
           usedHours,
           hours);

    printf("Unused Hours    : %d\n",
           hours - usedHours);

    printf(
        "Learning Value  : %d\n",
        dp[candidateCount][hours]
    );

    printf(
        "\nAlgorithm Used  : 0/1 Knapsack\n"
    );

    printf(
        "Time Complexity : O(n * H)\n"
    );

    waitForEnter();
}

/* ============================================================
   NEXT RECOMMENDED TOPIC
   ============================================================ */

int prerequisitesReady(int target)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (graph[i][target] != 0)
        {
            if (topics[i].score < 60)
                return 0;
        }
    }

    return 1;
}

void showNextPriority()
{
    calculatePriority();

    printHeader(
        "NEXT RECOMMENDED TOPIC"
    );

    int best = -1;

    for (int i = 0; i < topicCount; i++)
    {
        if (!topics[i].completed &&
            prerequisitesReady(i))
        {
            if (best == -1 ||
                topics[i].priority >
                topics[best].priority)
            {
                best = i;
            }
        }
    }

    if (best == -1)
    {
        printf(
            YELLOW
            "\nNo topic is currently ready.\n"
            RESET
        );

        printf(
            "Complete weak prerequisites first.\n"
        );
    }
    else
    {
        printf(
            "\nRecommended Topic : "
            BOLD "%s" RESET "\n",
            topics[best].name
        );

        printf(
            "Current Score     : %d%%\n",
            topics[best].score
        );

        printf(
            "Priority Score    : %.2f\n",
            topics[best].priority
        );

        printf(
            "Study Time        : %d Hours\n",
            topics[best].requiredHours
        );
    }

    waitForEnter();
}

/* ============================================================
   ALGORITHM 4
   KMP STRING MATCHING
   ============================================================ */

/*
   LPS = Longest Proper Prefix
         which is also a Suffix.

   This table helps KMP avoid
   unnecessary repeated comparisons.
*/

void buildLPS(const char pattern[],
              int lps[])
{
    int length = 0;
    int i = 1;

    lps[0] = 0;

    while (pattern[i] != '\0')
    {
        if (pattern[i] ==
            pattern[length])
        {
            length++;

            lps[i] = length;

            i++;
        }
        else
        {
            if (length != 0)
            {
                length =
                    lps[length - 1];
            }
            else
            {
                lps[i] = 0;

                i++;
            }
        }
    }
}

/*
   Returns 1 if pattern occurs
   anywhere inside text.
*/

int KMPSearch(const char text[],
              const char pattern[])
{
    if (pattern[0] == '\0')
        return 0;

    int lps[50];

    buildLPS(pattern, lps);

    int i = 0;
    int j = 0;

    while (text[i] != '\0')
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;

            if (pattern[j] == '\0')
            {
                return 1;
            }
        }
        else
        {
            if (j != 0)
            {
                j =
                    lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return 0;
}

void searchTopicKMP()
{
    printHeader(
        "TOPIC SEARCH - KMP"
    );

    char pattern[50];

    printf(
        "\nEnter Topic Keyword: "
    );

    scanf(" %49[^\n]", pattern);

    int found = 0;

    printf(
        "\nMatching Topics:\n\n"
    );

    for (int i = 0;
         i < topicCount;
         i++)
    {
        if (KMPSearch(
                topics[i].name,
                pattern))
        {
            printf(
                "[%d] %-28s\n",
                topics[i].id,
                topics[i].name
            );

            found = 1;
        }
    }

    if (!found)
    {
        printf(
            YELLOW
            "No matching topic found.\n"
            RESET
        );
    }

    printf(
        "\nAlgorithm Used  : "
        "KMP String Matching\n"
    );

    printf(
        "Time Complexity : O(n + m)\n"
    );

    waitForEnter();
}

/* ============================================================
   ALGORITHM 5
   SUM OF SUBSETS USING BACKTRACKING
   ============================================================ */

/*
   Find combinations of topics whose
   required study hours exactly equal
   the target study hours.

   At every topic we have two choices:

   1. Include topic
   2. Exclude topic
*/

void findStudyCombinations(
    int index,
    int currentSum,
    int target,
    int selected[])
{
    /*
       Exact target achieved.
    */

    if (currentSum == target)
    {
        solutionCount++;

        printf(
            "\nPlan %d:\n",
            solutionCount
        );

        int totalHours = 0;

        for (int i = 0;
             i < topicCount;
             i++)
        {
            if (selected[i])
            {
                printf(
                    "  %-28s %d Hours\n",
                    topics[i].name,
                    topics[i].requiredHours
                );

                totalHours +=
                    topics[i].requiredHours;
            }
        }

        printf(
            "  Total Study Time: %d Hours\n",
            totalHours
        );

        return;
    }

    /*
       Pruning:
       Stop when no topics remain
       or target is exceeded.
    */

    if (index >= topicCount ||
        currentSum > target)
    {
        return;
    }

    /* ---------- INCLUDE ---------- */

    selected[index] = 1;

    findStudyCombinations(
        index + 1,

        currentSum +
            topics[index].requiredHours,

        target,

        selected
    );

    /* ---------- BACKTRACK ---------- */

    selected[index] = 0;

    /* ---------- EXCLUDE ---------- */

    findStudyCombinations(
        index + 1,
        currentSum,
        target,
        selected
    );
}

void exactStudyHoursPlanner()
{
    printHeader(
        "EXACT STUDY HOURS - BACKTRACKING"
    );

    printf(
        "\nAvailable Study Time: %d Hours\n",
        student.availableHours
    );

    printf(
        "\n%-5s %-28s %-10s\n",
        "ID",
        "TOPIC",
        "HOURS"
    );

    printf(
        "--------------------------------------------------\n"
    );

    for (int i = 0;
         i < topicCount;
         i++)
    {
        printf(
            "%-5d %-28s %-10d\n",
            topics[i].id,
            topics[i].name,
            topics[i].requiredHours
        );
    }

    int target;

    printf(
        "\nEnter Exact Study Hours: "
    );

    scanf("%d", &target);

    if (target <= 0)
    {
        printf(
            RED
            "\nStudy hours must be greater than 0.\n"
            RESET
        );

        waitForEnter();
        return;
    }

    if (target >
        student.availableHours)
    {
        printf(
            RED
            "\nYou only have %d available hours.\n"
            RESET,
            student.availableHours
        );

        waitForEnter();
        return;
    }

    int selected[MAX_TOPICS] = {0};

    solutionCount = 0;

    printf(
        "\nPossible Study Plans "
        "for Exactly %d Hours:\n",
        target
    );

    findStudyCombinations(
        0,
        0,
        target,
        selected
    );

    if (solutionCount == 0)
    {
        printf(
            YELLOW
            "\nNo exact combination found.\n"
            RESET
        );
    }
    else
    {
        printf(
            GREEN
            "\nTotal Possible Plans: %d\n"
            RESET,
            solutionCount
        );
    }

    printf(
        "\nAlgorithm Used   : "
        "Sum of Subsets Backtracking\n"
    );

    printf(
        "Worst Complexity : O(2^n)\n"
    );

    waitForEnter();
}

/* ============================================================
   RE-ASSESSMENT
   ============================================================ */

void reassessment()
{
    printHeader("RE-ASSESSMENT");

    for (int i = 0;
         i < topicCount;
         i++)
    {
        printf(
            "[%d] %-28s Current: %d%%\n",
            topics[i].id,
            topics[i].name,
            topics[i].score
        );
    }

    int id;
    int newScore;

    printf("\nSelect Topic ID: ");
    scanf("%d", &id);

    int index =
        findTopicIndex(id);

    if (index == -1)
    {
        printf(
            RED
            "Invalid Topic.\n"
            RESET
        );

        waitForEnter();
        return;
    }

    printf(
        "Enter New Assessment Score: "
    );

    scanf("%d", &newScore);

    if (newScore < 0 ||
        newScore > 100)
    {
        printf(
            RED
            "Invalid Score.\n"
            RESET
        );

        waitForEnter();
        return;
    }

    topics[index].previousScore =
        topics[index].score;

    topics[index].score =
        newScore;

    calculatePriority();

    int change =
        topics[index].score -
        topics[index].previousScore;

    printHeader("PROGRESS UPDATE");

    printf(
        "\nTopic          : %s\n",
        topics[index].name
    );

    printf(
        "Previous Score : %d%%\n",
        topics[index].previousScore
    );

    printf(
        "New Score      : %d%%\n",
        topics[index].score
    );

    printf(
        "Change         : %+d%%\n\n",
        change
    );

    if (change > 0)
    {
        printf(
            GREEN
            "Performance Improved!\n"
            RESET
        );
    }
    else if (change < 0)
    {
        printf(
            RED
            "Performance Decreased.\n"
            RESET
        );
    }
    else
    {
        printf(
            YELLOW
            "No Performance Change.\n"
            RESET
        );
    }

    waitForEnter();
}

/* ============================================================
   PROGRESS DASHBOARD
   ============================================================ */

void progressDashboard()
{
    calculatePriority();

    printHeader(
        "OVERALL PROGRESS DASHBOARD"
    );

    float total = 0;
    int mastered = 0;

    for (int i = 0;
         i < topicCount;
         i++)
    {
        total += topics[i].score;

        if (topics[i].completed)
            mastered++;
    }

    float average =
        total / topicCount;

    printf(
        "\nStudent         : "
        BOLD "%s" RESET "\n",
        student.name
    );

    printf(
        "Average Score   : %.2f%%\n",
        average
    );

    printf(
        "Mastered Topics : %d/%d\n\n",
        mastered,
        topicCount
    );

    printf(
        BOLD
        "TOPIC PROGRESS\n"
        RESET
    );

    printf(
        "----------------------------------------------------------------------\n"
    );

    for (int i = 0;
         i < topicCount;
         i++)
    {
        printf(
            "%-25s ",
            topics[i].name
        );

        progressBar(
            topics[i].score
        );

        printf(" ");

        printStatus(
            topics[i].score
        );

        printf("\n");
    }

    waitForEnter();
}

/* ============================================================
   STUDENT ANALYSIS MENU
   ============================================================ */

void studentAnalysisMenu()
{
    int choice;

    while (1)
    {
        printHeader(
            "PART 1 - STUDENT ANALYSIS"
        );

        printf("\n[1] View Topics\n");
        printf("[2] Take Assessment\n");
        printf("[3] Assessment Dashboard\n");
        printf("[4] Weak / Strong Analysis\n");
        printf("[5] Priority Ranking (Merge Sort)\n");
        printf("[6] Prerequisite Graph\n");
        printf("[7] Dependency Risk Detector\n");

        /* NEW */
        printf("[8] Search Topic (KMP)\n");

        printf("[9] Back\n");

        printf("\nSelect > ");
        scanf("%d", &choice);

        /*
           Options 3,4,5,7 require
           assessment data.
        */

        if ((((choice >= 3 &&
               choice <= 5) ||
              choice == 7)) &&
            !assessmentTaken)
        {
            printf(
                RED
                "\nTake Assessment First.\n"
                RESET
            );

            waitForEnter();
            continue;
        }

        switch (choice)
        {
            case 1:

                displayTopics();
                break;

            case 2:

                takeAssessment();
                break;

            case 3:

                assessmentDashboard();
                break;

            case 4:

                weakStrongAnalysis();
                break;

            case 5:

                priorityRanking();
                break;

            case 6:

                displayPrerequisiteGraph();
                break;

            case 7:

                dependencyRiskDetector();
                break;

            case 8:

                /* KMP */

                searchTopicKMP();
                break;

            case 9:

                return;

            default:

                printf(
                    RED
                    "\nInvalid Choice.\n"
                    RESET
                );

                waitForEnter();
        }
    }
}

/* ============================================================
   PERSONALIZED PLANNER MENU
   ============================================================ */

void plannerMenu()
{
    if (!assessmentTaken)
    {
        printHeader(
            "PERSONALIZED PLANNER"
        );

        printf(
            RED
            "\nComplete Assessment First.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    int choice;

    while (1)
    {
        printHeader(
            "PART 2 - PERSONALIZED PLANNER"
        );

        printf(
            "\n[1] Personalized Learning Path\n"
        );

        printf(
            "[2] Optimized Study Plan "
            "(Knapsack)\n"
        );

        printf(
            "[3] Shortest Learning Route "
            "(Dijkstra)\n"
        );

        printf(
            "[4] Next Recommended Topic\n"
        );

        /* NEW BACKTRACKING OPTION */

        printf(
            "[5] Exact Study Hours "
            "(Backtracking)\n"
        );

        printf("[6] Back\n");

        printf("\nSelect > ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                personalizedLearningPath();
                break;

            case 2:

                optimizedStudyPlan();
                break;

            case 3:

                shortestLearningRoute();
                break;

            case 4:

                showNextPriority();
                break;

            case 5:

                /*
                   Sum of Subsets
                   Backtracking
                */

                exactStudyHoursPlanner();
                break;

            case 6:

                return;

            default:

                printf(
                    RED
                    "\nInvalid Choice.\n"
                    RESET
                );

                waitForEnter();
        }
    }
}

/* ============================================================
   ADAPTIVE INTELLIGENCE MENU
   ============================================================ */

void adaptiveMenu()
{
    if (!assessmentTaken)
    {
        printHeader(
            "ADAPTIVE INTELLIGENCE"
        );

        printf(
            RED
            "\nComplete Assessment First.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    int choice;

    while (1)
    {
        printHeader(
            "PART 3 - ADAPTIVE INTELLIGENCE"
        );

        printf(
            "\n[1] Re-Assessment\n"
        );

        printf(
            "[2] View Updated Priority Ranking\n"
        );

        printf(
            "[3] Generate Updated Study Plan\n"
        );

        printf("[4] Back\n");

        printf("\nSelect > ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                reassessment();
                break;

            case 2:

                priorityRanking();
                break;

            case 3:

                optimizedStudyPlan();
                break;

            case 4:

                return;

            default:

                printf(
                    RED
                    "\nInvalid Choice.\n"
                    RESET
                );

                waitForEnter();
        }
    }
}

/* ============================================================
   MAIN PROGRAM
   ============================================================ */

int main()
{
    /*
       Step 1:
       Initialize course information.
    */

    initializeTopics();

    /*
       Step 2:
       Create prerequisite graph.
    */

    initializeGraph();

    /*
       Step 3:
       Create student profile.
    */

    enterStudentDetails();

    /*
       Step 4:
       Main application menu.
    */

    while (1)
    {
        printHeader(
            "PERSONALIZED LEARNING PATH PLANNER"
        );

        printf(
            "\nWelcome, "
            BOLD "%s" RESET "\n",
            student.name
        );

        printf(
            "Study Time: %d Hours | "
            "Target Score: %d%%\n",
            student.availableHours,
            student.targetScore
        );

        printf("\n");

        printf(
            "        [1]  STUDENT ANALYSIS\n\n"
        );

        printf(
            "        [2]  PERSONALIZED PLANNER\n\n"
        );

        printf(
            "        [3]  ADAPTIVE INTELLIGENCE\n\n"
        );

        printf(
            "        [4]  PROGRESS DASHBOARD\n\n"
        );

        printf(
            "        [5]  EXIT\n\n"
        );

        printLine();

        int choice;

        printf("Select Option > ");

        if (scanf("%d", &choice) != 1)
        {
            return 1;
        }

        switch (choice)
        {
            case 1:

                studentAnalysisMenu();
                break;

            case 2:

                plannerMenu();
                break;

            case 3:

                adaptiveMenu();
                break;

            case 4:

                if (!assessmentTaken)
                {
                    printf(
                        RED
                        "\nComplete Assessment First.\n"
                        RESET
                    );

                    waitForEnter();
                }
                else
                {
                    progressDashboard();
                }

                break;

            case 5:

                printHeader("GOODBYE");

                printf(
                    GREEN
                    "\nThank you for using the "
                    "Personalized Learning Planner.\n\n"
                    RESET
                );

                return 0;

            default:

                printf(
                    RED
                    "\nInvalid Option.\n"
                    RESET
                );

                waitForEnter();
        }
    }

    return 0;
}