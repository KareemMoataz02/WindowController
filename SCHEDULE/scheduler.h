#define NUM_OF_TASKS 3

void create_task(void(*task)(), unsigned long periodicity);
void scheduler_run();

typedef struct
{
  void (*ptr)();
  unsigned long periodicity;
} osThread;
