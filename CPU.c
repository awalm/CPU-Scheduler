/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include "list.h"
#include "cpu.h"

// run this task for the specified time slice
static int curr_time = 0;

void run_task(Task *task, int slice) {
    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
    curr_time += slice;
    update_fields(task, slice);
    //printf("Curr time:%d", curr_time);
}

void update_fields(Task *task, int slice) {
    task -> burst_rem = (task -> burst_rem) - slice;
        //printf("Task %d burst time remaining:\n", task -> burst_rem);

    //If the response time is -1, that means that it was not initialized yet. 
    if (task -> resp_time == -1) {
        //printf("Responding to Task %d first time: %d\n", task -> tid, curr_time - slice - (task -> arr_time));
        task -> resp_time = curr_time - slice - (task -> arr_time);
    }
    
    if (task -> burst_rem == 0) {
        //printf("Task %d finished, with finish time: %d\n", task -> tid, curr_time);
        (task -> exit_time) = curr_time;
        (task -> wait_time) += (curr_time - (task -> last_cpu_time));
    } else {
        (task -> wait_time) += (curr_time - (task -> last_cpu_time));
        task -> last_cpu_time = curr_time;
    }
}

//Assuming that bursts can only be an integer, which seems to be the case based on the started code that was given.
double get_avg_turn_time(struct Node* head) {
    struct Node *temp;
    temp = head;
    
    double turn_time_sum = 0;
    int num_tasks = 0;

    while (temp != NULL) {
        turn_time_sum += (temp -> task -> exit_time) - (temp -> task -> arr_time);
        num_tasks++;
        temp = temp->next;
    }
    return turn_time_sum/num_tasks;
}

double get_avg_resp_time(struct Node* head) {
    struct Node *temp;
    temp = head;
    
    double resp_time_sum = 0.0;
    int num_tasks = 0;

    while (temp != NULL) {
        resp_time_sum += (temp -> task -> resp_time);
        num_tasks++;
        temp = temp->next;
    }
    return resp_time_sum/num_tasks;
}

double get_avg_wait_time(struct Node* head) {
    struct Node *temp;
    temp = head;
    
    double wait_time_sum = 0;
    int num_tasks = 0;

    while (temp != NULL) {
        wait_time_sum += ((temp -> task) -> exit_time)- ((temp -> task) -> arr_time) - ((temp -> task) -> burst);
        //printf("Task %d, Wait time: %d\n", temp -> task -> tid, ((temp -> task) -> exit_time)- ((temp -> task) -> arr_time) - ((temp -> task) -> burst));
        num_tasks++;
        temp = temp->next;
    }
    //printf("Sum of waiting time: %f\n", wait_time_sum);
    return wait_time_sum/num_tasks;
}