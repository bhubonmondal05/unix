#include <stdio.h>
struct Process {
    int pid, arrival, burst, waiting, turnaround, type;
};
void fcfs(struct Process p[], int n, int startTime) {
    int time = startTime;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
}
int main() {
    struct Process sys[10], user[10];
    int n, s = 0, u = 0;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int t;
        printf("\nProcess %d type (0=System, 1=User): ", i + 1);
        scanf("%d", &t);
        printf("Arrival Time: ");
        int a; scanf("%d", &a);
        printf("Burst Time: ");
        int b; scanf("%d", &b);
        if (t == 0) sys[s++] = (struct Process){i + 1, a, b, 0, 0, 0};
        else user[u++] = (struct Process){i + 1, a, b, 0, 0, 1};
    }
    printf("\n--- System Queue (High Priority) ---\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    fcfs(sys, s, 0);
    int endTime = 0;
    for (int i = 0; i < s; i++)
        if (sys[i].arrival + sys[i].turnaround > endTime)
            endTime = sys[i].arrival + sys[i].turnaround;
    printf("\n--- User Queue (Low Priority) ---\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    fcfs(user, u, endTime);
}
