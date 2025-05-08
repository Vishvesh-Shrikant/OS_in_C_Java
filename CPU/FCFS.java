package CPU;
import java.util.*;

class FCFS {
    public static void main(String[] args) {
        Scanner ob = new Scanner(System.in);
        
        // Input: Number of processes
        System.out.print("Enter number of processes: ");
        int n = ob.nextInt();

        // Arrays to store Process ID, Arrival Time, Burst Time, Start Time,
        // Completion Time, Turnaround Time, and Waiting Time
        int[] p = new int[n];   // Process ID
        int[] at = new int[n];  // Arrival Time
        int[] bt = new int[n];  // Burst Time
        int[] st = new int[n];  // Start Time
        int[] ct = new int[n];  // Completion Time
        int[] tat = new int[n]; // Turnaround Time
        int[] wt = new int[n];  // Waiting Time

        // Input: Arrival Time and Burst Time for each process
        for (int i = 0; i < n; i++) {
            p[i] = i + 1; // Assign process ID starting from 1
            System.out.print("Enter arrival time of Process " + p[i] + ": ");
            at[i] = ob.nextInt();
            System.out.print("Enter burst time of Process " + p[i] + ": ");
            bt[i] = ob.nextInt();
        }

        // Sort processes by Arrival Time (since FCFS schedules based on arrival order)
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (at[i] > at[j]) {
                    // Swap arrival time
                    int temp = at[i]; at[i] = at[j]; at[j] = temp;
                    // Swap burst time accordingly
                    temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                    // Swap process ID accordingly
                    temp = p[i]; p[i] = p[j]; p[j] = temp;
                }
            }
        }

        // Variables to calculate total Turnaround Time and Waiting Time for averages
        float totalTAT = 0, totalWT = 0;
        int currentTime = 0; // Tracks the current time on CPU timeline

        // Calculate Start Time, Completion Time, Turnaround Time, and Waiting Time
        for (int i = 0; i < n; i++) {
            // Start time is either current time or arrival time, whichever is later
            st[i] = Math.max(currentTime, at[i]);
            // Completion time = start time + burst time
            ct[i] = st[i] + bt[i];
            // Turnaround time = completion time - arrival time
            tat[i] = ct[i] - at[i];
            // Waiting time = turnaround time - burst time
            wt[i] = tat[i] - bt[i];

            // Add to total for average calculation later
            totalTAT += tat[i];
            totalWT += wt[i];

            // Update current time to the completion time of this process
            currentTime = ct[i];
        }

        // Output: Display the table of process details
        System.out.println("\nProcess\tAT\tBT\tCT\tTAT\tWT");
        for (int i = 0; i < n; i++) {
            System.out.printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        }

        // Output: Display average Turnaround Time and Waiting Time
        System.out.printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
        System.out.printf("Average Waiting Time: %.2f\n", totalWT / n);

        // Output: Display Gantt chart (sequence of process execution)
        System.out.println("\nGANTT CHART");
        System.out.println("Process\tStart\tComplete");
        for (int i = 0; i < n; i++) {
            System.out.printf("P%d\t%d\t%d\n", p[i], st[i], ct[i]);
        }

        // Close the scanner to avoid resource leak
        ob.close();
    }
}
