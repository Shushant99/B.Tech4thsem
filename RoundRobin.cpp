// this is a cpu scheduling algo Round Robin i tried to make it without any unnessesory header files
#include <iostream>
using namespace std;

struct Process {
    int id;
    int at;
    int bt; 
    int rbt;
    int ct; 
    int tat;
    int wt;   
};

int main() {
    int tq; 
    int n;  

    cout << "enter number of processes: ";
    cin >> n;
    cout << "enter time quantum: ";
    cin >> tq;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "enter Arrival Time for P" << p[i].id << ": ";
        cin >> p[i].at;
        cout << "enter Burst Time for P" << p[i].id << ": ";
        cin >> p[i].bt;
        p[i].rbt = p[i].bt; 
    }

    int time = 0;
    int completed = 0;
    bool done[n] = {false};

    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rbt > 0) {
                found = true;

                if (p[i].rbt > tq) {
                    time += tq;
                    p[i].rbt -= tq;
                } else {
                    time += p[i].rbt;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].rbt = 0;
                    completed++;
                }
            }
        }

        if (!found) {
            time++; 
        }
    }

    float total_wt = 0;

    cout << "\nprocess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        total_wt += p[i].wt;
    }

    cout << "\naverage waiting time: " << (total_wt / n) << endl;

    return 0;
}