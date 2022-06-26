#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <string>

using namespace std;

class Task {
private:
    string name;
    string list;
    string description;
    string user_name;
    unsigned int estimated_time;
    unsigned int priority;
    bool finishing_status;
    bool assign_status;
public:
    Task() {};
    Task(string _list, string _name, unsigned int _estimated_time, unsigned int _priority, string _description);

    void set_name(string task);
    void set_list(string _list);
    void set_description(string _description);
    void set_user_name(string user);
    void set_priority(unsigned int _priority);
    void set_time(unsigned int time);
    void set_finishing_status(bool status);
    void set_assign_status(bool status);

    string get_name();
    string get_list();
    string get_description();
    string get_user_name();
    int get_priority();
    int get_estimated_time();

    bool is_finished();
    bool is_assigned();

};
#endif