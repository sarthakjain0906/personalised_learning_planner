#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOPICS 20
#define MAX_HOURS 100

/* ================= COLORS ================= */

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

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

int graph[MAX_TOPICS][MAX_TOPICS] = {0};

int assessmentTaken = 0;

/* ============================================================
   UI FUNCTIONS
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

    printf(
        "\n" CYAN
        "Press ENTER to continue..."
        RESET
    );

    while (
        (c = getchar()) != '\n'
        &&
        c != EOF
    )
    {
    }

    getchar();
}

void printLine()
{
    printf(
        CYAN
        "======================================================================\n"
        RESET
    );
}

void printHeader(const char title[])
{
    clearScreen();

    printLine();

    printf(
        BOLD CYAN
        "                 %s\n"
        RESET,
        title
    );

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
   KNOWLEDGE LEVEL
   ============================================================ */

const char *getLevel(int score)
{
    if (score >= 80)
        return "STRONG";

    if (score >= 60)
        return "GOOD";

    if (score >= 40)
        return "WEAK";

    return "VERY WEAK";
}

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
       Greedy -> Dynamic Programming
       DP -> Graph Basics
       Graph Basics -> Dijkstra
       Graph Basics -> MST
    */

    graph[0][1] = 1;

    graph[1][2] = 1;

    graph[2][3] = 1;

    graph[3][4] = 1;

    graph[4][5] = 1;

    graph[4][6] = 1;
}

/* ============================================================
   BASIC FUNCTIONS
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

int maxValue(int a, int b)
{
    return (a > b) ? a : b;
}

/* ============================================================
   PRIORITY CALCULATION
   ============================================================ */

void calculatePriority()
{
    for (int i = 0; i < topicCount; i++)
    {
        int weakness =
            100 - topics[i].score;

        int difficultyScore =
            topics[i].difficulty * 20;

        topics[i].priority =
            0.6f * weakness
            +
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
    printHeader(
        "STUDENT PROFILE"
    );

    printf(
        "\nStudent Name          : "
    );

    scanf(
        " %49[^\n]",
        student.name
    );

    do
    {
        printf(
            "Available Study Hours : "
        );

        scanf(
            "%d",
            &student.availableHours
        );

    }
    while (
        student.availableHours <= 0
        ||
        student.availableHours > MAX_HOURS
    );

    do
    {
        printf(
            "Target Score          : "
        );

        scanf(
            "%d",
            &student.targetScore
        );

    }
    while (
        student.targetScore < 0
        ||
        student.targetScore > 100
    );

    printf(
        "\n" GREEN
        "Profile Created Successfully!"
        RESET "\n"
    );

    waitForEnter();
}

/* ============================================================
   DISPLAY TOPICS
   ============================================================ */

void displayTopics()
{
    printHeader(
        "COURSE TOPICS"
    );

    printf(
        "\n%-5s %-28s %-12s %-10s\n",
        "ID",
        "TOPIC",
        "DIFFICULTY",
        "HOURS"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "%-5d %-28s %-12d %-10d\n",
            topics[i].id,
            topics[i].name,
            topics[i].difficulty,
            topics[i].requiredHours
        );
    }

    waitForEnter();
}

/* ============================================================
   PART 1 - ASSESSMENT
   ============================================================ */

void takeAssessment()
{
    printHeader(
        "STUDENT ASSESSMENT"
    );

    printf(
        "\nEnter score from 0 to 100 for each topic.\n\n"
    );

    for (int i = 0; i < topicCount; i++)
    {
        do
        {
            printf(
                "%-28s : ",
                topics[i].name
            );

            scanf(
                "%d",
                &topics[i].score
            );

            if (
                topics[i].score < 0
                ||
                topics[i].score > 100
            )
            {
                printf(
                    RED
                    "Invalid score. Use 0-100.\n"
                    RESET
                );
            }

        }
        while (
            topics[i].score < 0
            ||
            topics[i].score > 100
        );

        topics[i].previousScore =
            topics[i].score;
    }

    assessmentTaken = 1;

    calculatePriority();

    printf(
        "\n" GREEN
        "Assessment Completed Successfully!"
        RESET "\n"
    );

    waitForEnter();
}

/* ============================================================
   ASSESSMENT DASHBOARD
   ============================================================ */

