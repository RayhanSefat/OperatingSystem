#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("input.txt", "r", stdin);

    int numberOfProcess;
    cin >> numberOfProcess;
    int numberOfResources;
    cin >> numberOfResources;

    int allocated[numberOfProcess][numberOfResources];
    for(int i=0; i<numberOfProcess; i++){
        for(int j=0; j<numberOfResources; j++){
            cin >> allocated[i][j];
        }
    }

    int maximum[numberOfProcess][numberOfResources];
    for(int i=0; i<numberOfProcess; i++){
        for(int j=0; j<numberOfResources; j++){
            cin >> maximum[i][j];
        }
    }

    int need[numberOfProcess][numberOfResources];
    for(int i=0; i<numberOfProcess; i++){
        for(int j=0; j<numberOfResources; j++){
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }

    int available[numberOfResources];
    for(int i=0; i<numberOfResources; i++){
        cin >> available[i];
    }

    int work[numberOfResources];
    for(int i=0; i<numberOfResources; i++){
        work[i] = available[i];
    }

    vector<int> safeSequence;
    int current = numberOfProcess - 1;
    int last = numberOfProcess - 1;
    vector<bool> visited(numberOfProcess, false);
    bool noSafeSequence = false;
    while(true){
        current = (current + 1) % numberOfProcess;
        if(current == last){
            noSafeSequence = true;
            break;
        }
        if(visited[current]){
            continue;
        }

        bool ok = true;
        for(int i=0; i<numberOfResources; i++){
            if(work[i] < need[current][i]){
                ok = false;
                break;
            }
        }

        if(ok){
            safeSequence.push_back(current);
            visited[current] = true;
            last = current;

            cout << current + 1 << endl;
            for(int i=0; i<numberOfResources; i++){
                work[i] += allocated[current][i];
                cout << work[i] << ' ';
            }
            cout << endl;

            if(safeSequence.size() == numberOfProcess){
                break;
            }
        }
    }

    if(noSafeSequence){
        cout << "There exists no safe sequence.\n";
    }
    else{
        cout << "Safe sequence: ";
        for(int process : safeSequence){
            cout << 'p' << process + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
