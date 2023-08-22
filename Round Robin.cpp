#include<bits/stdc++.h>
using namespace std;

int grant_TQ = 2;

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

    int process_served = 0;
    queue<int> ready_queue;
    vector<int> pushed_to_ready_queue(number_of_process, 0);
    int idx = 0;
    for(int time=0; ;)
    {
        for(int i=0; i<number_of_process; i++){
            if(!pushed_to_ready_queue[idx])
            {
                if(process_list[idx].arrival_time <= time){
                    ready_queue.push(idx);
                    pushed_to_ready_queue[idx]++;
                }
            }

            idx = (idx + 1) % number_of_process;
        }

        if(ready_queue.empty())
        {
            time++;
            continue;
        }

        int current_idx = ready_queue.front();
        ready_queue.pop();

        int increament_time = min(grant_TQ, process_list[current_idx].burst_time - process_list[current_idx].processed_time);
        if(process_list[current_idx].processed_time == 0){
            process_list[current_idx].starting_time = time;
        }
        process_list[current_idx].processed_time += increament_time;
        time += increament_time;

        if(process_list[current_idx].burst_time == process_list[current_idx].processed_time)
        {
            process_completion_message(process_list[current_idx], time);
            process_served++;
        }
        else
        {
            ready_queue.push(current_idx);
        }

        if(process_served == number_of_process) break;
    }

    return 0;
}
