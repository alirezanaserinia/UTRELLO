#include <iostream>
#include "user.hpp"

User::User(string _name) {
    set_user(_name);
}

void User::set_user(string _name) {
    name = _name;
}

void User::set_task(Task task) {
    tasks.push_back(task);
}
void User::set_task_priority_in_user(int task_number, unsigned int priority) {
    tasks[task_number].set_priority(priority);
}
void User::set_task_time_in_user(int task_number, unsigned int time) {
    tasks[task_number].set_time(time);
}
void User::set_task_description_in_user(int task_number, string description) {
    tasks[task_number].set_description(description);
}
void User::set_task_list_in_user(int task_number, string list) {
    tasks[task_number].set_list(list);
}
void User::set_finishing_status_in_user(int task_number, bool status) {
    tasks[task_number].set_finishing_status(status);
}
void User::set_assign_status_in_user(int task_number, bool status) {
    tasks[task_number].set_assign_status(status);
}
void User::delete_task_in_user(int task_number) {
    tasks.erase(tasks.begin() + task_number);
}
int User::total_tasks_time() {
    int total_time = 0;
    for (int task_counter = 0; task_counter < tasks.size(); task_counter++)
            total_time += tasks[task_counter].get_estimated_time();
    return total_time;
}
int User::total_finished_tasks_time() {
    int total_time = 0;
    for (int task_counter = 0; task_counter < tasks.size(); task_counter++)
        if (tasks[task_counter].is_finished())
            total_time += tasks[task_counter].get_estimated_time();
    return total_time;
}
string User::get_username() { return name; }

vector<Task> User::get_tasks() { return tasks; }
