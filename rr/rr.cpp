#include "Task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

int main(int argc, char *argv[]) {
    /* Display Information */
    cout << "CS 433 Programming assignment 3\n" <<
            "Authors: Ian Murphy, Anthony Finn and Loc Huynh\n" <<
            "Date: 03/10/2022\n" <<
            "Course: CS 433 (Operating Systems)\n" <<
            "Description: Round Robin (RR) CPU scheduling algorithmn implementation using a queue.\n" <<
            "=================================" << endl;

    /* Check Arguments */
    if (argc < 2) {
        cerr << "Usage: ./rr <input_file> [<time_quantum>]" << endl;
        exit(1);
    }

    /* Open File */
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        exit(1);
    }

    /* Check Quantum */
    int time_quantum = argv[2] != nullptr ? atoi(argv[2]) : 10;

    /* Prepare CPU Scheduling Task queue */
    queue<Task *> queued_tasks;
    queue<Task *> completed_tasks;

    /* Read open file CSVs & Create new tasks */
    string line, task_name;
    int priority = 0, cpu_burst = 0;
    while (getline(file, line)) {
        istringstream iss(line);

        /* Split Line into categories */
        iss >> task_name;
        task_name.pop_back();

        iss >> priority;
        iss.ignore();

        iss >> cpu_burst;

        /* Create New Task */
        Task *task = new Task(task_name, priority, cpu_burst);
        queued_tasks.push(task);

        /* Display */
        cout << task_name << " " << priority << " " << cpu_burst << endl;
    }

    /* Begin scheduling */
    int current_time = 0;
    while (!queued_tasks.empty()) {
        Task *task = queued_tasks.front();

        int current_burst_time = task->remaining_cpu_burst() - time_quantum < 0 ? task->remaining_cpu_burst() : time_quantum;

        /* Simulate running task */
        task->remaining_cpu_burst() -= current_burst_time;
        current_time += current_burst_time;
        cout << "Running task = [" << task->task_name() << "] [" << task->priority() << "] [" << task->cpu_burst() << "] for " << current_burst_time << " units." << endl;

        /* Complete running task */
        queued_tasks.pop();

        if (task->remaining_cpu_burst() <= 0) {
            task->turnaround_time() = current_time;
            task->waiting_time() = task->turnaround_time() - task->cpu_burst();
            completed_tasks.push(task);

            /* Display */
            cout << "Task " << task->task_name() << " just finished." << endl;
        } else {
            queued_tasks.push(task);
        }
    }

    /* Finalize scheduling */
    int totalTurnaroundTime = 0, totalWaitingTime = 0, count = 0;
    while (!completed_tasks.empty()) {
        Task *task = completed_tasks.front();

        count++;
        totalTurnaroundTime += task->turnaround_time();
        totalWaitingTime += task->waiting_time();

        cout << task->task_name() << " turn-around time = " << task->turnaround_time() << ", waiting time = " << task->waiting_time() << endl;

        completed_tasks.pop();
        delete task;
    }

    /* Display Averages */
    double averageTurnaroundTime = (double) totalTurnaroundTime / (double) count;
    double averageWaitingTime = (double) totalWaitingTime / (double) count;
    cout << "Average turn-around time = " << averageTurnaroundTime << ", waiting time = " << averageWaitingTime << endl;

    return 0;
}