package CPU;
import java.util.*;

public class RoundRobin {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int n, timeQuantum;

        // Input: number of processes and time quantum
        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        System.out.print("Enter time quantum: ");
        timeQuantum = sc.nextInt();

        Queue<Integer> queue = new LinkedList<>(); // Ready queue for Round Robin

        int p[] = new int[n];    // Process IDs
        int at[] = new int[n];   // Arrival times
        int bt[] = new int[n];   // Burst times (original)
        int rt[] = new int[n];   // Remaining burst times (for RR processing)
        int st[] = new int[n];   // Start times (first time process gets CPU)
        int ct[] = new int[n];   // Completion times (when process finishes)

        boolean isCompleted[] = new boolean[n]; // true if process has completed execution
        boolean isQueued[] = new boolean[n];    // true if process has been added to queue

        int currentTime = 0, count = 0;  // Current simulation time, number of processes completed

        // Input: Arrival and Burst times of each process
        for (int i = 0; i < n; i++) {
            p[i] = i + 1; // Assign process IDs (1-indexed)
            System.out.print("Enter arrival time for Process " + p[i] + ": ");
            at[i] = sc.nextInt();
            System.out.print("Enter burst time for Process " + p[i] + ": ");
            bt[i] = sc.nextInt();
            isCompleted[i] = false; // Mark as not completed
            isQueued[i] = false;    // Mark as not added to queue
            st[i] = -1;             // Initialize start time as -1 (not yet started)
        }

        // Sort all processes by arrival time (FCFS basis initially)
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (at[i] > at[j]) {
                    int temp;
                    temp = at[i]; at[i] = at[j]; at[j] = temp;
                    temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                    temp = p[i]; p[i] = p[j]; p[j] = temp;
                }
            }
        }

        // Copy burst times to remaining times (used in Round Robin)
        for (int i = 0; i < n; i++) {
            rt[i] = bt[i];
        }

        // Main Round Robin scheduling loop
        while (count < n) {
            // Add processes that have arrived and not yet queued/completed
            for (int i = 0; i < n; i++) {
                if (!isQueued[i] && !isCompleted[i] && at[i] <= currentTime) {
                    queue.add(i);
                    isQueued[i] = true;
                }
            }

            // If queue is empty, increment current time (CPU idle)
            if (queue.isEmpty()) {
                currentTime++;
                continue;
            }

            int idx = queue.poll(); // Get next process from queue

            // Set start time if process runs first time
            if (st[idx] == -1)
                st[idx] = currentTime;

            // If process requires more than time quantum
            if (rt[idx] > timeQuantum) {
                currentTime += timeQuantum; // Execute for time quantum
                rt[idx] -= timeQuantum;     // Reduce remaining burst

                // After executing, check if new processes have arrived
                for (int i = 0; i < n; i++) {
                    if (!isQueued[i] && !isCompleted[i] && at[i] <= currentTime) {
                        queue.add(i);
                        isQueued[i] = true;
                    }
                }

                queue.add(idx); // Requeue current process as it's not finished
            } else {
                // Process can finish in this turn
                currentTime += rt[idx];  // Execute for remaining burst
                rt[idx] = 0;             // Set remaining burst to 0
                ct[idx] = currentTime;   // Set completion time
                isCompleted[idx] = true; // Mark process as completed
                count++;                 // Increase completed count

                // After process finishes, check if new processes have arrived
                for (int i = 0; i < n; i++) {
                    if (!isQueued[i] && !isCompleted[i] && at[i] <= currentTime) {
                        queue.add(i);
                        isQueued[i] = true;
                    }
                }
            }
        }

        // Calculate and display Turnaround Time and Waiting Time
        int tat, wt;
        float totalTAT = 0, totalWT = 0;
        System.out.println("\nProcess No.\tA.T\tB.T\tC.T\tT.A.T\tW.T");
        for (int i = 0; i < n; i++) {
            tat = ct[i] - at[i];   // Turnaround Time = Completion - Arrival
            wt = tat - bt[i];      // Waiting Time = Turnaround - Burst
            System.out.println("Process " + p[i] + "\t" + at[i] + "\t" + bt[i] + "\t" + ct[i] + "\t" + tat + "\t" + wt);
            totalTAT += tat;
            totalWT += wt;
        }

        // Display average Turnaround Time and Waiting Time
        System.out.printf("Average Turnaround Time: %.2f\n", totalTAT / n);
        System.out.printf("Average Waiting Time: %.2f\n", totalWT / n);

        // Sort processes by start time (to prepare for Gantt chart display)
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (st[i] > st[j]) {
                    int temp;
                    temp = st[i]; st[i] = st[j]; st[j] = temp;
                    temp = ct[i]; ct[i] = ct[j]; ct[j] = temp;
                    temp = p[i]; p[i] = p[j]; p[j] = temp;
                }
            }
        }

        // Display Gantt Chart (process execution order)
        System.out.println("\n\t\tGANTT CHART");
        System.out.println("PROCESS\t\tStart Time\tCompletion Time");
        for (int i = 0; i < n; i++) {
            System.out.println("Process " + p[i] + "\t\t" + st[i] + "\t\t" + ct[i]);
        }

        sc.close(); // Close scanner
    }
}
