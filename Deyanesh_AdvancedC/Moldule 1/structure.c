#include <stdio.h>
#include <string.h>

struct Day {
    char dayName[10];
    char tasks[3][100]; // 3 tasks, each up to 99 characters
};

int main() {
    struct Day week[7];

    // Step 1: Assign day names
    strcpy(week[0].dayName, "Monday");
    strcpy(week[1].dayName, "Tuesday");
    strcpy(week[2].dayName, "Wednesday");
    strcpy(week[3].dayName, "Thursday");
    strcpy(week[4].dayName, "Friday");
    strcpy(week[5].dayName, "Saturday");
    strcpy(week[6].dayName, "Sunday");

    // Step 2: Take input for 3 tasks per day
    for (int i = 0; i < 7; i++) {
        printf("\nEnter 3 tasks for %s:\n", week[i].dayName);
        for (int j = 0; j < 3; j++) {
            printf("  Task %d: ", j + 1);
            fgets(week[i].tasks[j], 100, stdin);
            
        }
    }

    // Step 3: Display all tasks
    printf("\n===== Weekly Tasks =====\n");
    for (int i = 0; i < 7; i++) {
        printf("\n%s:\n", week[i].dayName);
        for (int j = 0; j < 3; j++) {
            printf("  - %s\n", week[i].tasks[j]);
        }
    }

    return 0;
}
