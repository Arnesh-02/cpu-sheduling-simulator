#include <stdio.h>
#include  "process.h"
#define MAXIMUM_PROCESSES 20

struct process processes[MAXIMUM_PROCESSES];


void SortProcessByArrivalTime(int n)
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


void CalculateTimes(int n)
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


int main(void) {
   int n;
   printf("\nEnter no of Processes: ");
   scanf("%d", &n);
   for (int i=0; i < n; i++) {
      printf("\nEnter Process ID: ");
      scanf("%d",&processes[i].processId);
      printf("\nEnter Burst Time for ProcessId %d:",processes[i].processId);
      scanf("%d",&processes[i].burstTime);
      printf("\nEnter Arrival Time for ProcessId %d:",processes[i].processId);
      scanf("%d",&processes[i].arrivalTime);
   }
   SortProcessByArrivalTime(n);
   CalculateTimes(n);
}





