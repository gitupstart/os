#include <stdio.h>
#include <stdlib.h>

struct process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_completed;
    int start_time;
};

void find_waiting_time(struct process[], int);
void find_turnaround_time(struct process[], int);
void find_average_time(struct process[], int);
void priority_scheduling(struct process[], int);
void print_gantt_chart(struct process[], int, int[]);

int main()
{
    int n, i;
    struct process proc[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter the process ID: ");
        scanf("%d", &proc[i].process_id);

        printf("Enter the arrival time: ");
        scanf("%d", &proc[i].arrival_time);

        printf("Enter the burst time: ");
        scanf("%d", &proc[i].burst_time);

        printf("Enter the priority: ");
        scanf("%d", &proc[i].priority);

        proc[i].is_completed = 0; // Initialize is_completed to 0
    }

    priority_scheduling(proc, n);
    return 0;
}

void find_waiting_time(struct process proc[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void find_turnaround_time(struct process proc[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void find_average_time(struct process proc[], int n)
{
    int total_wt = 0, total_tat = 0, i;

    find_turnaround_time(proc, n);
    find_waiting_time(proc, n);

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time");

    for (i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\n\nAverage Waiting Time = %f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %f\n", (float)total_tat / n);
}

void priority_scheduling(struct process proc[], int n)
{
    int i, time = 0, completed = 0, pos;
    int gantt_chart[n];
    int gantt_index = 0;

    while (completed != n) {
        pos = -1;

        for (i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && !proc[i].is_completed) {
                if (pos == -1 || proc[i].priority < proc[pos].priority) {
                    pos = i;
                }
            }
        }

        if (pos != -1) {
            proc[pos].start_time = time;
            proc[pos].completion_time = time + proc[pos].burst_time;
            time = proc[pos].completion_time;
            proc[pos].is_completed = 1;
            gantt_chart[gantt_index++] = pos;
            completed++;
        } else {
            time++;
        }
    }

    find_average_time(proc, n);
    print_gantt_chart(proc, n, gantt_chart);
}

void print_gantt_chart(struct process proc[], int n, int gantt_chart[])
{
    int i;

    printf("\n\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("| P%d ", proc[gantt_chart[i]].process_id);
    }
    printf("|\n");

    for (i = 0; i < n; i++) {
        printf("%d   ", proc[gantt_chart[i]].start_time);
    }
    printf("%d\n", proc[gantt_chart[n-1]].completion_time);
}
