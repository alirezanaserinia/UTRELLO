#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <vector>
#include <string>
#include "task.hpp"

using namespace std;

class List {
private:
    string name;
    vector<Task> tasks;
public:
    List(string _name);
    void set_name(string _name);
    void set_task(Task task);

    string get_name();
    vector<Task> get_tasks();

    void set_task_priority_in_list(int task_number, unsigned int priority);
    void set_task_time_in_list(int task_number, unsigned int time);
    void set_task_description_in_list(int task_number, string description);
    void set_user_name_in_list(int task_number, string user_name);
    void set_task_list_in_list(int task_number, string list);
    void set_finishing_status_in_list(int task_number, bool status);
    void set_assign_status_in_list(int task_number, bool status);
    void delete_task_in_list(int task_number);
    
};
#endif

