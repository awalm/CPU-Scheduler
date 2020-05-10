#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "cpu.h"
#include "schedulers.h"

int tasks_rem (struct Node* head);
void run_schedule_prr();

struct Node* node_arr[MAX_PRIORITY];

//int max_priority = 1;

void schedule(struct Node *head) {
    if (head == NULL) {
        printf("No jobs found.");
        return; 
    }
    //split the tasks into priority "buckets"
    struct Node *curr_node;

    /* Attempted to dynamically calculate the maximum priority, but array pointers didn't work out
    //Find the maximum priority by going through the list
    
    curr_node = head;
    while (curr_node != NULL) {
       if ((curr_node -> task -> priority) > max_priority) {
           max_priority = curr_node -> task -> priority;
       }
       curr_node = curr_node -> next;
    }
    struct Node *node_arr = malloc(max_priority*sizeof(struct Node));
    
    //Create the array
    //struct Node* node_arr[MAX_PRIORITY];
    //Reset curr_node to head
    */

    curr_node = head;
    while (curr_node != NULL) {
       //printf("inserting node tid: %d\n", curr_node -> task -> tid);
       
        if (curr_node -> task -> priority > MAX_PRIORITY) {
            printf("WARNING: Defined max priority %d is lower than priority of task %d, which was %d. Program will fail to function properly.\n", MAX_PRIORITY, curr_node -> task -> tid, curr_node -> task -> priority);
            return;            
        }
        
       insertAtEnd(&node_arr[curr_node -> task -> priority], curr_node -> task);
       curr_node = curr_node -> next;
    }
    /*
    printf("Array of linked lists contents:\n");
    for (int i = 0; i >= QUANTUM; i++) {
        printf("Priority: %d\n", i);
        print((node_arr[i]));
    }
    */
    run_schedule_prr();
}

void run_schedule_prr() {
    struct Node *curr_node;
    struct Node *head;
    Task *curr_task;
    int slice_time = QUANTUM;

    for (int i = MAX_PRIORITY; i > 0; i--) {
        if (node_arr[i] != NULL) {
            head = node_arr[i];
            //printf("Curr head: %d\n", head -> task -> tid);
            if (head -> next == NULL) {
                //If the next one is null, that means that there is only one task with this priority.
                run_task(head -> task, head -> task -> burst);
                continue;
            }
            curr_node = head;
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