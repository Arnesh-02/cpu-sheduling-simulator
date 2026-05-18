#ifndef PROCESS_H
#define PROCESS_H

struct process {
    int processId;
    int burstTime;
    int arrivalTime;
    int priority;

    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

#endif