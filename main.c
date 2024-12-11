#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"
#include "task8.h"
#include "task9.h"

typedef int (task_func) (int, char**);

int main(int argc, char** argv) {
    task_func* tasks[9] = {
            task_1,
            task_2,
            task_3,
            task_4,
            task_5,
            task_6,
            task_7,
            task_8,
            task_9
    };

    int task_choice;
    printf("Choose task: ");
    scanf("%d", &task_choice);

    return tasks[task_choice - 1](argc, argv);
}