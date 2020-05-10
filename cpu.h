// length of a time quantum
#define QUANTUM 10

// run the specified task for the following time slice
void run_task(Task *task, int slice);
void update_fields(Task *task, int slice);
double get_avg_turn_time(struct Node* head);
double get_avg_resp_time(struct Node* head);
double get_avg_wait_time(struct Node* head);