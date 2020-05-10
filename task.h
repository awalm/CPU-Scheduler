/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

// representation of a task
typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
    
    int arr_time;
    int burst_rem;
    int resp_time;
    int last_cpu_time;
    int wait_time;
    int exit_time;
    
} Task;

#endif
