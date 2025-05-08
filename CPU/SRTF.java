package CPU;
import java.util.*;

class SRTF
{
    public static void main(String args[])
    {
        Scanner ob = new Scanner(System.in);
        
        // Input: Number of processes
        System.out.print("Enter number of processes: ");
        int n = ob.nextInt();
        
        // Arrays to store process info
        int p[]= new int[n];   // Process IDs
        int at[]= new int[n];  // Arrival Time
        int bt[] = new int[n]; // Burst Time
        int st[] = new int[n]; // Start Time
        int ct[] = new int[n]; // Completion Time
        int tat[] = new int[n]; // Turnaround Time
        int wt[] = new int[n];  // Waiting Time
        int rt[] = new int[n];  // Remaining Time
        
        // Flags for process completion and first-time execution
        boolean isCompleted[] = new boolean[n];
        boolean firstTime[]= new boolean[n];
        
        // Variables to track totals and time
        float total_tat=0, total_wt=0;
        int currentTime=0, count=0;
        
        // Initialize flags for all processes
        for(int i=0;i< n;i++)
        {
            isCompleted[i]= false;
            firstTime[i]= true;
        }
        
        // Input: Arrival time and burst time for each process
        for (int i = 0; i < n; i++) {
            p[i] = i + 1;
            System.out.print("Enter arrival time for Process " + p[i] + ": ");
            at[i] = ob.nextInt();
            System.out.print("Enter burst time for Process " + p[i] + ": ");
            bt[i] = ob.nextInt();
            rt[i] = bt[i]; // Initialize remaining time as burst time
        }
        
        // SRTF Scheduling loop (Shortest Remaining Time First — Preemptive)
        while (count != n)
        {
            int idx=-1, min_RT=9999;
            // Find process with shortest remaining time that has arrived and not completed
            for(int i=0;i<n;i++)
            {
                if( !isCompleted[i] && at[i] <= currentTime )
                {
                    if( rt[i] < min_RT && rt[i]>0)
                    {
                        min_RT= rt[i];
                        idx=i;
                    }
                }
            }
            
            // If no process has arrived yet, increment time
            if( idx == -1)
                currentTime++;
                
            else
            {
                // If process is starting for the first time, record start time
                if(firstTime[idx])
                {
                    st[idx]= currentTime;
                    firstTime[idx]= false;
                }
                
                currentTime++;    // Execute process for 1 time unit
                rt[idx]--;        // Decrease remaining time
                
                // If process is completed
                if( rt[idx] == 0)
                {
                    ct[idx]= currentTime;                 // Completion time
                    tat[idx]= ct[idx]- at[idx];           // Turnaround time = CT - AT
                    wt[idx]= tat[idx]-bt[idx];            // Waiting time = TAT - BT
                    
                    isCompleted[idx]=true;                // Mark process completed
                    count++;                              // Increase count of completed processes
                    
                    total_tat += tat[idx];                // Add to total TAT
                    total_wt += wt[idx];                  // Add to total WT
                }
            }
        }
        
        // Output table of process timings
        System.out.println("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT");
        for (int i = 0; i < n; i++) {
            System.out.printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                    p[i], at[i], bt[i], st[i],
                    ct[i], tat[i], wt[i]);
        }

        // Output average turnaround time and waiting time
        System.out.printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
        System.out.printf("Average Waiting Time: %.2f\n", total_wt / n);

        // Output Gantt Chart (Start and Completion times for each process)
        System.out.println("\n\t\tGANTT CHART");
        System.out.println("Process\tStart Time\tCompletion Time");
        for (int i = 0; i < n; i++) {
            System.out.printf("P%d\t\t%d\t\t%d\n", p[i], st[i], ct[i]);
        }

        ob.close();  // Close scanner
    }
}
