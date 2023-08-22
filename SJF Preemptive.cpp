#include<bits/stdc++.h>
using namespace std;

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int processed_time = 0;
    int starting_time = 0;
    int completion_time = -1;
    int turn_around_time = -1;
    int waiting_time = -1;
    int response_time = -1;
};

void process_completion_message(struct process current_process, int time)
{
    current_process.completion_time = time;
    current_process.turn_around_time = current_process.completion_time - current_process.arrival_time;
    current_process.waiting_time = current_process.turn_around_time - current_process.burst_time;
    current_process.response_time = current_process.starting_time - current_process.arrival_time;

    cout << "Process Id: " << current_process.process_id << endl;
    cout << "Starting time: " << current_process.starting_time << endl;
    cout << "Completion time: " << current_process.completion_time << endl;
    cout << "Turn around time: " << current_process.turn_around_time << endl;
    cout << "Waiting time: " << current_process.waiting_time << endl;
    cout << "Response time: " << current_process.response_time << endl << endl;
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

    int process_served = 0;
    vector<int> served(number_of_process, 0);
    for(int time = 0; ;)
    {
        int minimum_remaining_time = 100000;
        int job_idx = -1;

        for(int i = 0; i < number_of_process; i++)
        {
            if(process_list[i].arrival_time > time) break;
            if(served[i]) continue;

            if((process_list[i].burst_time - process_list[i].processed_time) < minimum_remaining_time)
            {
                minimum_remaining_time = process_list[i].burst_time - process_list[i].processed_time;
                job_idx = i;
            }
        }

        if(job_idx == -1)
        {
            time++;
            continue;
        }

        process_list[job_idx].processed_time++;
        if(process_list[job_idx].processed_time == 1)
        {
            process_list[job_idx].starting_time = time;
        }
        time++;

        if(process_list[job_idx].burst_time == process_list[job_idx].processed_time)
        {
            served[job_idx] = 1;
            process_served++;
            process_completion_message(process_list[job_idx], time);
        }

        if(process_served == number_of_process) break;
    }

    return 0;
}