void assessmentDashboard()
{
    printHeader(
        "STUDENT ANALYSIS"
    );

    printf(
        "\nStudent      : "
        BOLD "%s" RESET "\n",
        student.name
    );

    printf(
        "Target Score : %d%%\n\n",
        student.targetScore
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "%-25s ",
            topics[i].name
        );

        progressBar(
            topics[i].score
        );

        printf("  ");

        printStatus(
            topics[i].score
        );

        printf("\n");
    }

    waitForEnter();
}

/* ============================================================
   WEAK / STRONG ANALYSIS
   ============================================================ */

void weakStrongAnalysis()
{
    printHeader(
        "WEAK / STRONG ANALYSIS"
    );

    int found;

    printf(
        GREEN
        "\nSTRONG TOPICS\n"
        RESET
    );

    found = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].score >= 80)
        {
            printf(
                "  %-28s %d%%\n",
                topics[i].name,
                topics[i].score
            );

            found = 1;
        }
    }

    if (!found)
        printf("  None\n");


    printf(
        CYAN
        "\nGOOD TOPICS\n"
        RESET
    );

    found = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (
            topics[i].score >= 60
            &&
            topics[i].score < 80
        )
        {
            printf(
                "  %-28s %d%%\n",
                topics[i].name,
                topics[i].score
            );

            found = 1;
        }
    }

    if (!found)
        printf("  None\n");


    printf(
        YELLOW
        "\nWEAK TOPICS\n"
        RESET
    );

    found = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (
            topics[i].score >= 40
            &&
            topics[i].score < 60
        )
        {
            printf(
                "  %-28s %d%%\n",
                topics[i].name,
                topics[i].score
            );

            found = 1;
        }
    }

    if (!found)
        printf("  None\n");


    printf(
        RED
        "\nVERY WEAK TOPICS\n"
        RESET
    );

    found = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].score < 40)
        {
            printf(
                "  %-28s %d%%\n",
                topics[i].name,
                topics[i].score
            );

            found = 1;
        }
    }

    if (!found)
        printf("  None\n");

    waitForEnter();
}

/* ============================================================
   PRIORITY ANALYSIS
   ============================================================ */

void displayPriorities()
{
    calculatePriority();

    printHeader(
        "TOPIC PRIORITY ANALYSIS"
    );

    printf(
        "\n%-28s %-8s %-10s %-12s\n",
        "TOPIC",
        "SCORE",
        "PRIORITY",
        "STATUS"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "%-28s %-8d %-10.2f ",
            topics[i].name,
            topics[i].score,
            topics[i].priority
        );

        if (topics[i].completed)
        {
            printf(
                GREEN
                "MASTERED"
                RESET
            );
        }

        else if (
            topics[i].priority >= 70
        )
        {
            printf(
                RED
                "HIGH"
                RESET
            );
        }

        else if (
            topics[i].priority >= 50
        )
        {
            printf(
                YELLOW
                "MEDIUM"
                RESET
            );
        }

        else
        {
            printf(
                CYAN
                "LOW"
                RESET
            );
        }

        printf("\n");
    }

    waitForEnter();
}

/* ============================================================
   PREREQUISITE GRAPH
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
            if (graph[i][j])
            {
                printf(
                    "%-28s ---> %s\n",
                    topics[i].name,
                    topics[j].name
                );
            }
        }
    }

    printf(
        "\nA ---> B means A should be understood before B.\n"
    );

    waitForEnter();
}

/* ============================================================
   DEPENDENCY CHECK
   ============================================================ */

void checkDependencies(
    int target,
    int visited[],
    int *risk)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (
            graph[i][target]
            &&
            !visited[i]
        )
        {
            visited[i] = 1;

            checkDependencies(
                i,
                visited,
                risk
            );

            printf(
                "%-28s %3d%%  ",
                topics[i].name,
                topics[i].score
            );

            if (
                topics[i].score < 40
            )
            {
                printf(
                    RED
                    "HIGH RISK"
                    RESET
                    "\n"
                );

                if (*risk < 2)
                    *risk = 2;
            }

            else if (
                topics[i].score < 60
            )
            {
                printf(
                    YELLOW
                    "MEDIUM RISK"
                    RESET
                    "\n"
                );

                if (*risk < 1)
                    *risk = 1;
            }

            else
            {
                printf(
                    GREEN
                    "SAFE"
                    RESET
                    "\n"
                );
            }
        }
    }
}

