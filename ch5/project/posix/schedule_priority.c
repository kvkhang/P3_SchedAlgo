#include "schedulers.h"
#include "list.h"
#include "task.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node **g_head = NULL;

// add a task to the list
void add(char *name, int priority, int burst)
{
    Task *currTask = (Task *)malloc(sizeof(Task));
    currTask->name = name;
    currTask->priority = priority;
    currTask->burst = burst;
    insert(&g_head, currTask);
}

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// based on traverse from list.c
// finds the task whose name comes first in dictionary
Task *pickNextTask()
{
    // if list is empty, nothing to do
    if (!g_head)
        return NULL;

    struct node *temp;
    temp = g_head;
    Task *best_sofar = temp->task;

    while (temp != NULL)
    {
        if (temp->task->priority > best_sofar->priority)
            best_sofar = temp->task;
        else if (temp->task->priority == best_sofar->priority && comesBefore(temp->task->name, best_sofar->name))
        {
            best_sofar = temp->task;
        }
        temp = temp->next;
    }
    // delete the node from list, Task will get deleted later
    delete (&g_head, best_sofar);
    return best_sofar;
}
// invoke the scheduler
void schedule()
{
    int totalTime_ = 0;
    while (g_head != NULL)
    {
        Task *nextTask_ = pickNextTask();
        totalTime_ += nextTask_->burst;
        printf("Running Task = [%s] [%d] [%d] for %d units.\n        Time is now: %d\n", nextTask_->name, nextTask_->priority, nextTask_->burst, nextTask_->burst, totalTime_);
    }
}
