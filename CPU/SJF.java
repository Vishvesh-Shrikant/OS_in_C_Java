package CPU;
import java.util.*;

class Main
{
    public static void main(String args[])
    {
        Scanner ob = new Scanner(System.in);
        
        // Input: Number of processes
        System.out.print("Enter number of processes: ");
        int n = ob.nextInt();
        
        // Arrays to store process information
        int p[]= new int[n];   // Process IDs
        int at[]= new int[n];  // Arrival Time
        int bt[] = new int[n]; // Burst Time
        int st[] = new int[n]; // Start Time
        int ct[] = new int[n]; // Completion Time
        int tat[] = new int[n]; // Turnaround Time
        int wt[] = new int[n];  // Waiting Time
        
        // Array to track whether process is completed
        boolean isCompleted[]= new boolean [n];
        for(int i=0;i< n;i++)
            isCompleted[i]= false;
        
        // Input Arrival time and Burst time for each process
        for (int i = 0; i < n; i++) 
        {
            p[i] = i + 1;
            System.out.print("Enter arrival time for Process " + p[i] + ": ");
            at[i] = ob.nextInt();
            System.out.print("Enter burst time for Process " + p[i] + ": ");
            bt[i] = ob.nextInt();
        }
        
        // Initialize counters and total time variables
        int count=0, currentTime=0;
        float total_tat=0, total_wt=0;
        
        // Non-preemptive Shortest Job First (SJF) Scheduling loop
        while (count < n)
        {
            int shortest= 9999, idx=-1;
            // Find process with the shortest burst time among arrived processes
            for(int i=0;i<n; i++)
            {
                if(!isCompleted[i] && at[i]<= currentTime)
                {
                    if( bt[i] < shortest)
                    {
                        shortest=bt[i];
                        idx=i;
                    }
                }
            }
            
            // If no process has arrived yet, increment time
            if(idx== -1)
                currentTime++;
            
            else
            {
                // Calculate timings for the selected process
                st[idx]= currentTime;              // Start time
                ct[idx] = st[idx]+ bt[idx];        // Completion time
                tat[idx]= ct[idx]- at[idx];        // Turnaround time = CT - AT
                wt[idx]= tat[idx]- bt[idx];        // Waiting time = TAT - BT
                
                currentTime = ct[idx];             // Advance current time
                total_tat+= tat[idx];              // Add to total TAT
                total_wt += wt[idx];               // Add to total WT
                isCompleted[idx]= true;            // Mark process as completed
                count++;                           // Increase completed process count
            }   
        }
        
        // Output table of process timings
        System.out.println("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT");
        for (int i = 0; i < n; i++) 
        {
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
        for (int i = 0; i < n; i++) 
        {
            System.out.printf("P%d\t\t%d\t\t%d\n", p[i], st[i], ct[i]);
        }

        ob.close();  // Close scanner
    }
}
