#include<bits/stdc++.h>
using namespace std;

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
};

bool comp(struct process p1, struct process p2)
{
    return (p1.arrival_time <= p2.arrival_time);
}

void serve_process(struct process current_process, int starting_time)
{
    int completion_time = starting_time + current_process.burst_time;
    int turn_around_time = completion_time - current_process.arrival_time;
    int waiting_time = starting_time - current_process.arrival_time;
    int response_time = waiting_time;

    cout << "Process Id: " << current_process.process_id << endl;
    cout << "Starting time: " << starting_time << endl;
    cout << "Completion time: " << completion_time << endl;
    cout << "Turn around time: " << turn_around_time << endl;
    cout << "Waiting time: " << waiting_time << endl;
    cout << "Response time: " << response_time << endl << endl;
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
        int minimun_burst_tine = 1000000;
        int job_idx = -1;

        for(int i=0; i<number_of_process; i++){
            if(process_list[i].arrival_time > time) break;
            if(served[i]) continue;

            if(process_list[i].burst_time < minimun_burst_tine){
                minimun_burst_tine = process_list[i].burst_time;
                job_idx = i;
            }
        }

        if(job_idx == -1){
            time++;
            continue;
        }

        serve_process(process_list[job_idx], time);
        time += process_list[job_idx].burst_time;
        served[job_idx] = 1;
        process_served++;

        if(process_served == number_of_process) break;
    }

    return 0;
}
