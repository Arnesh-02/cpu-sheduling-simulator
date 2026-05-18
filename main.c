#include <stdio.h>
#include  "process.h"
#define MAXIMUM_PROCESSES 20

struct process processes[MAXIMUM_PROCESSES];


void SortProcessByArrivalTimeAsc(int n)
{
   struct process temp;

   for(int i = 0; i < n - 1; i++)
   {
      for(int j = 0; j < n - i - 1; j++)
      {
         if(processes[j].arrivalTime > processes[j + 1].arrivalTime)
         {
            temp = processes[j];
            processes[j] = processes[j + 1];
            processes[j + 1] = temp;
         }
      }
   }
}


void SortProcessByBurstTimeAsc(int n) {

   struct process temp;

   for (int i = 0; i < n; i++) {
      for(int j = 0; j < n - 1; j++) {
         if (processes[j].burstTime > processes[j + 1].burstTime) {
             temp = processes[j+1];
            processes[j+1] = processes[j];
            processes[j] = temp;
         }
      }
   }
}



void SortProcessByBurstTimeDesc(int n) {

   struct process temp;

   for (int i = 0; i < n; i++) {
      for(int j = 0; j < n - 1; j++) {
         if (processes[j].burstTime < processes[j + 1].burstTime) {
            temp = processes[j+1];
            processes[j+1] = processes[j];
            processes[j] = temp;
         }
      }
   }
}


void ljf(int n) {
   int currentTime = 0;
   float totalWT = 0, totalTAT = 0;

   for (int i=0;i<n;i++) {

      while (currentTime < processes[i].arrivalTime) {
         currentTime++;
      }

      processes[i].completionTime = currentTime + processes[i].burstTime;

      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

      processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

      totalWT += processes[i].waitingTime;
      totalTAT += processes[i].turnAroundTime;

      currentTime += processes[i].burstTime;
   }

   printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

   for(int i = 0; i < n; i++)
   {
      printf("%d\t%d\t%d\t%d\t%d\t%d\n",
          processes[i].processId,
          processes[i].arrivalTime,
          processes[i].burstTime,
          processes[i].completionTime,
          processes[i].turnAroundTime,
          processes[i].waitingTime);
   }

   printf("\nAverage Waiting Time = %.2f",
          totalWT / n);

   printf("\nAverage Turn Around Time = %.2f\n",
          totalTAT / n);
}


void sjf(int n) {
   int currentTime = 0;
   float totalWT = 0, totalTAT = 0;

   for (int i=0;i<n;i++) {

      while (currentTime < processes[i].arrivalTime) {
         currentTime++;
      }

      processes[i].completionTime = currentTime + processes[i].burstTime;

      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

      processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

      totalWT += processes[i].waitingTime;
      totalTAT += processes[i].turnAroundTime;

      currentTime += processes[i].burstTime;
   }

   printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

   for(int i = 0; i < n; i++)
   {
      printf("%d\t%d\t%d\t%d\t%d\t%d\n",
          processes[i].processId,
          processes[i].arrivalTime,
          processes[i].burstTime,
          processes[i].completionTime,
          processes[i].turnAroundTime,
          processes[i].waitingTime);
   }

   printf("\nAverage Waiting Time = %.2f",
          totalWT / n);

   printf("\nAverage Turn Around Time = %.2f\n",
          totalTAT / n);
}


void fcfs(int n)
{
   int currentTime = 0;
   float totalWT = 0, totalTAT = 0;

   for(int i = 0; i < n; i++)
   {
      if(currentTime < processes[i].arrivalTime)
      {
         currentTime = processes[i].arrivalTime;
      }

      processes[i].completionTime = currentTime + processes[i].burstTime;


      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;


      processes[i].waitingTime =processes[i].turnAroundTime - processes[i].burstTime;


      currentTime = processes[i].completionTime;


      totalWT += processes[i].waitingTime;
      totalTAT += processes[i].turnAroundTime;
   }

   printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

   for(int i = 0; i < n; i++)
   {
      printf("%d\t%d\t%d\t%d\t%d\t%d\n",
          processes[i].processId,
          processes[i].arrivalTime,
          processes[i].burstTime,
          processes[i].completionTime,
          processes[i].turnAroundTime,
          processes[i].waitingTime);
   }

   printf("\nAverage Waiting Time = %.2f",
          totalWT / n);

   printf("\nAverage Turn Around Time = %.2f\n",
          totalTAT / n);
}