/* ============================================================
   DEPENDENCY RISK DETECTOR
   ============================================================ */

void dependencyRiskDetector()
{
    printHeader(
        "DEPENDENCY RISK DETECTOR"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "[%d] %-28s %d%%\n",
            topics[i].id,
            topics[i].name,
            topics[i].score
        );
    }

    int id;

    printf(
        "\nSelect Target Topic ID: "
    );

    scanf(
        "%d",
        &id
    );

    int target =
        findTopicIndex(id);

    if (target == -1)
    {
        printf(
            RED
            "\nInvalid Topic ID.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    int visited[MAX_TOPICS] =
        {0};

    int risk = 0;

    printf(
        "\nTarget: "
        BOLD "%s" RESET "\n\n",
        topics[target].name
    );

    printf(
        "Prerequisite Analysis:\n\n"
    );

    checkDependencies(
        target,
        visited,
        &risk
    );

    printf(
        "\n--------------------------------------------------------------------\n"
    );

    if (risk == 2)
    {
        printf(
            RED
            "OVERALL DEPENDENCY RISK: HIGH\n"
            RESET
        );

        printf(
            "Complete weak prerequisites first.\n"
        );
    }

    else if (risk == 1)
    {
        printf(
            YELLOW
            "OVERALL DEPENDENCY RISK: MEDIUM\n"
            RESET
        );

        printf(
            "Revise prerequisites before continuing.\n"
        );
    }

    else
    {
        printf(
            GREEN
            "OVERALL DEPENDENCY RISK: LOW\n"
            RESET
        );

        printf(
            "You can proceed with the topic.\n"
        );
    }

    waitForEnter();
}

/* ============================================================
   PART 2 - LEARNING PATH
   ============================================================ */

void buildLearningPath(
    int target,
    int visited[],
    int path[],
    int *count)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (
            graph[i][target]
            &&
            !visited[i]
        )
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

        if (
            !topics[target].completed
        )
        {
            path[*count] =
                target;

            (*count)++;
        }
    }
}

/* ============================================================
   PERSONALIZED LEARNING PATH
   ============================================================ */

