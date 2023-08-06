// Willian Wiegand

#include <stdio.h>
#include <stdlib.h>

int count_students_unable_to_eat(int students[], int sandwiches[], int num_students) {
    int queue[num_students];
    int stack[num_students];

    for (int i = 0; i < num_students; i++) {
        queue[i] = students[i];
        stack[i] = sandwiches[i];
    }
  
    while (num_students > 0) {
        if (queue[0] == stack[0]) {
            for (int i = 1; i < num_students; i++) {
                queue[i - 1] = queue[i];
                stack[i - 1] = stack[i];
            }
            num_students--;
        } else {
            int temp = queue[0];
            for (int i = 1; i < num_students; i++) {
                queue[i - 1] = queue[i];
            }
            queue[num_students - 1] = temp;
        }

        int all_same = 1;
        for (int i = 1; i < num_students; i++) {
            if (queue[i] != queue[0]) {
                all_same = 0;
                break;
            }
        }
        if (all_same) {
            return num_students;
        }
    }

    return 0;
}

int main() {
    int students1[] = {1,1,0,0};
    int sandwiches1[] = {0,1,0,1};
    int num_students1 = sizeof(students1) / sizeof(students1[0]);
    printf("%d\n", count_students_unable_to_eat(students1, sandwiches1, num_students1));  
    return 0;
}
