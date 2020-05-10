#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "cpu.h"
#include "schedulers.h"

void ensureCorrectOrder(struct Node **head);

void schedule(struct Node *head) {
    if (head == NULL) {
        printf("No jobs found.");
        return; 
    }
    struct Node *curr_node;
    struct Node *new_head;
    Task *curr_task;
    curr_node = head;

    //Initialize the new linked list using the first task. Initialize both min and max burst times to that burst time.
    curr_task = head -> task;
    int max_burst_time = curr_task -> burst;
    int min_burst_time = curr_task -> burst;
    new_head = initList(curr_task);
    
    curr_node = head -> next;
    //Create a new linked list based on length of the jobs.
    while (curr_node != NULL) {
       //printf("curr_list\n");
       // print(new_head);
        curr_task = curr_node -> task;
        
        //If the burst time is greater than the max burst time, then insert it at the end.
        if ((curr_task -> burst) > max_burst_time){ 
            //printf("adding to back \n");
            insertAtEnd(&new_head, curr_task);
            max_burst_time = curr_task -> burst;
        } else if ((curr_task -> burst) < min_burst_time) { 
            //printf("adding to front");
            insertAtFront(&new_head, curr_task);
            min_burst_time = curr_task -> burst;
        } else {
            //If not the max burst time, then traverse the list and insert it at the right place. 
            //Min burst time not required because essentially same efficiency - first node will always be min.
            struct Node *tmp;
            tmp = new_head;

            //printf("Finding correct place for tid, burst %d, %d\n", curr_task -> tid, curr_task -> burst);
            while (curr_task -> burst > (tmp -> next -> task -> burst)) {
               // printf("Skipping tid, burst: %d, %d \n", tmp -> task -> tid, tmp -> task -> burst);
                tmp = tmp -> next;
            }
            //printf("adding after \n");
            insertAfter(&tmp, curr_task);
    
        }
        curr_node = curr_node -> next;
    }
        ensureCorrectOrder(&new_head);
        run_schedule(new_head);


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

void ensureCorrectOrder(struct Node **head) {
    struct Node *curr_node;
    Task *tmp;
    
    curr_node = *head;
    
    while (curr_node -> next != NULL) {
        //If current burst is the same, and the next task id is smaller than the previous task id, then swap
        
        if ((curr_node -> task -> burst) == (curr_node -> next -> task -> burst) 
            && (curr_node -> task -> tid) > (curr_node -> next -> task -> tid)) {
                tmp = (curr_node) -> task;
                curr_node -> task = curr_node -> next -> task;
                curr_node -> next -> task = tmp;
            }

        curr_node = curr_node->next;
    }
}