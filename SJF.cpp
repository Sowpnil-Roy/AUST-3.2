
#include <bits/stdc++.h>    // Include bits/stdc++ library
using namespace std;    // Specifying namespace std

struct process    // Defining process structure
{
    int ArrivalWait;    // "ArrivalWait" variable of int data type
    int status;    // "status" variable of int data type
    int processNo;    // "processNo" variable of int data type
    int CpuTime;    // "CpuTime" variable of int data type
    int ArrivalTime;    // "ArrivalTime" variable of int data type
    int EndTime;    // "EndTime" variable of int data type
    int TurnAround;    // "TurnAround" variable of int data type
    int WaitingTime;    // "WaitingTime" variable of int data type
};

bool sortByArrivalWait(process &a, process &b)    // Define sort function
{
    return a.ArrivalWait < b.ArrivalWait;    // Return the value of "ArrivalWait" less than value of "b.ArrivalWait"
}

int main()    // main function
{
    //Inputs
    int n;    // Initialize variable "n"
    int completed = 0;    // Initialize variable "completed"
    int ganttProgress = 0;    // Initialize variable "ganttProgress"
    float avg_TAT = 0, avg_WT = 0;    // Initialize the variable "avg_TAT" and "avg_WT"
    cout << "Enter the number of Processes : ";    // Print "Enter the number of Processes" on console.
    cin >> n;    // Take input from console
    cout << endl;    // Print new line
    process p[n];    // Initialize the process structure array
    cout << "Enter CPU time : " << endl;    // Print "Enter CPU time" on console
    for (int i = 0; i < n; i++)    // for loop
    {
        cin >> p[i].CpuTime;    // Take input from console
        p[i].processNo = i + 1;    // Assign value of "i+1" to "processNo" variable
        p[i].status = 0;    // Assign value 0 to status variable
    }
    cout << "Enter arrival time : " << endl;    // Print "Enter arrival time" on console
    for (int i = 0; i < n; i++)    // for loop
    {
        cin >> p[i].ArrivalTime;    // Take input from console
    }
    //Calculations
   while(completed!=n)    // while loop
   {
    int min_index=-1;    // Initialize variable "min_index"
    int minimum=INT_MAX;    // Initialize variable "minimum" with value "INT_MAX"
    for(int i=0;i<n;i++)    // for loop
    {
        if(p[i].ArrivalTime<=ganttProgress&&p[i].status==0)    // check if the value of "ArrivalTime" is less than or equal to value of "ganttProgress"
        {
            if(p[i].CpuTime<minimum)    // check if the value of "CpuTime" is less than value of "minimum"
            {
                minimum=p[i].CpuTime;    // Assign the value of "CpuTime" to "minimum" variable
                min_index=i;    // Assign the value of "i" to "min_index" variable
            }

        if(p[i].CpuTime==minimum)    // Check if the value of "CpuTime" is equal to "minimum"
        {
            if(p[i].ArrivalTime<p[min_index].ArrivalTime)    // Check if the value of "ArrivalTime" is less than value of "p[min_index].ArrivalTime"
            {
                minimum=p[i].CpuTime;    // Assign the value of "CpuTime" to "minimum" variable
                min_index=i;    // Assign the value of "i" to "min_index" variable
            }
        }
        }
    }
    if(min_index!=-1)    // Check if the value of "min_index" is not equal to -1
    {
        ganttProgress+=p[min_index].CpuTime;    // Add the value of "CpuTime" to "ganttProgress" variable
        completed++;    // Increment the value of "completed" variable by 1
        p[min_index].EndTime=ganttProgress;    // Assign the value of "ganttProgress" to "EndTime" variable
        p[min_index].status=1;    // Assign the value of 1 to "status" variable
    }
    else    // else block
    {
        ganttProgress++;    // Increment the value of "ganttProgress" variable by 1
    }
   }
    //Calculating TurnAround
    for(int i=0;i<n;i++)    // for loop
    {
        p[i].TurnAround=p[i].EndTime-p[i].ArrivalTime;    // Calculate the value of "TurnAround"
        avg_TAT+=p[i].TurnAround;    // Add the value of "TurnAround" to "avg_TAT"
    }
    avg_TAT=avg_TAT/n;    // Calculate the value of "avg_TAT"
    //Calculating WaitingTime
    for(int i=0;i<n;i++)    // for loop
    {
        p[i].WaitingTime=p[i].TurnAround-p[i].CpuTime;    // Calculate the value of "WaitingTime"
        avg_WT+=p[i].WaitingTime;    // Add the value of "WaitingTime" to "avg_WT"
    }
    avg_WT=avg_WT/n;    // Calculate the value of "avg_WT"
    for(int i =0;i<n;i++)    // for loop
    {
        cout << "Process " << p[i].processNo <<" : Waiting Time : "<<p[i].WaitingTime << " TurnAround Time : "<< p[i].TurnAround << endl;    // Print "Process : Waiting Time : TurnAround Time" on console
         p[i].ArrivalWait = p[i].ArrivalTime + p[i].WaitingTime;    // Calculate the value of "ArrivalWait"
    }
    cout <<endl<< "Average Waiting time : "<< avg_WT << endl;    // Print "Average Waiting time" on console
    cout << "Average Turnaround time : "<< avg_TAT << endl;    // Print "Average Turnaround time" on console
    //Gantt Chart output
    cout <<endl<< "Gantt Chart : " <<endl;    // Print "Gantt Chart" on console
    sort(&p[0], &p[n], sortByArrivalWait);    // Sort the array "p"
    cout << "\n|";    // print "|" on console
    for (int i = 0; i < n; i++)    // for loop
    {
        for (int j = 0; j < p[i].CpuTime - 1; j++)    // for loop
            cout << "-";    // print "-" on console
        cout << "p" << p[i].processNo;    // print "p" and value of "processNo" on console
        for (int j = 0; j < p[i].CpuTime - 1; j++)    // for loop
            cout << "-";    // print "-" on console
        cout << "|";    // print "|" on console
        if (p[i].EndTime != p[i + 1].ArrivalWait && i + 1 < n)    // check if value of "EndTime" is not equal to value of "ArrivalWait" and "i + 1 < n"
        {
            for (int j = 0; j < (p[i + 1].ArrivalWait - p[i].EndTime) - 1; j++)    // for loop
            {
                cout << "-";    // print "-" on console
            }
            cout << "|";    // print "|" on console
        }
    }
    cout << endl;    // print new line
    int prev_print = 0;    // Initialize variable "prev_print"
    cout << p[0].ArrivalWait;    // Print the value of "ArrivalWait"
    for (int i = 0; i < n; i++)    // for loop
    {
        for (int j = 0; j < p[i].CpuTime; j++)    // for loop
        {
            cout << "  ";    // print two white spaces on console
        }
        cout << p[i].EndTime;    // Print the value of "EndTime"
        if (p[i].EndTime != p[i + 1].ArrivalWait && i + 1 < n)    // Check if the value of "EndTime" is not equal to value of "ArrivalWait" and "i + 1 < n"
        {
            for (int j = 0; j < (p[i + 1].ArrivalWait - p[i].EndTime) - 1; j++)    // for loop
            {
                cout << " ";    // print white space on console
            }
            cout << p[i+1].ArrivalWait;    // Print the value of "ArrivalWait"
        }
    }
    return 0;    // return 0
}
