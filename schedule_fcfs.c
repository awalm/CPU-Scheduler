#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "cpu.h"
#include "schedulers.h"

void schedule(struct Node *head) {
    if (head == NULL) {
        printf("No jobs found.");
        return; 
    }
    //Don't need to do anything extra for fcfs, as the linked list is already 
    //built as first come first serve.
    
    run_schedule(head);
}

void run_schedule(struct Node *head) {
    struct Node *curr_node;
    Task *curr_task;
    curr_node = head;
    int slice_time = 0;
    while (curr_node != NULL) {
        curr_task = curr_node -> task;
        slice_time = (curr_task -> burst); 
        run_task(curr_task, slice_time);
        curr_node = curr_node->next;
    }
}