
#include<bits/stdc++.h>    // Include Standard library
using namespace std;    // Specifying namespace std

int main() {    // main() function
    int numProcesses;    // Define numProcesses variable
    cout << "Enter the number of process: ";    // print message on console
    cin >> numProcesses;    // Take input from user

    vector<int> burstTime(numProcesses);    // Define burstTime as vector
    vector<int> arrivalTime(numProcesses);    // Define arrivalTime as vector
    vector<int> remainingTime(numProcesses, 0);    // Define remainingTime as vector
    vector<int> waitingTime(numProcesses, 0);    // Define waitingTime as vector
    vector<int> turnaroundTime(numProcesses, 0);    // Define turnaroundTime as vector
    vector<bool> completed(numProcesses, false);    // Define completed as vector
    int currentTime = 0;    // Define current time
    int completedProcesses = 0;    // Define variable completedProcesses


    // Input burst times
    cout << "Enter the burst times:" << endl;    // print message on console
    for (int i = 0; i < numProcesses; i++) {    // for loop
        cin >> burstTime[i];    // taking input from user
        remainingTime[i] = burstTime[i];    // Initialize remaining time
    }

    // Input arrival times
    cout << "Enter the arrival times:" << endl;    // print message on console
    for (int i = 0; i < numProcesses; i++) {    // for loop
        cin >> arrivalTime[i];    // taking input from user
    }
    //for Gantt chart
    vector<pair<int,int>>gantt;    // Define gantt as vector
    int temp=0;    // Define temp as 0
    while (completedProcesses < numProcesses)
    {
        int shortestJob = -1;    // Define shortestJob as -1
        int shortestTime = INT_MAX;    // Define shortestTime as INT_MAX

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < numProcesses; i++) {    // for loop
            if (!completed[i] && arrivalTime[i] <= currentTime && remainingTime[i] < shortestTime) {    // if block
                shortestTime = remainingTime[i];    // assign the value of remainingTime[i] to shortestTime
                shortestJob = i;    // assign the value of i to shortestJob
            }
        }

        if (shortestJob == -1) {    // check if shortestJob is -1
            currentTime++;    // increment value of currentTime by 1
        } else {
            remainingTime[shortestJob]--;    // decrement the value of remainingTime[shortestJob] by 1

            if (remainingTime[shortestJob] == 0) {    // check if remainingTime[shortestJob] is 0
                completedProcesses++;    // increment value of completedProcesses by 1
                completed[shortestJob] = true;    // set completed[shortestJob] to true
                int completionTime = currentTime + 1;    // calculate the completion time
                turnaroundTime[shortestJob] = completionTime - arrivalTime[shortestJob];    // calculate the turnaround time
                waitingTime[shortestJob] = turnaroundTime[shortestJob] - burstTime[shortestJob];    // calculate the waiting time
            }

            currentTime++;    // increment value of currentTime by 1
            gantt.push_back(make_pair(++temp, shortestJob+1));    // initialize the value of gantt
        }
    }
    // Calculate average waiting time and turnaround time
    double totalWaitingTime = 0;    // Define totalWaitingTime as 0.0
    double totalTurnaroundTime = 0;    // Define totalTurnaroundTime as 0.0
    for (int i = 0; i < numProcesses; i++) {    // for loop
        totalWaitingTime += waitingTime[i];    // Calculate totalWaitingTime
        totalTurnaroundTime += turnaroundTime[i];    // Calculate totalTurnaroundTime
    }
    double avgWaitingTime = totalWaitingTime / numProcesses;    // Calculate avgWaitingTime
    double avgTurnaroundTime = totalTurnaroundTime / numProcesses;    // Calculate avgTurnaroundTime

    // Print the results
    cout<<endl;    // print newline on console
    for (int i = 0; i < numProcesses; i++) {    // for loop
        cout <<"Process "<<i + 1<<":    "<<"Waiting time: "<<waitingTime[i]<<"    Turnaround time: "<<turnaroundTime[i]<< endl;    // print message on console
    }
    cout <<endl<< "Average Waiting Time: " << avgWaitingTime << endl;    // print message on console
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;    // print message on console

    cout << endl << "Gantt Chart:" << endl;    // print message on console
    vector<pair<int, pair<int, int>>>sowpnil;    // Define sowpnil as vector
    int i=0;    // Define i as 0
    while(i<gantt.size())
    {
        int c = 1;    // Define c as 1
        for(int j=i+1; j<gantt.size();j++)
        {
            if(gantt[i].second==gantt[j].second)
            {
                c++;    // increment value of c by 1
            }
            else
            {
                break;    // break from loop
            }
        }
        if(i==0)
        {
            sowpnil.push_back(make_pair(0, make_pair(gantt[i].second, c)));    // push the value in sowpnil
        }
        else
        {
            sowpnil.push_back(make_pair(i, make_pair(gantt[i].second, c)));    // push the value in sowpnil
        }
        i+=c;    // increment value of i by c
    }

    //gant chart output
    for(int i=0;i<sowpnil.size();i++)
    {
        cout<<"|---P"<<sowpnil[i].second.first<<"---|";    // print message on console
    }
    cout<<endl;    // print newline on console
    for(int i=0;i<sowpnil.size();i++)
    {
        if(i==(sowpnil.size()-1))
        {
            cout<<sowpnil[i].first<<"        "<<sowpnil[i].second.second+sowpnil[i].first;    // print message on console
        }
        else
        {
            cout<<sowpnil[i].first<<"        ";    // print message on console
        }
    }

    return 0;    // return 0
}
