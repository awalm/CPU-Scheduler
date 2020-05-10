/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct Node {
    Task *task;
    struct Node *next;
};

// insert and delete operations.
void insertAtEnd(struct Node **head, Task *task);
void insertAtFront(struct Node **head, Task *newTask);
//void insertBefore(struct Node **head, struct Node **before, Task *newTask);
void insertAfter(struct Node **prev_node, Task *new_task);
struct Node* initList(Task *task);
void insert(struct Node **head, Task *task);
void delete(struct Node **head, Task *task);
void print(struct Node *head);
