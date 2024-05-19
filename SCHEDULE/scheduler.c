#include "scheduler.h"
extern int counter;
extern unsigned char volatile elapsed;

osThread threads_array[NUM_OF_TASKS] = {{0}};

void create_task(void(*task)(), unsigned long periodicity)
{
  static int i = 0;
  
  threads_array[i].ptr = task;
  threads_array[i].periodicity = periodicity;
  
  i++;
}

void scheduler_run()
{
  while(1)
  {
    int ind = 0;
    if (elapsed == 1)
    {
      for(ind = 0; ind < NUM_OF_TASKS; ind++)
      {
        if (counter % threads_array[ind].periodicity == 0)
          threads_array[ind].ptr();
      }
    }
    elapsed = 0;
  }
}