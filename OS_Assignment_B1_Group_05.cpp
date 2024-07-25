/** Lab Assignment on CPU Scheduling **/
/** Course Title : Operating System (Sessional) **/
/** Course Code : CSE-336 **/
/** CSE-20 Batch **/
/** Group B1 **/
/** Team No : 5 **/
/** Team Members
 * Shougata (2004087)
 * Swakkhar (2004088)
 * Arupa    (2004089)
 * Rashu    (2004090)
 * Tasnimur (2004091)
 **/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back

/**Global Variables**/

double fcfs_avg_res=0,fcfs_avg_wait=0,fcfs_avg_turn=0;

double n_sjf_avg_res=0,n_sjf_avg_wait=0,n_sjf_avg_turn=0;

double sjf_avg_res=0,sjf_avg_wait=0,sjf_avg_turn=0;

double n_prio_avg_res=0,n_prio_avg_wait=0,n_prio_avg_turn=0;

double prio_avg_res=0,prio_avg_wait=0,prio_avg_turn=0;

double RR_avg_res=0,RR_avg_wait=0,RR_avg_turn=0;

double algo_avg_res=0,algo_avg_wait=0,algo_avg_turn=0;

ll dynamic_time_quantum=1,lowest_priority=0;

/** Structures **/
struct Process {
    ll arrival_time;
    ll priority;
    ll burst_time;
    ll process_id;

    bool operator>(const Process& other) const {
        if (priority == other.priority) {
            if (arrival_time == other.arrival_time) {
                return process_id > other.process_id;
            }
            return arrival_time > other.arrival_time;
        }
        return priority > other.priority;
    }
};

struct New_Algo_process {
    ll arrival_time;
    ll priority;
    ll burst_time;
    ll process_id;
    ll remaining_b_time;
    ll redundancy;

    bool operator>(const New_Algo_process& other) const {
        if (priority != other.priority)
            return priority > other.priority;
        if (redundancy != other.redundancy)
            return redundancy > other.redundancy;
        if (remaining_b_time != other.remaining_b_time)
            return remaining_b_time > other.remaining_b_time;
        if (arrival_time != other.arrival_time)
            return arrival_time > other.arrival_time;
        return process_id > other.process_id;
    }
};

/** Prototype Of Functions **/

int display_option();

void FCFS(vector<ll>arrival_time,vector<ll>brust_time);

void Non_Preemptive_SJF(vector<ll>arrival_time,vector<ll>brust_time);

void Preemptive_SJF(vector<ll>arrival_time,vector<ll>brust_time);

void Non_Preemptive_Priority(vector<ll>arrival_time,vector<ll>brust_time,vector<ll>priority);

void Preemptive_Priority(vector<ll>arrival_time,vector<ll>brust_time,vector<ll>priority);

void Round_Robin(vector<ll>arrival_time,vector<ll>brust_time);

void new_algorithm(vector<ll>arrival_time,vector<ll>brust_time,vector<ll>priority);

void compare_all(vector<ll>arrival_time,vector<ll>brust_time,vector<ll> priority);

void calculate_time_quamtum(priority_queue<New_Algo_process, vector<New_Algo_process>, greater<New_Algo_process>> input);

/** The Main Function **/
int main(){

        while(1)
        {

        ll choice;
        choice = display_option();

        if(choice != 9)
        {

        ll num_of_process,time_quantum=0;
        cout<<"\nNumber of process, n: ";
        cin>>num_of_process;

        vector<ll> arrival_time(num_of_process+1),brust_time(num_of_process+1),priority(num_of_process+1);

        if( choice==1 || choice==2 || choice==3 || choice == 6)
        {

            for (int i = 1; i <= num_of_process; ++i)
            {
                cout<<"Enter the burst time of P"<<i<<": ";
                cin>>brust_time[i];
                cout<<"Enter the arrival time of P"<<i<<": ";
                cin>>arrival_time[i];
            }

            if(choice==1)
            {
                FCFS(arrival_time,brust_time);
            }
            else if(choice==2)
            {
                Non_Preemptive_SJF(arrival_time,brust_time);
            }
            else if(choice==3)
            {
                Preemptive_SJF(arrival_time,brust_time);
            }
            else
            {
                Round_Robin(arrival_time,brust_time);
            }

        }
        else if(choice == 4 || choice == 5)
        {
            for (int i = 1; i <= num_of_process; ++i)
            {
                cout<<"Enter the burst time of P"<<i<<": ";
                cin>>brust_time[i];
                cout<<"Enter the arrival time of P"<<i<<": ";
                cin>>arrival_time[i];
                cout<<"Enter the priority of P"<<i<<": ";
                cin>>priority[i];
            }

            if(choice == 4)
            {
                Non_Preemptive_Priority(arrival_time,brust_time,priority);
            }
            else
            {
                Preemptive_Priority(arrival_time,brust_time,priority);
            }
        }
        else if( choice == 7 )
        {
            for (int i = 1; i <= num_of_process; ++i)
            {
                cout<<"Enter the burst time of P"<<i<<": ";
                cin>>brust_time[i];
                cout<<"Enter the arrival time of P"<<i<<": ";
                cin>>arrival_time[i];
                cout<<"Enter the priority of P"<<i<<": ";
                cin>>priority[i];
            }

            new_algorithm(arrival_time,brust_time,priority);
        }
        else
        {
            for (int i = 1; i <= num_of_process; ++i)
            {
                cout<<"Enter the burst time of P"<<i<<": ";
                cin>>brust_time[i];
                cout<<"Enter the arrival time of P"<<i<<": ";
                cin>>arrival_time[i];
                cout<<"Enter the priority of P"<<i<<": ";
                cin>>priority[i];
            }


            compare_all(arrival_time,brust_time,priority);

        }

        }
        else
        {
           break;
        }
    }

}


