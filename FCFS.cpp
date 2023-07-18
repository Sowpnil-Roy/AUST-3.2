#include<bits/stdc++.h>    // include the standard C++ library
using namespace std;    // specify the namespace
bool sortbysec(const pair<int, pair<int,int>> &a, const pair<int, pair<int,int>> &b)    // function to sort by second
{
    return (a.second.first < b.second.first);    // return true if second of a is less than second of b
}
int main()    // main function
{
    //Inputs
    int NumProcessor;    // NumProcessor variable
    cout<<"Enter the number of process: ";    // print message on console
    cin>>NumProcessor;    // take input of No. of processes from user

    int CpuTime[NumProcessor];    // array to store CPU time of each process
    int ArrivalTime[NumProcessor];    // array to store arrival time of each process
    vector<pair<int,int>>WaitingTime;    // vector to store waiting time of each process
    vector<pair<int,int>>TurnaroundTime;    // vector to store turnaround time of each process

    cout<<"Enter the CPU times"<<endl;    // print message on console
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        cin>>CpuTime[i];    // take CPU time of process i from user
    }
    cout<<"Enter the arrival times"<<endl;    // print message on console
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        cin>>ArrivalTime[i];    // take arrival time of process i from user
    }

    vector<pair<int, pair<int,int>>>sowpnil;    // vector to store arrival time and CPU time of each process
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        sowpnil.push_back(make_pair(i+1, make_pair(ArrivalTime[i],CpuTime[i])));    // push to the vector
    }
    sort(sowpnil.begin(), sowpnil.end(), sortbysec);    // sort by arrival time in ascending order

    //waiting time for all processes
    int temp1, temp2;    // temporary variables
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        if(i==0)    // check if it is the first process
        {
            WaitingTime.push_back(make_pair(sowpnil[i].first,0));    // waiting time of first process = 0
        }
        else    // else body
        {
            WaitingTime.push_back(make_pair(sowpnil[i].first, sowpnil[i-1].second.second+WaitingTime[i-1].second+sowpnil[i-1].second.first-sowpnil[i].second.first));    // push the waiting time of process i to the vector
            //WaitingTime.push_back(make_pair(sowpnil[i].first, sowpnil[i-1].second.second+WaitingTime[i-1].second-sowpnil[i].second.first));    // push the waiting time of process i to the vector
        }
    }

    //TurnAround Time for all processes
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        TurnaroundTime.push_back(make_pair(sowpnil[i].first, WaitingTime[i].second+sowpnil[i].second.second));    // push the turnaround time of process i to the vector
    }

    //Average Waiting Time and Turnaround Time
    int TotalWaitingTime=0;    // initialize variable to store total waiting time
    int TotalTurnaroundTime=0;    // initialize variable to store total turnaround time
    double AvgWaitingTime;    // initialize variable to store average waiting time
    double AvgTurnaroundTime;    // initialize variable to store average turnaround time
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        TotalTurnaroundTime+=TurnaroundTime[i].second;    // add the turnaround time of process i to TotalTurnaroundTime
        TotalWaitingTime+=WaitingTime[i].second;    // add the waiting time of process i to TotalWaitingTime
    }
    AvgTurnaroundTime = (double)TotalTurnaroundTime/(double)NumProcessor;    // calculate average turnaround time
    AvgWaitingTime = (double)TotalWaitingTime/(double)NumProcessor;    // calculate average waiting time

    sort(WaitingTime.begin(), WaitingTime.end());    // sort by waiting time in ascending order
    sort(TurnaroundTime.begin(), TurnaroundTime.end());    // sort by turnaround time in ascending order

    //Lab manual sample Output
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        cout<<"Process "<<WaitingTime[i].first<<": "<<"Waiting Time: "<<WaitingTime[i].second<<"   "<<"Turnaround Time: "<<TurnaroundTime[i].second<<endl;    // print the waiting time and turnaround time of each process
    }
    cout<<endl<<"Average Waiting time: "<<AvgWaitingTime<<endl;    // print the average waiting time
    cout<<"Average Turnaround time: "<<AvgTurnaroundTime<<endl;    // print the average turnaround time

    //Gantt chart output
    cout<<endl<<endl<<"GANTT CHART:"<<endl;    // print message on console
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        cout<<"|----P"<<sowpnil[i].first<<"----";    // print the Gantt chart
    }
    cout<<"|"<<endl;
    cout<<"0          ";
    int temp=sowpnil[0].second.second;    // initialize temporary variable
    for(int i=0; i<NumProcessor; i++)    // iterate over each process
    {
        if(i==0)    // check if it is the first process
        {
            cout<<temp<<"          ";    // print the Gantt chart
        }
        else    // else body
        {
            temp+=sowpnil[i].second.second;    // add CPU time of process i to temp
            cout<<temp<<"          ";    // print the Gantt chart
        }
    }

    return 0;
}
