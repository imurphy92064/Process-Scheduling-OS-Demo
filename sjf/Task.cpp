#include "Task.h"

Task::Task(string task_name_, int priority_, int cpu_burst_) : _task_name(task_name_), _priority(priority_), _cpu_burst(cpu_burst_), _remaining_cpu_burst(cpu_burst_) { };

string& Task::task_name() {
    return _task_name;
}

const string& Task::task_name() const {
    return _task_name;
}

int& Task::priority() {
    return _priority;
}

const int& Task::priority() const {
    return _priority;
}

int& Task::cpu_burst() {
    return _cpu_burst;
}

const int& Task::cpu_burst() const {
    return _cpu_burst;
}

int& Task::remaining_cpu_burst() {
    return _remaining_cpu_burst;
}

const int& Task::remaining_cpu_burst() const {
    return _remaining_cpu_burst;
}

int& Task::waiting_time() {
    return _waiting_time;
}

const int& Task::waiting_time() const {
    return _waiting_time;
}

int& Task::turnaround_time() {
    return _turnaround_time;
}

const int& Task::turnaround_time() const {
    return _turnaround_time;
}