/**Function Declaration**/

int display_option()
{
    cout<<"1: FCFS\n";
    cout<<"2: Non-Preemptive-SJF\n";
    cout<<"3: Preemptive-SJF\n";
    cout<<"4: Non-Preemptive-Priority\n";
    cout<<"5: Preemptive-Priority\n";
    cout<<"6: Round-Robin\n";
    cout<<"7: Your-Own-Algorithm\n";
    cout<<"8: Compare-All\n";
    cout<<"9: Exit\n";
    cout<<"Input your Choice: \n";

    ll n;
    cin>>n;

    return n;
}


/** Choice 1 **/
void FCFS(vector<ll>arrival_time,vector<ll>brust_time)
{
    int n = arrival_time.size() - 1;

    vector<int> waiting_time(n + 1, 0);
    vector<int> turnaround_time(n + 1, 0);
    vector<int> completion_time(n + 1, 0);
    vector<int> start_time(n + 1, 0);
    vector<int> response_time(n + 1, 0);
    vector<pair<int, int>> Gantt_chart;

    completion_time[1] = arrival_time[1] + brust_time[1];
    turnaround_time[1] = brust_time[1];
    waiting_time[1] = 0;
    start_time[1] = arrival_time[1];
    response_time[1] = waiting_time[1];
    Gantt_chart.push_back({1, start_time[1]});
    cout<<"FCFS:"<<endl;
    for (int i = 2; i <= n; i++) {
        if (arrival_time[i] <= completion_time[i - 1]) {
            start_time[i] = completion_time[i - 1];
        } else {
            start_time[i] = arrival_time[i];
        }
        completion_time[i] = start_time[i] + brust_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - brust_time[i];
        response_time[i] = waiting_time[i];
        Gantt_chart.push_back({i, start_time[i]});
    }

    int CPU_time = 0, i = 0, last = 0;
    int sz = Gantt_chart.size() - 1;
    cout << "\nGantt Chart: ";
    for (const auto &entry : Gantt_chart) {
        cout << CPU_time;
        if (entry.second > CPU_time) {
            cout << " Idle " << entry.second << " ";
        }
        cout << " P" << entry.first << " ";
        i++;
        if (i <= sz)
            CPU_time = Gantt_chart[i].second;
        else
            CPU_time = completion_time[n];
    }
    cout << CPU_time << "\n";

    double total_turnaround_time = 0;
    double total_waiting_time = 0;
    double total_response_time = 0;

    for (int i = 1; i <= n; i++) {
        total_turnaround_time += turnaround_time[i];
        total_waiting_time += waiting_time[i];
        total_response_time += response_time[i];
    }

    cout << "\nProcess Details:\n";
    for (int i = 1; i <= n; i++) {
        cout << "Process: P" << i
             << " Start time: " << start_time[i]
             << " End time: " << completion_time[i]
             << " Response Time: " << response_time[i]
             << " Waiting time: " << waiting_time[i]
             << " Turnaround time: " << turnaround_time[i] << endl;
    }

    double avg_turnaround_time = total_turnaround_time / n;
    double avg_waiting_time = total_waiting_time / n;
    double avg_response_time = total_response_time / n;

    cout << "\nAverage Turnaround Time: " << avg_turnaround_time << "\n";
    cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    cout << "Average Response Time: " << avg_response_time << "\n\n";

    fcfs_avg_turn = avg_turnaround_time;
    fcfs_avg_wait = avg_waiting_time;
    fcfs_avg_res = avg_response_time;
}

