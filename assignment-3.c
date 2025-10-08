#include <stdio.h>
struct Process {
    int pid;
    int burst;
    int arrival;
    int priority;
    int waiting;
    int turnaround;
};
void calculateAverage(struct Process p[], int n) {
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

void FCFS(struct Process p[], int n) {
    printf("\n---- FCFS Scheduling ----\n");
    int time = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    time = p[0].arrival;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    calculateAverage(p, n);
}

void SJF(struct Process p[], int n) {
    printf("\n---- SJF Scheduling ----\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst > p[j + 1].burst ||
                (p[j].burst == p[j + 1].burst && p[j].arrival > p[j + 1].arrival)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int time = p[0].arrival;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    calculateAverage(p, n);
}

void PriorityScheduling(struct Process p[], int n) {
    printf("\n---- Priority Scheduling ----\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority ||
                (p[j].priority == p[j + 1].priority && p[j].arrival > p[j + 1].arrival)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int time = p[0].arrival;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    printf("PID\tPriority\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].priority, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    calculateAverage(p, n);
}
int main() {
    struct Process p1[10], p2[10], p3[10];
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &p1[i].arrival);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &p1[i].burst);
        printf("Process %d Priority: ", i + 1);
        scanf("%d", &p1[i].priority);
        p1[i].pid = i + 1;
        p2[i] = p3[i] = p1[i];
    }
    FCFS(p1, n);
    SJF(p2, n);
    PriorityScheduling(p3, n);
    return 0;
}



bhubonmondal@Bhubons-Mac-mini OS Assignments % gcc assignment-3.c -o assignment-3
bhubonmondal@Bhubons-Mac-mini OS Assignments % ./assignment-3                    
Enter number of processes: 3
Process 1 Arrival Time: 0
Process 1 Burst Time: 5
Process 1 Priority: 1
Process 2 Arrival Time: 3
Process 2 Burst Time: 2
Process 2 Priority: 8
Process 3 Arrival Time: 2
Process 3 Burst Time: 3
Process 3 Priority: 3

---- FCFS Scheduling ----
PID     Arrival Burst   Waiting Turnaround
P1      0       5       0       5
P3      2       3       3       6
P2      3       2       5       7

Average Waiting Time: 2.67
Average Turnaround Time: 6.00

---- SJF Scheduling ----
PID     Arrival Burst   Waiting Turnaround
P2      3       2       0       2
P3      2       3       3       6
P1      0       5       8       13

Average Waiting Time: 3.67
Average Turnaround Time: 7.00

---- Priority Scheduling ----
PID     Priority        Arrival Burst   Waiting Turnaround
P1      1               0       5       0       5
P3      3               2       3       3       6
P2      8               3       2       5       7

Average Waiting Time: 2.67
Average Turnaround Time: 6.00