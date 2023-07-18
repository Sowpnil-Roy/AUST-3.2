#include<bits/stdc++.h>    // Include all standard libraries
using namespace std;
int r, cycle = 1;    // Initialize variables r and cycle

int getIndex(char ArrNode[], char c)    // Function to get index of node
{
    int nodeIndex;
    for (int i = 0; i < r; i++)
    {
        if (ArrNode[i] == c)
            nodeIndex = i;
    }
    return nodeIndex;
}

void printTheStack(stack<int> stack, char nodes[], int index)    // Function to print the deadlock node
{
    int k = 0;
    char nameArr[r];
    while (!stack.empty())
    {
        nameArr[k] = nodes[stack.top()];
        k++;
        stack.pop();
        if (nameArr[k - 1] == nodes[index])
            break;
    }
    cout << cycle << " - Deadlock Detected Among nodes: ";
    for (int i = k - 1; i >= 0; i--)
        cout << nameArr[i] << " ";
    cout << endl;
    cycle++;
}

int main()    // Main function
{
    cout << "Enter number of nodes: ";    // Print message on console
    cin >> r;    // Take input from user
    int graph[r][r], visited[r];    // Initialize graph and visited array
    char nodeName[r];    // Initialize nodeName array

    cout << "Node names: ";    // Print message on console
    for (int i = 0; i < r; i++)
    {
        cin >> nodeName[i];    // Take node names from user
        visited[i] = -1;
    }

    for (int i = 0; i < r; i++)
        for (int j = 0; j < r; j++)
            graph[i][j] = 0;

    cout << "Edges: ";    // Print message on console
    string line;    // Initialize variable line
    cin.ignore();    // Ignore input
    getline(cin, line);    // Take input from user
    while (line[0] != '\0')
    {
        graph[getIndex(nodeName, line[0])][getIndex(nodeName, line.back())] = 1;    // Construct the graph
        line = "";    // empty the line variable
        getline(cin, line);    // Take input from user
    }

    stack<int> st;    // Initialize variable st

    for (int node = 0; node < r; node++)
    {
        st.push(node);    // Push the node to the stack
        while (!st.empty())
        {
            node = st.top();
            if (visited[node] == 1)
            {
                st.pop();    // Pop the node
            }
            if (visited[node] != 1)
            {
                for (int i = 0; i < r; i++)
                {
                    if (graph[node][i] && visited[i] == -1)
                    {
                        visited[node] = 0;
                        st.push(i);    // Push the node to the stack
                        break;
                    }
                    else if (graph[node][i] && visited[i] == 0)
                    {
                        visited[node] = 0;
                        for (int j = 0; j < r; j++)
                        {
                            if (graph[i][j] && visited[j] != 1)
                            {
                                visited[i] = 0;
                            }
                            else
                                visited[i] = 1;
                        }
                        printTheStack(st, nodeName, i);    // Print the deadlock nodes
                    }
                    else
                    {
                        visited[node] = 1;
                    }
                }
            }
        }
    }
    cout << endl;
}


/*
Example:

Enter number of nodes: 13
Node names: R A C S D T B E F U V W G
Edges:
R to A
A to S
C to S
W to F
F to S
B to T
T to E
E to V
V to G
G to U
U to D
D to S
D to T
*/