/** Choice 2 **/
void Non_Preemptive_SJF(vector<ll>arrival_time,vector<ll>brust_time)
{
    cout<<"Non preemptive SJF:"<<endl;
    int n = arrival_time.size() - 1;
    vector<pair<int, pair<int, string>>> v;
    map<string, int> m;
    int tottime=0;
    for (int i = 1; i <= n; i++) {
        int a = brust_time[i];
        tottime+=a;
        int b = arrival_time[i];
        string s = "P" + to_string(i);
        m[s] = 0;
        v.push_back(make_pair(b, make_pair(a, s)));
    }
    sort(v.begin(), v.end());

    map<int, string> m1;
    m1[v[0].first] = v[0].second.second;
    int st = v[0].second.first;
    int q = 1;
    vector<int> wait, tat;
    tat.push_back(v[0].second.first - v[0].first);
    wait.push_back(tat[0] - v[0].second.first);

    while (1) {
        q++;
        int pt = INT_MAX;
        string x;
        int a;
        for (int i = 1; i < n; i++) {
            if (m[v[i].second.second] != 0) {
                continue;
            }
            if (v[i].first <= st) {
                if (pt > v[i].second.first) {
                    pt = v[i].second.first;
                    x = v[i].second.second;
                    a = i;
                }
            }
        }
        m1[st] = x;
        m[x]++;
        st += v[a].second.first;
        tat.push_back(st - v[a].first);
        wait.push_back(st - v[a].first - v[a].second.first);
        if (q >= n) {
            break;
        }
    }

    cout << endl << "Gantt Chart:" << endl;
    for (auto it : m1) {
        cout << it.first << " " << it.second << " ";
    }
    cout <<tottime<< endl << endl;

    int stq = 0;
    vector<int>res;
    for (auto it : m1) {
        res.push_back(it.first-v[stq].first);
        cout << "Process: " << it.second
             << " | Arrival time: " << v[stq].first
             << " | Start time: " << it.first
             << " | Waiting time: " << wait[stq]
             << " | Turnaround time: " << tat[stq]
             << " | Response time: " << res[stq] <<endl;
        stq++;
    }

    double totalWaitingTime = accumulate(wait.begin(), wait.end(), 0);
    double totalTurnaroundTime = accumulate(tat.begin(), tat.end(), 0);
    double totalResponseTime = accumulate(res.begin(),res.end(),0);
    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;
    double averageResponseTime = totalResponseTime / n;

    n_sjf_avg_wait = averageWaitingTime;
    n_sjf_avg_turn = averageTurnaroundTime;
    n_sjf_avg_res = n_sjf_avg_wait;

    cout << endl;
    cout << "Average waiting time: " << averageWaitingTime << endl;
    cout << "Average turnaround time: " << averageTurnaroundTime << endl;
    cout << "Average response time: " << averageResponseTime<<endl<<endl;
}