void roundRobin(int n, int timeQuantum)
{
    int currentTime = 0;
    int completed = 0;

    float totalWT = 0;
    float totalTAT = 0;

    int remainingBT[MAXIMUM_PROCESSES];

    for(int i = 0; i < n; i++)
    {
        remainingBT[i] = processes[i].burstTime;
    }

    while(completed < n)
    {
        int executed = 0;

        for(int i = 0; i < n; i++)
        {
            if(processes[i].arrivalTime <= currentTime &&
               remainingBT[i] > 0)
            {
                executed = 1;

                if(remainingBT[i] > timeQuantum)
                {
                    currentTime += timeQuantum;

                    remainingBT[i] -= timeQuantum;
                }

                else
                {
                    currentTime += remainingBT[i];

                    processes[i].completionTime = currentTime;

                    processes[i].turnAroundTime =
                        processes[i].completionTime -
                        processes[i].arrivalTime;

                    processes[i].waitingTime =
                        processes[i].turnAroundTime -
                        processes[i].burstTime;

                    totalWT += processes[i].waitingTime;
                    totalTAT += processes[i].turnAroundTime;

                    remainingBT[i] = 0;

                    completed++;
                }
            }
        }

        /*
           CPU Idle Case
        */

        if(executed == 0)
        {
            currentTime++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processId,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turn Around Time = %.2f\n",
           totalTAT / n);
}


void priorityScheduling(int n)
{
    int currentTime = 0;
    int completed = 0;

    float totalWT = 0;
    float totalTAT = 0;

    int isCompleted[MAXIMUM_PROCESSES] = {0};

    while(completed < n)
    {
        int index = -1;

        int highestPriority = 99999;

        for(int i = 0; i < n; i++)
        {
            if(processes[i].arrivalTime <= currentTime &&
               isCompleted[i] == 0)
            {
                if(processes[i].priority <
                   highestPriority)
                {
                    highestPriority =
                        processes[i].priority;

                    index = i;
                }

                /*
                   Tie Breaking
                */

                else if(processes[i].priority ==
                        highestPriority)
                {
                    if(processes[i].arrivalTime <
                       processes[index].arrivalTime)
                    {
                        index = i;
                    }
                }
            }
        }

        /*
           CPU Idle
        */

        if(index == -1)
        {
            currentTime++;
        }

        else
        {
            processes[index].completionTime =
                currentTime +
                processes[index].burstTime;

            processes[index].turnAroundTime =
                processes[index].completionTime -
                processes[index].arrivalTime;

            processes[index].waitingTime =
                processes[index].turnAroundTime -
                processes[index].burstTime;

            totalWT += processes[index].waitingTime;

            totalTAT +=
                processes[index].turnAroundTime;

            currentTime =
                processes[index].completionTime;

            isCompleted[index] = 1;

            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processId,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turn Around Time = %.2f\n",
           totalTAT / n);
}

int main()
{
   int n;
   int choice;

   printf("Enter Number of Processes: ");
   scanf("%d", &n);

   for(int i = 0; i < n; i++)
   {
      printf("\nEnter Process ID: ");
      scanf("%d", &processes[i].processId);

      printf("Enter Arrival Time: ");
      scanf("%d", &processes[i].arrivalTime);

      printf("Enter Burst Time: ");
      scanf("%d", &processes[i].burstTime);
   }

   while(1)
   {
      printf("\n========== CPU SCHEDULING ==========\n");

      printf("1. FCFS\n");
      printf("2. SJF\n");
      printf("3. LJF\n");
      printf("4. Round Robin\n");
      printf("5. Exit\n");

      printf("\nEnter Choice: ");
      scanf("%d", &choice);

      switch(choice)
      {
         case 1:
            SortProcessByArrivalTimeAsc(n);
            fcfs(n);
            break;

         case 2:
            SortProcessByBurstTimeAsc(n);
            sjf(n);
            break;

         case 3:
            SortProcessByBurstTimeDesc(n);
            ljf(n);
            break;

         case 4:

             int timeQuantum;

             printf("Enter Time Quantum: ");
             scanf("%d", &timeQuantum);

             roundRobin(n, timeQuantum);

             break;


          case 5:

             for(int i = 0; i < n; i++)
             {
                 printf("Enter Priority for P%d: ",
                        processes[i].processId);

                 scanf("%d", &processes[i].priority);
             }

             priorityScheduling(n);

             break;

         case 6:
            printf("\nExiting Program...\n");
            return 0;

         default:
            printf("\nInvalid Choice!\n");
      }
   }
}