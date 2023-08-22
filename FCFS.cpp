#include<bits/stdc++.h>
using namespace std;

int current_time = 0;

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
};

void serve_process(struct process current_process)
{
    int starting_time = max(current_time, current_process.arrival_time);
    int completion_time = starting_time + current_process.burst_time;
    int turn_around_time = completion_time - current_process.arrival_time;
    int waiting_time = starting_time - current_process.arrival_time;
    int response_time = waiting_time;

    current_time = completion_time;

    cout << "Process Id: " << current_process.process_id << endl;
    cout << "Starting time: " << starting_time << endl;
    cout << "Completion time: " << completion_time << endl;
    cout << "Turn around time: " << turn_around_time << endl;
    cout << "Waiting time: " << waiting_time << endl;
    cout << "Response time: " << response_time << endl << endl;
}

bool comp(struct process p1, struct process p2)
{
    return (p1.arrival_time <= p2.arrival_time);
}

int main()
{
    cout << "Enter the number of process: ";
    int number_of_process;
    cin >> number_of_process;

    struct process process_list[number_of_process];
    for(int i = 0; i < number_of_process; i++)
    {
        cout << "Proces " << i+1 << ":\n";

        cout << "Enter the process id: ";
        cin >> process_list[i].process_id;
        cout << "Enter arrival time: ";
        cin >> process_list[i].arrival_time;
        cout << "Enter burst time: ";
        cin >> process_list[i].burst_time;

        cout << endl;
    }

    sort(process_list, process_list + number_of_process, comp);

    for(int i = 0; i < number_of_process; i++){
        serve_process(process_list[i]);
    }

    return 0;
}