/** Choice 3 **/
void Preemptive_SJF(vector<ll>arrival_time,vector<ll>brust_time)
{
    cout<<"Preemptive SJF:"<<endl;
    int n = arrival_time.size() - 1;
    vector<pair<int, pair<int, string>>> processes;
    map<string, int> processMap;
    int tottime=0;
    for (int i = 1; i <= n; i++) {
        int burstTime = brust_time[i];
        tottime+=burstTime;
        int arrivalTime = arrival_time[i];
        string processName = "P" + to_string(i);
        processMap[processName] = burstTime;
        processes.push_back({arrivalTime, {burstTime, processName}});
    }


    sort(processes.begin(), processes.end());

    map<int, string> ganttChart;
    int currentTime = 0;
    vector<int> waitingTimes(n, 0);
    vector<int> turnaroundTimes(n, 0);
    vector<int> startTimes(n, -1);
    vector<int> responseTimes(n, 0);

    vector<bool> completed(n, false);
    int completedCount = 0;

    while (completedCount < n) {
        int shortestBurstTime = INT_MAX;
        int currentProcessIndex = -1;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].first <= currentTime) {
                if (processes[i].second.first < shortestBurstTime) {
                    shortestBurstTime = processes[i].second.first;
                    currentProcessIndex = i;
                }
            }
        }

        if (currentProcessIndex == -1) {
            currentTime++;
            continue;
        }

        if (startTimes[currentProcessIndex] == -1) {
            startTimes[currentProcessIndex] = currentTime;
        }
        ganttChart[currentTime] = processes[currentProcessIndex].second.second;

        processes[currentProcessIndex].second.first--;

        if (processes[currentProcessIndex].second.first == 0) {
            completed[currentProcessIndex] = true;
            completedCount++;
            turnaroundTimes[currentProcessIndex] = currentTime + 1 - processes[currentProcessIndex].first;
            waitingTimes[currentProcessIndex] = turnaroundTimes[currentProcessIndex] - processMap[processes[currentProcessIndex].second.second];
            responseTimes[currentProcessIndex] = startTimes[currentProcessIndex] - processes[currentProcessIndex].first;
        }

        currentTime++;
    }

    cout << endl << "Gantt Chart:" << endl;
    for (auto& entry : ganttChart) {
        cout << entry.first << " " << entry.second << " ";
    }
    cout <<tottime<< endl << endl;

    for (int i = 0; i < n; i++) {
        cout << "Process: " << processes[i].second.second
             << " | Arrival time: " << processes[i].first
             << " | Start time: " << startTimes[i]
             << " | Waiting time: " << waitingTimes[i]
             << " | Turnaround time: " << turnaroundTimes[i]
             << " | Response time: " << responseTimes[i] << endl;
    }


    double totalWaitingTime = accumulate(waitingTimes.begin(), waitingTimes.end(), 0);
    double totalTurnaroundTime = accumulate(turnaroundTimes.begin(), turnaroundTimes.end(), 0);
    double totalResponseTime = accumulate(responseTimes.begin(), responseTimes.end(), 0);
    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;
    double averageResponseTime = totalResponseTime / n;

    sjf_avg_wait = averageWaitingTime;
    sjf_avg_turn = averageTurnaroundTime;
    sjf_avg_res = averageResponseTime;

    cout << endl;
    cout << "Average waiting time: " << averageWaitingTime << endl;
    cout << "Average turnaround time: " << averageTurnaroundTime << endl;
    cout << "Average response time: " << averageResponseTime << endl<<endl;
}

/** Choice 4 **/
void Non_Preemptive_Priority(vector<ll>arrival_time,vector<ll>burst_time,vector<ll>priority)
{
    cout<<"Non preemptive priority:"<<endl;
    int n = arrival_time.size()-1, i, j;
    vector<ll> turnaround_time(n+1), waiting_time(n+1), end_time(n+1), response_time(n+1), start_time(n+1);
    double avg_response, avg_turnaround, avg_waiting;

    if(n==1){
        start_time[1] = arrival_time[1];
        end_time[1] = arrival_time[1]+burst_time[1];
        turnaround_time[1] = end_time[1]-arrival_time[1];
        waiting_time[1] =turnaround_time[1]-burst_time[1];
        response_time[1] = 0;

        cout << endl << "Gantt Chart:" << endl;
        cout << start_time[1] << " P1 " << end_time[1] << endl;
        cout << "Process: P1 Start time: " << start_time[1] << " End time: " << end_time[1] << " Response Time: " << response_time[1] <<" Waiting time: " << waiting_time[1] << " Turnaround time: " << turnaround_time[1] << endl;
        cout << "Average Response Time: " << response_time[1] << endl;
        cout << "Average Waiting Time: " << waiting_time[1] << endl;
        cout << "Average Turnaround Time: " << turnaround_time[1] << endl;
        return;
    }

    vector<pair<ll, int>>arrived, temp;
    vector<pair<ll, int>> gantt;
    for(i=1; i<=n; ++i){
        arrived.pb({arrival_time[i], i});
    }
    sort(arrived.begin(), arrived.end());

    temp.pb({priority[arrived[0].second], arrived[0].second});//first->Priority number, second->Process number
    ll last=0;

    for(i=1; i<n; ){
        if(arrived[i].first==arrived[i-1].first){
            temp.pb({priority[arrived[i].second], arrived[i].second});
            ++i;
        }
        else{
            sort(temp.begin(), temp.end());
            while(temp.size()!=0){
                int process_num = temp[0].second;
                start_time[process_num] = last;
                end_time[process_num] = last+burst_time[process_num];
                turnaround_time[process_num] = end_time[process_num]-arrival_time[process_num];
                waiting_time[process_num] = turnaround_time[process_num]-burst_time[process_num];
                response_time[process_num] = start_time[process_num]-arrival_time[process_num];

                pair<ll, int> pr;
                pr = {start_time[process_num], process_num};
                gantt.pb(pr);

                last+=burst_time[process_num];
                temp.erase(temp.begin());
                bool f=0;
                for(j=i; j<n; ++j){
                    if(arrived[j].first<=last){
                        temp.pb({priority[arrived[j].second], arrived[j].second});
                        f=1;
                    }
                    else
                        break;
                }
                if(f){
                    sort(temp.begin(), temp.end());
                    i=j;
                }
            }
        }
    }
    ll turn=0, wait=0, res=0;
    for(i=1; i<=n; ++i){
        turn+=turnaround_time[i];
        wait+=waiting_time[i];
        res+=response_time[i];
    }
    avg_response = double(res)/n;
    avg_turnaround = double(turn)/n;
    avg_waiting = double(wait)/n;
    n_prio_avg_res=avg_response;
    n_prio_avg_turn=avg_turnaround;
    n_prio_avg_wait=avg_waiting;

    cout << endl << "Gantt Chart:" << endl;
    for(i=0; i<gantt.size(); ++i){
        cout << gantt[i].first << " P" << gantt[i].second << " ";
    }
    cout << end_time[gantt[gantt.size()-1].second] << endl << endl;
    for(i=1; i<=n; ++i){
        cout << "Process: P" << i << " Start time: " << start_time[i] << " End time: " << end_time[i] << " Response Time: " << response_time[i] <<" Waiting time: " << waiting_time[i] << " Turnaround time: " << turnaround_time[i] << endl << endl;
    }
    cout << "Average Response Time: " << avg_response << endl;
    cout << "Average Waiting Time: " << avg_waiting << endl;
    cout << "Average Turnaround Time: " << avg_turnaround << endl<<endl;
    return;
}

