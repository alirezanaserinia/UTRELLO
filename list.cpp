#include <iostream>
#include <string>
#include "list.hpp"

List::List(string _name) {
    set_name(_name);   
}

void List::set_name(string _name) {
    name = _name;
}

void List::set_task(Task task) {
    tasks.push_back(task);
}

void List::set_task_priority_in_list(int task_number, unsigned int priority) {
    tasks[task_number].set_priority(priority);
}

void List::set_task_time_in_list(int task_number, unsigned int time) {
    tasks[task_number].set_time(time);
}
void List::set_task_description_in_list(int task_number, string description) {
    tasks[task_number].set_description(description);
}
void List::set_user_name_in_list(int task_number, string user_name) {
    tasks[task_number].set_user_name(user_name);
}
void List::set_task_list_in_list(int task_number, string list) {
    tasks[task_number].set_list(list);
}
void List::set_finishing_status_in_list(int task_number, bool status) {
    tasks[task_number].set_finishing_status(status);
}
void List::set_assign_status_in_list(int task_number, bool status) {
    tasks[task_number].set_assign_status(status);
}
void List::delete_task_in_list(int task_number) {
    tasks.erase(tasks.begin() + task_number);
}

string List::get_name() { return name; }

vector<Task> List::get_tasks() { return tasks; }
