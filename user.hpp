#ifndef __USER_HPP__
#define __USER_HPP__

#include <vector>
#include <string>
#include "task.hpp"

using namespace std;

class User {
private:
    string name;
    vector<Task> tasks;
public:
    User(string _name);

    void set_user(string _name);
    void set_task(Task task);
    void set_task_priority_in_user(int task_number, unsigned int priority);
    void set_task_time_in_user(int task_number, unsigned int time);
    void set_task_description_in_user(int task_number, string description);
    void set_task_list_in_user(int task_number, string list);
    void set_finishing_status_in_user(int task_number, bool status);
    void set_assign_status_in_user(int task_number, bool status);
    void delete_task_in_user(int task_number);
    int total_tasks_time();
    int total_finished_tasks_time();
    
    string get_username();
    vector<Task> get_tasks();
};
#endif