void personalizedLearningPath()
{
    calculatePriority();

    printHeader(
        "PERSONALIZED LEARNING PATH"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "[%d] %-28s %d%%\n",
            topics[i].id,
            topics[i].name,
            topics[i].score
        );
    }

    int id;

    printf(
        "\nSelect Final Target Topic: "
    );

    scanf(
        "%d",
        &id
    );

    int target =
        findTopicIndex(id);

    if (target == -1)
    {
        printf(
            RED
            "\nInvalid Topic.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    int visited[MAX_TOPICS] =
        {0};

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

    printf(
        "\nStudent : %s\n",
        student.name
    );

    printf(
        "Target  : %s\n\n",
        topics[target].name
    );

    if (count == 0)
    {
        printf(
            GREEN
            "Target and prerequisites are already mastered.\n"
            RESET
        );
    }

    else
    {
        for (int i = 0; i < count; i++)
        {
            int index =
                path[i];

            printf(
                "%d. "
                BOLD "%s" RESET,
                i + 1,
                topics[index].name
            );

            printf(
                "  Score: %d%%  Priority: %.2f\n",
                topics[index].score,
                topics[index].priority
            );

            if (
                i < count - 1
            )
            {
                printf(
                    "        |\n"
                );

                printf(
                    "        v\n"
                );
            }
        }
    }

    waitForEnter();
}

/* ============================================================
   0/1 KNAPSACK STUDY OPTIMIZER
   ============================================================ */

void generateKnapsackPlan(
    int availableHours)
{
    calculatePriority();

    if (
        availableHours <= 0
        ||
        availableHours > MAX_HOURS
    )
    {
        printf(
            RED
            "\nInvalid study hours.\n"
            RESET
        );

        return;
    }

    Topic candidates[MAX_TOPICS];

    int candidateCount = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (
            !topics[i].completed
        )
        {
            candidates[candidateCount++] =
                topics[i];
        }
    }

    if (candidateCount == 0)
    {
        printf(
            GREEN
            "\nAll topics are mastered.\n"
            RESET
        );

        return;
    }

    int dp[MAX_TOPICS + 1]
          [MAX_HOURS + 1];

    memset(
        dp,
        0,
        sizeof(dp)
    );

    for (
        int i = 1;
        i <= candidateCount;
        i++
    )
    {
        for (
            int h = 0;
            h <= availableHours;
            h++
        )
        {
            int hours =
                candidates[i - 1]
                    .requiredHours;

            int value =
                (int)
                candidates[i - 1]
                    .priority;

            if (
                hours <= h
            )
            {
                dp[i][h] =
                    maxValue(
                        dp[i - 1][h],

                        value
                        +
                        dp[i - 1]
                          [h - hours]
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

    int value =
        dp[candidateCount]
          [availableHours];

    int hoursLeft =
        availableHours;

    for (
        int i = candidateCount;
        i > 0 && value > 0;
        i--
    )
    {
        if (
            value !=
            dp[i - 1][hoursLeft]
        )
        {
            selected[selectedCount++] =
                i - 1;

            value -=
                (int)
                candidates[i - 1]
                    .priority;

            hoursLeft -=
                candidates[i - 1]
                    .requiredHours;
        }
    }

    printf(
        "\nAvailable Time : %d Hours\n",
        availableHours
    );

    printf(
        "Learning Value : %d\n\n",
        dp[candidateCount]
          [availableHours]
    );

    printf(
        "%-28s %-10s %-12s\n",
        "TOPIC",
        "HOURS",
        "PRIORITY"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );

    int usedHours = 0;

    for (
        int i = selectedCount - 1;
        i >= 0;
        i--
    )
    {
        int index =
            selected[i];

        printf(
            "%-28s %-10d %-12.2f\n",
            candidates[index].name,
            candidates[index].requiredHours,
            candidates[index].priority
        );

        usedHours +=
            candidates[index]
                .requiredHours;
    }

    printf(
        "--------------------------------------------------------------------\n"
    );

    printf(
        "Topics Selected : %d\n",
        selectedCount
    );

    printf(
        "Hours Used      : %d/%d\n",
        usedHours,
        availableHours
    );

    printf(
        "Unused Hours    : %d\n",
        availableHours -
        usedHours
    );
}

/* ============================================================
   OPTIMIZED STUDY PLAN
   ============================================================ */

void optimizedStudyPlan()
{
    printHeader(
        "OPTIMIZED STUDY PLAN"
    );

    generateKnapsackPlan(
        student.availableHours
    );

    waitForEnter();
}

/* ============================================================
   EXPLAINABLE RECOMMENDATION
   ============================================================ */

void explainRecommendation()
{
    calculatePriority();

    printHeader(
        "EXPLAINABLE RECOMMENDATION"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "[%d] %-28s %d%%\n",
            topics[i].id,
            topics[i].name,
            topics[i].score
        );
    }

    int id;

    printf(
        "\nSelect Topic ID: "
    );

    scanf(
        "%d",
        &id
    );

    int index =
        findTopicIndex(id);

    if (index == -1)
    {
        printf(
            RED
            "\nInvalid Topic.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    printHeader(
        "WHY THIS TOPIC?"
    );

    printf(
        "\nTopic           : "
        BOLD "%s" RESET "\n",
        topics[index].name
    );

    printf(
        "Current Score   : %d%%\n",
        topics[index].score
    );

    printf(
        "Knowledge Level : "
    );

    printStatus(
        topics[index].score
    );

    printf(
        "\nDifficulty      : %d/5\n",
        topics[index].difficulty
    );

    printf(
        "Required Time   : %d Hours\n",
        topics[index].requiredHours
    );

    printf(
        "Priority Score  : %.2f\n\n",
        topics[index].priority
    );

    printf(
        BOLD
        "WHY?\n"
        RESET
    );

    if (
        topics[index].score < 40
    )
    {
        printf(
            "- Assessment performance is very weak.\n"
        );
    }

    else if (
        topics[index].score < 60
    )
    {
        printf(
            "- Assessment performance is weak.\n"
        );
    }

    else if (
        topics[index].score < 80
    )
    {
        printf(
            "- Topic still needs improvement.\n"
        );
    }

    else
    {
        printf(
            "- Topic is already strongly understood.\n"
        );
    }

    if (
        topics[index].difficulty >= 4
    )
    {
        printf(
            "- This is a high-difficulty topic.\n"
        );
    }

    int important = 0;

    for (int i = 0; i < topicCount; i++)
    {
        if (
            graph[index][i]
        )
        {
            printf(
                "- It is required before learning %s.\n",
                topics[i].name
            );

            important = 1;
        }
    }

    printf(
        "\nFINAL RECOMMENDATION: "
    );

    if (
        topics[index].completed
    )
    {
        printf(
            GREEN
            "LOW PRIORITY - MASTERED"
            RESET
            "\n"
        );
    }

    else if (
        topics[index].priority >= 70
        ||
        important
    )
    {
        printf(
            RED
            "HIGH PRIORITY"
            RESET
            "\n"
        );
    }

    else
    {
        printf(
            YELLOW
            "MEDIUM PRIORITY"
            RESET
            "\n"
        );
    }

    waitForEnter();
}

/* ============================================================
   NEXT PRIORITY
   ============================================================ */

int getNextPriorityIndex()
{
    calculatePriority();

    int best = -1;

    for (int i = 0; i < topicCount; i++)
    {
        if (
            !topics[i].completed
            &&
            (
                best == -1
                ||
                topics[i].priority >
                topics[best].priority
            )
        )
        {
            best = i;
        }
    }

    return best;
}

void showNextPriority()
{
    printHeader(
        "NEXT RECOMMENDED TOPIC"
    );

    int best =
        getNextPriorityIndex();

    if (best == -1)
    {
        printf(
            GREEN
            "\nAll Topics Mastered!\n"
            RESET
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
   PART 3 - RE-ASSESSMENT
   ============================================================ */

void reassessment()
{
    printHeader(
        "RE-ASSESSMENT"
    );

    for (int i = 0; i < topicCount; i++)
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

    printf(
        "\nSelect Topic ID: "
    );

    scanf(
        "%d",
        &id
    );

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

    scanf(
        "%d",
        &newScore
    );

    if (
        newScore < 0
        ||
        newScore > 100
    )
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
        topics[index].score
        -
        topics[index].previousScore;

    printHeader(
        "PROGRESS UPDATE"
    );

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

    printf(
        "Before : "
    );

    progressBar(
        topics[index].previousScore
    );

    printf(
        "\nAfter  : "
    );

    progressBar(
        topics[index].score
    );

    printf("\n\n");

    if (change > 0)
    {
        printf(
            GREEN
            "Performance Improved!"
            RESET
            "\n"
        );
    }

    else if (change < 0)
    {
        printf(
            RED
            "Performance Decreased."
            RESET
            "\n"
        );
    }

    else
    {
        printf(
            YELLOW
            "No Performance Change."
            RESET
            "\n"
        );
    }

    printf(
        "Current Status : "
    );

    printStatus(
        topics[index].score
    );

    printf("\n");

    waitForEnter();
}

/* ============================================================
   PROGRESS COMPARISON
   ============================================================ */

void progressComparison()
{
    printHeader(
        "PROGRESS COMPARISON"
    );

    printf(
        "\n%-25s %-10s %-10s %-10s %-15s\n",
        "TOPIC",
        "PREVIOUS",
        "CURRENT",
        "CHANGE",
        "STATUS"
    );

    printf(
        "----------------------------------------------------------------------\n"
    );

    for (int i = 0; i < topicCount; i++)
    {
        int difference =
            topics[i].score
            -
            topics[i].previousScore;

        printf(
            "%-25s %-10d %-10d %+10d ",
            topics[i].name,
            topics[i].previousScore,
            topics[i].score,
            difference
        );

        if (difference > 0)
        {
            printf(
                GREEN
                "IMPROVED"
                RESET
            );
        }

        else if (
            difference < 0
        )
        {
            printf(
                RED
                "DECREASED"
                RESET
            );
        }

        else
        {
            printf(
                YELLOW
                "NO CHANGE"
                RESET
            );
        }

        printf("\n");
    }

    waitForEnter();
}

/* ============================================================
   ADAPTIVE RE-PLANNING
   ============================================================ */

void adaptiveReplanning()
{
    printHeader(
        "ADAPTIVE RE-PLANNING"
    );

    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "[%d] %-28s %d%%\n",
            topics[i].id,
            topics[i].name,
            topics[i].score
        );
    }

    int id;
    int newScore;

    printf(
        "\nTopic Recently Studied: "
    );

    scanf(
        "%d",
        &id
    );

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

    int oldScore =
        topics[index].score;

    printf(
        "Enter New Assessment Score: "
    );

    scanf(
        "%d",
        &newScore
    );

    if (
        newScore < 0
        ||
        newScore > 100
    )
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
        oldScore;

    topics[index].score =
        newScore;

    calculatePriority();

    printHeader(
        "ADAPTIVE PLAN UPDATED"
    );

    printf(
        "\nTopic       : %s\n",
        topics[index].name
    );

    printf(
        "Old Score   : %d%%\n",
        oldScore
    );

    printf(
        "New Score   : %d%%\n",
        newScore
    );

    printf(
        "Improvement : %+d%%\n",
        newScore -
        oldScore
    );

    printf(
        "New Priority: %.2f\n",
        topics[index].priority
    );

    printf(
        "Status      : "
    );

    if (
        topics[index].completed
    )
    {
        printf(
            GREEN
            "MASTERED"
            RESET
            "\n"
        );
    }

    else
    {
        printStatus(
            topics[index].score
        );

        printf("\n");
    }

    int best =
        getNextPriorityIndex();

    if (best >= 0)
    {
        printf(
            "\n"
            BOLD
            "NEW NEXT PRIORITY\n"
            RESET
        );

        printf(
            "%s | Score %d%% | Priority %.2f\n",
            topics[best].name,
            topics[best].score,
            topics[best].priority
        );
    }

    printf(
        "\n"
        BOLD
        "UPDATED OPTIMIZED PLAN\n"
        RESET
    );

    generateKnapsackPlan(
        student.availableHours
    );

    waitForEnter();
}

/* ============================================================
   WHAT-IF SIMULATOR
   ============================================================ */

void whatIfSimulator()
{
    printHeader(
        "WHAT-IF STUDY SIMULATOR"
    );

    printf(
        "\n[1] Custom Study Hours\n"
    );

    printf(
        "[2] Compare 5 / 10 / 15 / 20 Hours\n"
    );

    int choice;

    printf(
        "\nSelect > "
    );

    scanf(
        "%d",
        &choice
    );

    if (choice == 1)
    {
        int hours;

        printf(
            "Hypothetical Study Hours: "
        );

        scanf(
            "%d",
            &hours
        );

        if (
            hours <= 0
            ||
            hours > MAX_HOURS
        )
        {
            printf(
                RED
                "Invalid Hours.\n"
                RESET
            );

            waitForEnter();

            return;
        }

        printHeader(
            "WHAT-IF RESULT"
        );

        generateKnapsackPlan(
            hours
        );

        waitForEnter();
    }

    else if (choice == 2)
    {
        int scenarios[] =
            {5, 10, 15, 20};

        printHeader(
            "WHAT-IF COMPARISON"
        );

        for (int i = 0; i < 4; i++)
        {
            printf(
                "\n"
                BOLD
                "-------------------- %d HOURS --------------------\n"
                RESET,
                scenarios[i]
            );

            generateKnapsackPlan(
                scenarios[i]
            );
        }

        waitForEnter();
    }

    else
    {
        printf(
            RED
            "Invalid Choice.\n"
            RESET
        );

        waitForEnter();
    }
}

/* ============================================================
   OVERALL PROGRESS DASHBOARD
   ONLY USED FROM MAIN MENU
   ============================================================ */

void progressDashboard()
{
    calculatePriority();

    printHeader(
        "OVERALL PROGRESS DASHBOARD"
    );

    int mastered = 0;

    int weak = 0;

    float total = 0;

    for (int i = 0; i < topicCount; i++)
    {
        total +=
            topics[i].score;

        if (
            topics[i].completed
        )
        {
            mastered++;
        }

        if (
            topics[i].score < 60
        )
        {
            weak++;
        }
    }

    float average =
        total /
        topicCount;

    float mastery =
        (
            (float)
            mastered /
            topicCount
        )
        *
        100;

    printf(
        "\nStudent             : "
        BOLD "%s" RESET "\n",
        student.name
    );

    printf(
        "Average Score       : %.2f%%\n",
        average
    );

    printf(
        "Mastered Topics     : %d/%d\n",
        mastered,
        topicCount
    );

    printf(
        "Topics Needing Work : %d\n",
        weak
    );

    printf(
        "Overall Mastery     : "
    );

    progressBar(
        (int)mastery
    );

    printf(
        "\n\n"
        BOLD
        "TOPIC PROGRESS\n"
        RESET
    );

    printf(
        "----------------------------------------------------------------------\n"
    );

    for (int i = 0; i < topicCount; i++)
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
   PART 1 MENU
   ============================================================ */

void part1Menu()
{
    int choice;

    while (1)
    {
        printHeader(
            "PART 1 - STUDENT ANALYSIS"
        );

        printf(
            "\n[1] View Topics\n"
        );

        printf(
            "[2] Take Assessment\n"
        );

        printf(
            "[3] Assessment Dashboard\n"
        );

        printf(
            "[4] Weak / Strong Analysis\n"
        );

        printf(
            "[5] Topic Priority Analysis\n"
        );

        printf(
            "[6] Prerequisite Graph\n"
        );

        printf(
            "[7] Dependency Risk Detector\n"
        );

        printf(
            "[8] Back\n"
        );

        printf(
            "\nSelect > "
        );

        scanf(
            "%d",
            &choice
        );

        if (
            (
                choice == 3
                ||
                choice == 4
                ||
                choice == 5
                ||
                choice == 7
            )
            &&
            !assessmentTaken
        )
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

                displayPriorities();

                break;


            case 6:

                displayPrerequisiteGraph();

                break;


            case 7:

                dependencyRiskDetector();

                break;


            case 8:

                return;


            default:

                printf(
                    RED
                    "Invalid Choice.\n"
                    RESET
                );

                waitForEnter();
        }
    }
}

/* ============================================================
   PART 2 MENU
   ============================================================ */

void part2Menu()
{
    if (!assessmentTaken)
    {
        printHeader(
            "PERSONALIZED PLANNER"
        );

        printf(
            RED
            "\nComplete Part 1 Assessment First.\n"
            RESET
        );

        waitForEnter();

        return;
    }

    int choice;

    while (1)
    {
        printHeader(
            "PART 2 - PERSONALIZED PLANNING"
        );

        printf(
            "\n[1] Personalized Learning Path\n"
        );

        printf(
            "[2] Optimized Study Plan\n"
        );

        printf(
            "[3] Explain Recommendation\n"
        );

        printf(
            "[4] Next Recommended Topic\n"
        );

        printf(
            "[5] Back\n"
        );

        printf(
            "\nSelect > "
        );

        scanf(
            "%d",
            &choice
        );

        switch (choice)
        {
            case 1:

                personalizedLearningPath();

                break;


            case 2:

                optimizedStudyPlan();

                break;


            case 3:

                explainRecommendation();

                break;


            case 4:

                showNextPriority();

                break;


            case 5:

                return;


            default:

                printf(
                    RED
                    "Invalid Choice.\n"
                    RESET
                );

                waitForEnter();
        }
    }
}

/* ============================================================
   PART 3 MENU
   PROGRESS DASHBOARD REMOVED FROM HERE
   ============================================================ */

void part3Menu()
{
    if (!assessmentTaken)
    {
        printHeader(
            "ADAPTIVE INTELLIGENCE"
        );

        printf(
            RED
            "\nComplete Part 1 Assessment First.\n"
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
            "[2] Progress Comparison\n"
        );

        printf(
            "[3] Adaptive Re-Planning\n"
        );

        printf(
            "[4] What-If Study Simulator\n"
        );

        printf(
            "[5] Back\n"
        );

        printf(
            "\nSelect > "
        );

        scanf(
            "%d",
            &choice
        );

        switch (choice)
        {
            case 1:

                reassessment();

                break;


            case 2:

                progressComparison();

                break;


            case 3:

                adaptiveReplanning();

                break;


            case 4:

                whatIfSimulator();

                break;


            case 5:

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
    initializeTopics();

    initializeGraph();

    enterStudentDetails();

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
            "Study Time: %d Hours | Target Score: %d%%\n",
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

        printf(
            "Select Option > "
        );

        int choice;

        if (
            scanf(
                "%d",
                &choice
            ) != 1
        )
        {
            return 1;
        }

        switch (choice)
        {
            case 1:

                part1Menu();

                break;


            case 2:

                part2Menu();

                break;


            case 3:

                part3Menu();

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

                printHeader(
                    "GOODBYE"
                );

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