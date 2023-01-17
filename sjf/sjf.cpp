#include "Task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

bool compare(Task *lhs, Task *rhs) {
    return lhs->cpu_burst() > rhs->cpu_burst();
}

int main(int argc, char *argv[]) {
    /* Display Information */
    cout << "CS 433 Programming assignment 3\n" <<
            "Authors: Ian Murphy, Anthony Finn and Loc Huynh\n" <<
            "Date: 03/10/2022\n" <<
            "Course: CS 433 (Operating Systems)\n" <<
            "Description: Shortest Job First (SJF) CPU scheduling algorithmn implementation using a priority queue.\n" <<
            "=================================" << endl;

    /* Check Arguments */
    if (argc < 2) {
        cerr << "Usage: ./sjf <input_file>" << endl;
        exit(1);
    }

    /* Open File */
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        exit(1);
    }

    /* Prepare CPU Scheduling Task queue */
    priority_queue<Task *, vector<Task *>, decltype(&compare)> queued_tasks(compare);
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
        Task *task = queued_tasks.top();

        task->waiting_time() = current_time;
        current_time += task->cpu_burst();
        task->turnaround_time() = current_time;

        /* Simulate running task */
        task->remaining_cpu_burst() -= task->cpu_burst();
        cout << "Running task = [" << task->task_name() << "] [" << task->priority() << "] [" << task->cpu_burst() << "] for " << task->cpu_burst() << " units." << endl;

        /* Complete running task */
        completed_tasks.push(task);
        queued_tasks.pop();
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