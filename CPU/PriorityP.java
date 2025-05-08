package CPU;

import java.util.*;

class PriorityP
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
        int pri[]= new int[n]; // Priority (lower number = higher priority)
        int st[] = new int[n]; // Start Time
        int ct[] = new int[n]; // Completion Time
        int tat[] = new int[n]; // Turnaround Time
        int wt[] = new int[n];  // Waiting Time
        int rt[] = new int[n];  // Remaining Time for preemptive execution
        
        // Arrays to track process completion and first execution time
        boolean isCompleted[]= new boolean [n]; // Marks whether process has completed
        boolean firstTime[]= new boolean [n];   // Marks whether process has started first time
        
        for(int i=0;i< n;i++)
        {
            firstTime[i]= true;     // Initialize all processes as not started
            isCompleted[i]= false;  // Initialize all processes as not completed
        }
            
        // Input Arrival time, Burst time, Priority for each process
        for (int i = 0; i < n; i++) 
        {
            p[i] = i + 1;
            System.out.print("Enter arrival time for Process " + p[i] + ": ");
            at[i] = ob.nextInt();
            System.out.print("Enter burst time for Process " + p[i] + ": ");
            bt[i] = ob.nextInt();
            System.out.print("Enter priority (low no. = high priority) for Process " + p[i] + ":  ");
            pri[i] = ob.nextInt();
            
            rt[i]= bt[i];  // Initialize remaining time as burst time
        }
        
        // Initialize counters and accumulators
        int count=0, currentTime=0;
        float total_tat=0, total_wt=0;
        
        // Preemptive Priority Scheduling loop
        while ( count < n)
        {
            int idx=-1, min_pri=-1;
            // Find process with the highest priority (lowest priority number)
            for (int i=0;i < n;i++)
            {
                if( !isCompleted[i] && at[i]<=currentTime )
                {
                    // Select process with higher priority (greater pri[i] in this logic)
                    if(pri[i] > min_pri)
                    {
                        min_pri= pri[i];
                        idx=i;
                    }
                }
            }
            
            // If no process has arrived, increment current time
            if(idx == -1)
                currentTime++;
            else
            {
                // If process runs for the first time, record start time
                if(firstTime[idx])
                {
                    st[idx]= currentTime;
                    firstTime[idx]= false;
                }
                
                rt[idx]--;      // Execute process for 1 unit of time
                currentTime++;  // Move time forward by 1
                
                // If process finishes execution
                if(rt[idx] == 0 )
                {
                    ct[idx]= currentTime;               // Completion time
                    tat[idx]= ct[idx]- at[idx];         // Turnaround time = CT - AT
                    wt[idx]= tat[idx]- bt[idx];         // Waiting time = TAT - BT
                    
                    total_tat += tat[idx];              // Accumulate total turnaround time
                    total_wt += wt[idx];                // Accumulate total waiting time
                    isCompleted[idx]= true;             // Mark process as completed
                    count++;                            // Increment count of completed processes
                }
            }
        }
        
        // Output table of process information
        System.out.println("\nProcess\tAT\tBT\tPri\tCT\tTAT\tWT");
        for (int i = 0; i < n; i++) 
        {
            System.out.printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                    p[i], at[i], bt[i], pri[i],
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
