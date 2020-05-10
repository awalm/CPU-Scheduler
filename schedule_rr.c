#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "cpu.h"
#include "schedulers.h"

int tasks_rem (struct Node* head);


void schedule(struct Node *head) {
    if (head == NULL) {
        printf("No jobs found.");
        return; 
    }
   
    run_schedule(head);
}

void run_schedule(struct Node *head) {
    struct Node *curr_node;
    Task *curr_task;
    curr_node = head;
    int slice_time = QUANTUM;
    while (tasks_rem(head)) {
        //printf("Looping\n");
        if (curr_node == NULL) {
            //If the current node is null, then loop back to the head.
            curr_node = head;
        }
        if ((curr_node -> task -> burst_rem) != 0) {
            curr_task = curr_node -> task;
            //If the task remaining time is lower, take that time as the time slice. If not, use the quantum time.
            slice_time = (curr_task -> burst_rem >= QUANTUM) ? QUANTUM : curr_task -> burst_rem;
            run_task(curr_task, slice_time);   
        }
        
        curr_node = curr_node->next; 

    }
}


int tasks_rem (struct Node* head) {
//Scans the list and checks burst time remaining to determine whether or not all the tasks have been complete.

    if (head == NULL) {
        printf("Head is null."); 
        return -1;
    } 
    struct Node *curr_node;
    curr_node = head;

    while (curr_node != NULL) {
       if ((curr_node -> task -> burst_rem) > 0) {
           return 1;
       }
       curr_node = curr_node -> next;
    }
    return 0;
}