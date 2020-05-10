#define MIN_PRIORITY 1
#define MAX_PRIORITY 100

// add a task to the list 
//void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule(struct Node* head);
void run_schedule(struct Node *head);