/** Choice 5 **/
void Preemptive_Priority(vector<ll> arrival_time, vector<ll> burst_time, vector<ll> priority) {

    cout<<"Preemptive priority:"<<endl;

    priority_queue<Process, vector<Process>, greater<Process>> min_heap;
    vector<ll> remaining_time = burst_time;
    vector<ll> start_time(arrival_time.size(), -1);
    vector<ll> completion_time(arrival_time.size(), 0);
    ll current_time = 0;
    ll completed = 0;

    ll n = arrival_time.size() - 1; 

    vector<ll> response_time(n + 1, -1);
    vector<ll> waiting_time(n + 1, 0);
    vector<ll> turnaround_time(n + 1, 0);
    vector<pair<ll, ll>> Gantt_chart; 

    // Create a vector of processes
    vector<Process> processes;
    for (ll i = 1; i <= n; ++i) {
        processes.push_back({arrival_time[i], priority[i], burst_time[i], i});
    }

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        if (a.arrival_time == b.arrival_time) {
            return a.process_id < b.process_id;
        }
        return a.arrival_time < b.arrival_time;
    });

    // Push the sorted processes into the pending_processes queue
    queue<Process> pending_processes;
    for (const auto &p : processes) {
        pending_processes.push(p);
    }

    while (completed < n) {
        // Add all processes that have arrived to the min-heap
        while (!pending_processes.empty() && pending_processes.front().arrival_time <= current_time) {
            min_heap.push(pending_processes.front());
            pending_processes.pop();
        }

        if (min_heap.empty()) {
            // If no process is available to execute, jump to the next arrival time
            if (!pending_processes.empty()) {
                current_time = pending_processes.front().arrival_time;
                continue;
            }
        }

        // Process the top of the heap
        Process current_process = min_heap.top();
        min_heap.pop();

        if (response_time[current_process.process_id] == -1) {
            response_time[current_process.process_id] = current_time - current_process.arrival_time;
            start_time[current_process.process_id] = current_time;
        }


        if (Gantt_chart.empty() || Gantt_chart.back().first != current_process.process_id) {
            Gantt_chart.push_back({current_process.process_id, current_time});
        }

        current_time++;
        remaining_time[current_process.process_id]--;

        if (remaining_time[current_process.process_id] == 0) {
            completed++;
            completion_time[current_process.process_id] = current_time;
            turnaround_time[current_process.process_id] = completion_time[current_process.process_id] - arrival_time[current_process.process_id];
            waiting_time[current_process.process_id] = turnaround_time[current_process.process_id] - burst_time[current_process.process_id];
        } else {
            current_process.burst_time = remaining_time[current_process.process_id];
            min_heap.push(current_process);
        }
    }

    ll CPU_time=0,i=0,last=0;
    ll sz=Gantt_chart.size()-1;
    cout<<"\nGantt Chart: ";

    for (const auto &entry : Gantt_chart) {

        cout<<CPU_time;

        if (entry.second>CPU_time)
        {
           cout<<" Idle "<<entry.second<<" ";
        }
        cout << " P" << entry.first <<" ";
         i++;

        if(i<=sz)
        CPU_time=Gantt_chart[i].second;
      last=completion_time[entry.first];
    }
    cout<<last;

    cout<<"\n";
    for (auto i = 1; i <= n; i++) {
        cout << "Process: P" << setw(3) << left<< arrival_time[i]
             << setw(15) << left << " Start time: " << right << setw(10) << fixed << start_time[i]
             << setw(10) << left << " End time: " << right << setw(10) << fixed << completion_time[i]
             << setw(10) << left << " Response Time: " << right << setw(10) << fixed << response_time[i]
             << setw(10) << left << " Waiting time: " << right << setw(10) << fixed << waiting_time[i]
             << setw(15) << left << " Turnaround time: " << right << setw(10) << fixed << turnaround_time[i]
             << "\n";
    }

    double total_response_time = accumulate(response_time.begin() + 1, response_time.end(), 0);
    double total_waiting_time = accumulate(waiting_time.begin() + 1, waiting_time.end(), 0);
    double total_turnaround_time = accumulate(turnaround_time.begin() + 1, turnaround_time.end(), 0);

    prio_avg_res = total_response_time / n;
    prio_avg_wait = total_waiting_time / n;
    prio_avg_turn = total_turnaround_time / n;

    cout << "\nAverage Response Time : " << fixed << setprecision(2) << prio_avg_res << endl;
    cout << "Average Waiting Time : " << fixed << setprecision(2) << prio_avg_wait << endl;
    cout << "Average Turnaround Time : " << fixed << setprecision(2) << prio_avg_turn << endl<<endl;
}

