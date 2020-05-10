/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks, at the end
void insertAtEnd(struct Node **head, Task *newTask) {
    //printf("Insert at end");
    struct Node *new_node = malloc(sizeof(struct Node));

    new_node -> task = newTask;
    new_node -> next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct Node *temp;
    temp = *head;

    //Traverse until the end of the list is found
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp -> next = new_node;
}

struct Node* initList(Task *newTask) {
    struct Node* first = malloc (sizeof(struct Node));
    first -> task = newTask;
    (first -> next) = NULL;  
    return first;
}
void insertAtFront(struct Node **head, Task *newTask) {
    // add the new task to the list 
    struct Node *newNode = malloc(sizeof(struct Node));
    //printf("adding to list: [%s] [%d] [%d]\n",newTask->name, newTask->priority, newTask->burst);
    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

void insertAfter(struct Node **prev_node, Task *new_task) {
    if (prev_node == NULL) {
        printf("Previous Node is null. Unable to add.");
        return;
    }
    struct Node *new_node = malloc(sizeof(struct Node));

    new_node->task = new_task;
    new_node->next = (*prev_node) -> next;
    (*prev_node) -> next = new_node;
}
// delete the selected task from the list
void delete(struct Node **head, Task *task) {
    struct Node *temp;
    struct Node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
    }
}

// print the list
void print(struct Node *head) {
    printf("Init print\n");
    struct Node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
