/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

#define SIZE    100

struct Node *head = NULL;
static int num_tasks = 0;

//Function declarations
void add_task(char*, int, int);

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1],"r");
    
    //pointer to store the head of the list
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        //printf("adding to list, driver: [%s] [%d] [%d]\n",name, priority, burst);
	    add_task(name,priority,burst);
        //printf("um");
        free(temp);
    }

    fclose(in);

    // invoke the scheduler, which will schedule and run
    schedule(head);

    //Calculate and print the average times. Assuming bursts can only be integers.
     printf("Average Response Time: %.3f units\nAverage Waiting time: %.3f units\nAverage Turnaround Time: %.3f units\n", 
         get_avg_resp_time(head), get_avg_wait_time(head), get_avg_turn_time(head));
    
    return 0;
}

void add_task(char *name, int priority, int burst) {
    //printf("Adding");
    //FCFS, so just add it to the list as the processes come in. Returns the pointer to the "head" node
    //Have tid be the process number processed
    
    Task *curr_task = malloc(sizeof(Task));
    
    curr_task -> name = name;
    curr_task -> tid = num_tasks + 1;
    curr_task -> priority = priority;
    curr_task -> burst = burst;
    curr_task -> burst_rem = burst;
    curr_task -> arr_time = 0;
    curr_task -> wait_time = -1;
    curr_task -> resp_time = -1;
    curr_task -> last_cpu_time= 0;
    num_tasks++;
    
     if (head == NULL) {
        head = initList(curr_task);
     } else {
        insertAtEnd(&head, curr_task);
     }
}