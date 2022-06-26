#include <iostream>
#include <string>
#include "task.hpp"

Task::Task(string _list, string _name, unsigned int _estimated_time, unsigned int _priority, string _description) {
    set_name(_name);
    set_list(_list);
    set_description(_description);
    set_time(_estimated_time);
    set_priority(_priority);
    set_finishing_status(false);
    set_assign_status(false);
}

void Task::set_name(string task) {
    name = task;
}

void Task::set_list(string _list) {
    list = _list; 
}

void Task::set_description(string _description) {
    description = _description;
}

void Task::set_user_name(string user) {
    user_name = user;
}

void Task::set_priority(unsigned int _priority) {
    priority = _priority;
}

void Task::set_time(unsigned int time) {
    estimated_time = time;
}

void Task::set_finishing_status(bool status) {
    finishing_status = status;
}

void Task::set_assign_status(bool status) {
    assign_status = status;
}



string Task::get_name() { return name; }
string Task::get_list() { return list; }
string Task::get_description() { return description; }
string Task::get_user_name() { return user_name; }
int Task::get_priority() { return priority; }
int Task::get_estimated_time() { return estimated_time; }

bool Task::is_finished() { return finishing_status; }
bool Task::is_assigned() { return assign_status; }