/** Choice 6 **/
void Round_Robin(vector<ll>arrival_time,vector<ll>brust_time)
{
    cout<<"Round Robin:"<<endl;
    struct Process {
        int id;
        int arrivalTime;
        int burstTime;
        int remainingTime;
        int completionTime;
        int turnAroundTime;
        int waitingTime;
        int responseTime;
        bool firstResponse;
    };

    int n = arrival_time.size() - 1;
    Process proc[n + 1];
    int tmsq = 0;
    for (int i = 1; i <= n; ++i) {
        proc[i].id = i;
        proc[i].arrivalTime = arrival_time[i];
        proc[i].burstTime = brust_time[i];
        tmsq += proc[i].burstTime * proc[i].burstTime;
        proc[i].remainingTime = brust_time[i];
        proc[i].completionTime = 0;
        proc[i].turnAroundTime = 0;
        proc[i].waitingTime = 0;
        proc[i].responseTime = 0;
        proc[i].firstResponse = false;
    }

    int mean = tmsq / n;
    int time_quantum = sqrt(mean);
    int currentTime = 0;

    queue<int> q;
    vector<bool> inQueue(n + 1, false);

    cout << "Time quantum calculated using formula: " << time_quantum << endl<<endl;

    int completed = 0;
    cout << "Gantt Chart - " << endl;

    while (completed < n) {
        for (int i = 1; i <= n; ++i) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (!q.empty()) {
            int i = q.front();
            q.pop();
            inQueue[i] = false;

            if (!proc[i].firstResponse) {
                proc[i].responseTime = currentTime - proc[i].arrivalTime;
                proc[i].firstResponse = true;
            }

            cout << currentTime << " P" << proc[i].id << " ";

            if (proc[i].remainingTime > time_quantum) {
                currentTime += time_quantum;
                proc[i].remainingTime -= time_quantum;
            } else {
                currentTime += proc[i].remainingTime;
                proc[i].completionTime = currentTime;
                proc[i].remainingTime = 0;
                completed++;
            }

            for (int j = 1; j <= n; ++j) {
                if (proc[j].arrivalTime <= currentTime && proc[j].remainingTime > 0 && !inQueue[j] && j != i) {
                    q.push(j);
                    inQueue[j] = true;
                }
            }

            if (proc[i].remainingTime > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        } else {
            currentTime++;
        }
    }
    cout << currentTime << endl;

    for (int i = 1; i <= n; i++) {
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
    }

    double totalTurnAroundTime = 0;
    double totalWaitingTime = 0;
    double totalResponseTime = 0;


     for (auto i = 1; i <= n; i++) {
        cout << "Process: P" << setw(3) << left<<  proc[i].id
             << setw(15) << left << " Start time: " << right << setw(10) << fixed << proc[i].responseTime + proc[i].arrivalTime
             << setw(10) << left << " End time: " << right << setw(10) << fixed << proc[i].completionTime
             << setw(10) << left << " Response Time: " << right << setw(10) << fixed << proc[i].responseTime
             << setw(10) << left << " Waiting time: " << right << setw(10) << fixed << proc[i].waitingTime
             << setw(15) << left << " Turnaround time: " << right << setw(10) << fixed << proc[i].turnAroundTime 
             << "\n";

             totalTurnAroundTime+=proc[i].turnAroundTime ;
             totalWaitingTime+=proc[i].waitingTime;
             totalResponseTime+=proc[i].responseTime;
    }

    RR_avg_turn = totalTurnAroundTime / n;
    RR_avg_wait = totalWaitingTime / n;
    RR_avg_res = totalResponseTime / n;

    cout << "Average Turn Around Time = " << RR_avg_turn << endl;
    cout << "Average Waiting Time = " << RR_avg_wait << endl;
    cout << "Average Response Time = " << RR_avg_res << endl<<endl;
}

/** Choice 7 **/
void new_algorithm(vector<ll> arrival_time, vector<ll> burst_time, vector<ll> priority) {

    cout<<"Our algorithm:"<<endl;

    priority_queue<New_Algo_process, vector<New_Algo_process>, greater<New_Algo_process>> min_heap;

    vector<ll> remaining_time = burst_time;
    vector<ll> start_time(arrival_time.size(), -1);
    vector<ll> completion_time(arrival_time.size(), 0);
    ll current_time = 0;
    ll completed = 0;

    ll n = arrival_time.size() - 1; // Since arrival_time has n+1 elements including the dummy 0th index
    vector<ll> response_time(n + 1, -1);
    vector<ll> waiting_time(n + 1, 0);
    vector<ll> turnaround_time(n + 1, 0);
    vector<pair<ll, ll>> Gantt_chart; // Stores process ID and start time

    // Queue to track the lowest priority value
    queue<ll> priority_queue;
    ll lowest_priority = LLONG_MAX;

    bool checked_lowest = false;
    // Create a vector of processes
    vector<New_Algo_process> processes;
    for (ll i = 1; i <= n; ++i) {
        processes.push_back({arrival_time[i], priority[i], burst_time[i], i, burst_time[i], 0});
    }

    // Sort the processes by arrival time, and if they are the same, by process ID
    sort(processes.begin(), processes.end(), [](const New_Algo_process &a, const New_Algo_process &b) {
        if (a.arrival_time == b.arrival_time) {
            return a.process_id < b.process_id;
        }
        return a.arrival_time < b.arrival_time;
    });

    // Push the sorted processes into the pending_processes queue
    queue<New_Algo_process> pending_processes;
    for (const auto &p : processes) {
        pending_processes.push(p);
    }

    while (completed < n) {

    // Add all processes that have arrived to the min-heap
    while (!pending_processes.empty() && pending_processes.front().arrival_time <= current_time) {
        min_heap.push(pending_processes.front());
        pending_processes.pop();
    }

    if (min_heap.empty()) {
        // If no process is available to execute, jump to the next arrival time
        if (!pending_processes.empty()) {
            current_time = pending_processes.front().arrival_time;
            continue;
        }
    }

    // Calculate the time quantum dynamically
    calculate_time_quamtum(min_heap);
    ll time_quantum = dynamic_time_quantum;

    // Process the top of the heap
    New_Algo_process current_process = min_heap.top();
    min_heap.pop();

    if (response_time[current_process.process_id] == -1) {
        response_time[current_process.process_id] = current_time - current_process.arrival_time;
        start_time[current_process.process_id] = current_time;
    }

    if (Gantt_chart.empty() || Gantt_chart.back().first != current_process.process_id) {
        Gantt_chart.push_back({current_process.process_id, current_time});
    }

    // Execute the process for the time quantum or until it finishes
    int remaining_quantum = min(time_quantum, remaining_time[current_process.process_id]);
    current_time += remaining_quantum;
    remaining_time[current_process.process_id] -= remaining_quantum;
    current_process.redundancy++;

    if (remaining_time[current_process.process_id] == 0) {
        completed++;
        completion_time[current_process.process_id] = current_time;
        turnaround_time[current_process.process_id] = completion_time[current_process.process_id] - arrival_time[current_process.process_id];
        waiting_time[current_process.process_id] = turnaround_time[current_process.process_id] - burst_time[current_process.process_id];
    } else {
        // If the process didn't finish, push it back into the min-heap
        current_process.burst_time = remaining_time[current_process.process_id];
        if(current_process.redundancy % 3 == 0)
            current_process.priority=lowest_priority;
        min_heap.push(current_process);
    }
}

    ll CPU_time = 0, i = 0,last =0;
    ll sz = Gantt_chart.size() - 1;
    cout << "\nGantt Chart: ";

    for (const auto &entry : Gantt_chart) {
        cout << CPU_time;

        if (entry.second > CPU_time) {
            cout << " Idle " << entry.second << " ";
        }
        cout << " P" << entry.first << " ";
        i++;

        if (i <= sz)
            CPU_time = Gantt_chart[i].second;

        last=entry.first;
    }

    cout<<completion_time[last]<<"\n";
    cout << "\n";
    for (auto i = 1; i <= n; i++) {
        cout << "Process: P" << setw(3) << left << arrival_time[i]
             << setw(15) << left << " Start time: " << right << setw(10) << fixed << start_time[i]
             << setw(10) << left << " End time: " << right << setw(10) << fixed << completion_time[i]
             << setw(10) << left << " Response Time: " << right << setw(10) << fixed << response_time[i]
             << setw(10) << left << " Waiting time: " << right << setw(10) << fixed << waiting_time[i]
             << setw(15) << left << " Turnaround time: " << right << setw(10) << fixed << turnaround_time[i]
             << "\n";
    }

    double total_response_time = accumulate(response_time.begin() + 1, response_time.end(), 0);
    double total_waiting_time = accumulate(waiting_time.begin() + 1, waiting_time.end(), 0);
    double total_turnaround_time = accumulate(turnaround_time.begin() + 1, turnaround_time.end(), 0);

    algo_avg_res = total_response_time / n;
    algo_avg_wait = total_waiting_time / n;
    algo_avg_turn = total_turnaround_time / n;

    cout << "\nAverage Response Time : " << fixed << setprecision(2) << algo_avg_res << endl;
    cout << "Average Waiting Time : " << fixed << setprecision(2) << algo_avg_wait << endl;
    cout << "Average Turnaround Time : " << fixed << setprecision(2) << algo_avg_turn << endl<<endl;

}
/** Choice 8 **/
void compare_all(vector<ll>arrival_time,vector<ll>brust_time,vector<ll> priority)
{
    FCFS(arrival_time,brust_time);
    Non_Preemptive_SJF(arrival_time,brust_time);
    Preemptive_SJF(arrival_time,brust_time);
    Non_Preemptive_Priority(arrival_time,brust_time,priority);
    Preemptive_Priority(arrival_time,brust_time,priority);
    Round_Robin(arrival_time,brust_time);
    new_algorithm(arrival_time,brust_time,priority);

    //Display Comparison


      cout << setw(30) << left << "\nAlgo: FCFS"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << fcfs_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << fcfs_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << fcfs_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Non-Preemptive-SJF"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << n_sjf_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << n_sjf_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << n_sjf_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Preemptive-SJF"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << sjf_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << sjf_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << sjf_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Non-Preemptive-Priority"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << n_prio_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << n_prio_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << n_prio_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Preemptive-Priority"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << prio_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << prio_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << prio_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Round-Robin"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << RR_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << RR_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << RR_avg_turn
         << "\n";

      cout << setw(30) << left << "Algo: Proposed-Algorithm"
         << setw(30) << left << "\tAvg Response T.: " << fixed << setprecision(2) << algo_avg_res
         << setw(30) << left << "\tAvg Waiting T.: " << fixed << setprecision(2) << algo_avg_wait
         << "\tAvg. Turnaround T: " << fixed << setprecision(2) << algo_avg_turn
         << "\n";
}

/** Calculate Dynamic Time Quantum **/
void calculate_time_quamtum(priority_queue<New_Algo_process, vector<New_Algo_process>, greater<New_Algo_process>> input) {
    if (!input.empty()) {
        ll sum_remaining_burst_time = 0;
        ll num_processes = input.size();
        ll max_priority = LLONG_MIN;

        
        while (!input.empty()) {
           
            New_Algo_process current_process = input.top();

            sum_remaining_burst_time += current_process.remaining_b_time;

            
            max_priority = max(max_priority, current_process.priority);

            input.pop();
        }

 
        double mean_remaining_burst_time = static_cast<double>(sum_remaining_burst_time) / num_processes;

    
        ll time_quantum = ceil(sqrt(mean_remaining_burst_time));

        lowest_priority=max_priority ;
        dynamic_time_quantum=time_quantum;
    }
}
