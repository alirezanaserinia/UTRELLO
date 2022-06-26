#include <iostream>
#include "utrello_interface.hpp"

bool UTrelloInterface::is_user_exists(string username) {
    int counter = 0;
    for (int user_counter = 0; user_counter < users.size(); user_counter++) {
        if (users[user_counter].get_username() == username)
            counter++;
    }
    return counter;
}

bool UTrelloInterface::is_task_exists(string task_name) {
    int counter = 0;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) {
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task_name)
                counter++;
    }
    return counter;
}

bool UTrelloInterface::is_list_exists(string list_name) {
    int counter = 0;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) {
        if (lists[list_counter].get_name() == list_name)
            counter++;
    }
    return counter;
}

bool UTrelloInterface::is_task_assigned(string task) {
    bool task_assign_status = false;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) {
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task)
                task_assign_status = lists[list_counter].get_tasks()[task_counter].is_assigned();
    }
    return task_assign_status;
}

string UTrelloInterface::addUser(string username) {
    if (!is_user_exists(username)) {
        User user(username);
        users.push_back(user);
        return "Success";
    }
    else
        return "User already exists";
}

void UTrelloInterface::addNewTaskToList(Task task, string list) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        if (lists[list_counter].get_name() == list) {
            lists[list_counter].set_task(task);
            return;
        }
}

string UTrelloInterface::addTask(string list, string name,
 unsigned int estimated_time, unsigned int priority, string description) {
    if (is_task_exists(name))
        return "Task already exists";
    else if (!is_list_exists(list))
        return "List does not exist";
    else {
        Task task(list, name, estimated_time, priority, description);
        addNewTaskToList(task, list);
        return "Success";
    }
}

string UTrelloInterface::addList(string name) {
    if (!is_list_exists(name)) {
        List list(name);
        lists.push_back(list);
        return "Success";
    }
    else
        return "List already exists";
}

void UTrelloInterface::editTaskInList(string task, unsigned int estimatedTime, unsigned int priority, string description) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
                lists[list_counter].set_task_time_in_list(task_counter, estimatedTime);
                lists[list_counter].set_task_priority_in_list(task_counter, priority);
                lists[list_counter].set_task_description_in_list(task_counter, description); 
                return;     
            }
}

void UTrelloInterface::editTaskItemsInUserAssignedToIt(string task, unsigned int estimatedTime, unsigned int priority, string description) {
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].get_name() == task) {
                users[user_counter].set_task_time_in_user(task_counter, estimatedTime);
                users[user_counter].set_task_priority_in_user(task_counter, priority);
                users[user_counter].set_task_description_in_user(task_counter, description);
                return;
            }
}

string UTrelloInterface::editTask(string task, unsigned int estimatedTime, unsigned int priority, string description) {
    if (is_task_exists(task)) {
        editTaskInList(task, estimatedTime, priority, description);
        if (is_task_assigned(task)) {
            editTaskItemsInUserAssignedToIt(task, estimatedTime, priority, description);
        }
        return "Success";        
    }
    else 
        return "Task does not exist";
}

Task UTrelloInterface::changeTaskAssignStatus(string task, string user) {
    Task temp_task;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
               lists[list_counter].set_assign_status_in_list(task_counter, true);
               lists[list_counter].set_user_name_in_list(task_counter, user);
               temp_task = lists[list_counter].get_tasks()[task_counter];
            }
    return temp_task;
}

string UTrelloInterface::assignTask(string task, string user) {
    if (!is_task_exists(task))
        return "Task does not exist";
    else if (!is_user_exists(user))
        return "User does not exist";
    else {
        for (int user_counter = 0; user_counter < users.size(); user_counter++)
            if (users[user_counter].get_username() == user) {
                users[user_counter].set_task(changeTaskAssignStatus(task, user));
                break;
            }
        return "Success";
    }
}

void UTrelloInterface::addTaskToNewList(string task, string list) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
                lists[list_counter].set_task_list_in_list(task_counter, list);
                for (int list_number = 0; list_number < lists.size(); list_number++)
                    if (lists[list_number].get_name() == list) {
                        lists[list_number].set_task(lists[list_counter].get_tasks()[task_counter]);
                        return;
                    }
            }
}

void UTrelloInterface::deleteTaskFromOldList(string task) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) 
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
                lists[list_counter].delete_task_in_list(task_counter);
                return;
            }
}

void UTrelloInterface::editTaskListInUserAssignedToIt(string task, string list) {
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].get_name() == task) {
                users[user_counter].set_task_list_in_user(task_counter, list);
                return;
            }
}

string UTrelloInterface::moveTask(string task, string list) {
    if (!is_task_exists(task))
        return "Task does not exist";
    else if (!is_list_exists(list))
        return "List does not exist";
    else {
        addTaskToNewList(task, list);
        deleteTaskFromOldList(task);
        editTaskListInUserAssignedToIt(task, list);
        return "Success";
    }
}

void UTrelloInterface::changeTaskFinishingStatusInList(string task) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
                lists[list_counter].set_finishing_status_in_list(task_counter, true);
                return;
            }
}

void UTrelloInterface::changeTaskFinishingStatusInUserAssignedToIt(string task) {
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].get_name() == task) {
                users[user_counter].set_finishing_status_in_user(task_counter, true);
                return;
            }
}

string UTrelloInterface::completeTask(string task) {
    if (is_task_exists(task)) {
        changeTaskFinishingStatusInList(task);
        changeTaskFinishingStatusInUserAssignedToIt(task);
        return "Success";
    }
    else 
        return "Task does not exist";
}

void UTrelloInterface::deleteTaskFromUserAssignedToIt(string task) {
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].get_name() == task) {
                users[user_counter].delete_task_in_user(task_counter);
                return;
            }
}

string UTrelloInterface::deleteTask(string task) {
    if (is_task_exists(task)) {
        deleteTaskFromOldList(task);
        if (is_task_assigned(task))
            deleteTaskFromUserAssignedToIt(task);
        return "Success";
    }
    else 
        return "Task does not exist";
}

void UTrelloInterface::deleteTasksFromUsersAssignedToThem(string list) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++) 
            if (is_task_assigned(lists[list_counter].get_tasks()[task_counter].get_name())) {
                deleteTaskFromUserAssignedToIt(lists[list_counter].get_tasks()[task_counter].get_name());
                return;
            }
}

void UTrelloInterface::deleteListFromLists(string list) {
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        if (lists[list_counter].get_name() == list) {
            lists.erase(lists.begin() + list_counter);
            return;
        }
}

string UTrelloInterface::deleteList(string list) {
    if (is_list_exists(list)) {
        deleteTasksFromUsersAssignedToThem(list);
        deleteListFromLists(list);
        return "Success";
    }
    else 
        return "List does not exist";
}

string UTrelloInterface::printTaskUserAssignedToIt(string task) {
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].get_name() == task) 
                return users[user_counter].get_username();
    return "";
}

string UTrelloInterface::printTask(string task) {
    string task_elements;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (lists[list_counter].get_tasks()[task_counter].get_name() == task) {
                task_elements = lists[list_counter].get_tasks()[task_counter].get_name() + "\n";
                task_elements += lists[list_counter].get_tasks()[task_counter].get_description() + "\n"; 
                task_elements += "Priority: " + to_string(lists[list_counter].get_tasks()[task_counter].get_priority()) + "\n";
                task_elements += "Estimated Time: " + to_string(lists[list_counter].get_tasks()[task_counter].get_estimated_time()) + "\n";
                if (is_task_assigned(task))
                    task_elements += "Assigned to " + printTaskUserAssignedToIt(task) + "\n";
                else  
                    task_elements += "Unassigned\n";
                break;
            }
    return task_elements;
}

int UTrelloInterface::printTotalEstimatedTime() {
    int total_time = 0;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (is_task_assigned(lists[list_counter].get_tasks()[task_counter].get_name())) 
                total_time += lists[list_counter].get_tasks()[task_counter].get_estimated_time();
    return total_time;
}

int UTrelloInterface::printTotalRemainingTime() {
    int total_time = 0;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if ((is_task_assigned(lists[list_counter].get_tasks()[task_counter].get_name())) && 
                (lists[list_counter].get_tasks()[task_counter].is_finished() == false)) 
                    total_time += lists[list_counter].get_tasks()[task_counter].get_estimated_time();
    return total_time;
}

string UTrelloInterface::printList(string list) {
    if (is_list_exists(list)) {
        string list_tasks = "List " + list + "\n";
        for (int list_counter = 0; list_counter < lists.size(); list_counter++)
            if (lists[list_counter].get_name() == list)
                for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++) {
                    list_tasks += to_string(lists[list_counter].get_tasks()[task_counter].get_priority());
                    list_tasks += " | " + lists[list_counter].get_tasks()[task_counter].get_name();
                    if (is_task_assigned(lists[list_counter].get_tasks()[task_counter].get_name()))
                        list_tasks += " | " + printTaskUserAssignedToIt(lists[list_counter].get_tasks()[task_counter].get_name());
                    else 
                        list_tasks += " | Unassigned";
                    list_tasks += " | " + to_string(lists[list_counter].get_tasks()[task_counter].get_estimated_time()) + "h\n";
                }
        return list_tasks;
    }
    else 
        return "List does not exist\n";
}

string UTrelloInterface::printAllLists() {
    string all_lists;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++)
        all_lists += printList(lists[list_counter].get_name()) + "\n";
    return all_lists;
}

string UTrelloInterface::printUserTasks(string user) {
    if (is_user_exists(user)) {
        string user_tasks;
        for (int user_counter = 0; user_counter < users.size(); user_counter++)
            if (users[user_counter].get_username() == user)
                for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++) {
                    user_tasks += to_string(users[user_counter].get_tasks()[task_counter].get_priority());
                    user_tasks += " | " + users[user_counter].get_tasks()[task_counter].get_name();
                    if (is_task_assigned(users[user_counter].get_tasks()[task_counter].get_name()))
                        user_tasks += " | " + user;
                    else 
                        user_tasks += " | Unassigned";
                    user_tasks += " | " + to_string(users[user_counter].get_tasks()[task_counter].get_estimated_time()) + "h\n";
                }
        return user_tasks;
    }
    else 
        return "User does not exist";
}

string UTrelloInterface::printUserUnfinishedTasks(string user) {
    if (is_user_exists(user)) {
        string user_tasks;
        for (int user_counter = 0; user_counter < users.size(); user_counter++)
            if (users[user_counter].get_username() == user) 
                for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++) 
                    if (!users[user_counter].get_tasks()[task_counter].is_finished()) {
                        user_tasks += to_string(users[user_counter].get_tasks()[task_counter].get_priority());
                        user_tasks += " | " + users[user_counter].get_tasks()[task_counter].get_name();
                        if (is_task_assigned(users[user_counter].get_tasks()[task_counter].get_name()))
                            user_tasks += " | " + user;
                        else 
                            user_tasks += " | Unassigned";
                        user_tasks += " | " + to_string(users[user_counter].get_tasks()[task_counter].get_estimated_time()) + "h\n";
                    }
        return user_tasks;
    }
    else 
        return "User does not exist";
}

int UTrelloInterface::printUserWorkload(string user) {
    if (is_user_exists(user)) {
        int total_time = 0;
        for (int user_counter = 0; user_counter < users.size(); user_counter++)
            if (users[user_counter].get_username() == user) 
                for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++) 
                    total_time += users[user_counter].get_tasks()[task_counter].get_estimated_time();
        return total_time;
    }
    else 
        return 0;
}

void UTrelloInterface::exchange_in_users(vector<User> &list_of_users, int index) {
    User temp = list_of_users[index - 1];
    list_of_users[index - 1] = list_of_users[index];
    list_of_users[index] = temp;
}

void UTrelloInterface::sort_users_by_workload(vector<User> &list_of_users) {
    for (int user_counter = 0; user_counter < list_of_users.size(); user_counter++)
        for (int index = list_of_users.size() - 1; index > user_counter; index--)
            if (list_of_users[index].total_tasks_time() < list_of_users[index - 1].total_tasks_time())
                exchange_in_users(list_of_users, index);   
}

string UTrelloInterface::printUsersByWorkload() {
    string elements;
    vector<User> list_of_users = users;
    sort_users_by_workload(list_of_users);
    for (int user_counter = 0; user_counter < list_of_users.size(); user_counter++)
        elements += list_of_users[user_counter].get_username() + "\n";
    return elements;
}

void UTrelloInterface::sort_users_by_performance(vector<User> &list_of_users) {
    for (int user_counter = 0; user_counter < list_of_users.size(); user_counter++)
        for (int index = list_of_users.size() - 1; index > user_counter; index--)
            if (list_of_users[index].total_finished_tasks_time() > list_of_users[index - 1].total_finished_tasks_time())
                exchange_in_users(list_of_users, index);
}

string UTrelloInterface::printUsersByPerformance() {
    string elements;
    vector<User> list_of_users;
    for (int user_counter = 0; user_counter < users.size(); user_counter++)
        for (int task_counter = 0; task_counter < users[user_counter].get_tasks().size(); task_counter++)
            if (users[user_counter].get_tasks()[task_counter].is_finished()) {
                list_of_users.push_back(users[user_counter]);
                break;
            }
    sort_users_by_performance(list_of_users);
    for (int user_counter = 0; user_counter < list_of_users.size(); user_counter++)
        elements += list_of_users[user_counter].get_username() + "\n";
    return elements;
}

void UTrelloInterface::exchange_in_tasks(vector<Task> &unassigned_tasks, int index) {
    Task temp = unassigned_tasks[index - 1];
    unassigned_tasks[index - 1] = unassigned_tasks[index];
    unassigned_tasks[index] = temp;
}

void UTrelloInterface::sort_vector_by_priority(vector<Task> &list_of_tasks) {
    for (int task_counter = 0; task_counter < list_of_tasks.size(); task_counter++)
        for (int index = list_of_tasks.size() - 1; index > task_counter; index--)
            if (list_of_tasks[index].get_priority() < list_of_tasks[index - 1].get_priority())
                exchange_in_tasks(list_of_tasks, index);
}

string UTrelloInterface::printUnassignedTasksByPriority() {
    string tasks_elements;
    vector<Task> unassigned_tasks;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) {
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (!lists[list_counter].get_tasks()[task_counter].is_assigned())
                unassigned_tasks.push_back(lists[list_counter].get_tasks()[task_counter]);
    }
    sort_vector_by_priority(unassigned_tasks);
    for (int task_counter = 0; task_counter < unassigned_tasks.size(); task_counter++) {
        tasks_elements += to_string(unassigned_tasks[task_counter].get_priority());
        tasks_elements += " | " + unassigned_tasks[task_counter].get_name();
        tasks_elements += " | Unassigned";
        tasks_elements += " | " + to_string(unassigned_tasks[task_counter].get_estimated_time()) + "h\n";
    }

    return tasks_elements;
}

string UTrelloInterface::unfinishedTasks(vector<Task> unfinished_tasks) {
    string elements;
    for (int task_counter = 0; task_counter < unfinished_tasks.size(); task_counter++) {
        elements += to_string(unfinished_tasks[task_counter].get_priority());
        elements += " | " + unfinished_tasks[task_counter].get_name();
        if (is_task_assigned(unfinished_tasks[task_counter].get_name()))
            elements += " | " + unfinished_tasks[task_counter].get_user_name();
        else
            elements += " | Unassigned";
        elements += " | " + to_string(unfinished_tasks[task_counter].get_estimated_time()) + "h\n";
    }
    return elements;
}

string UTrelloInterface::printAllUnfinishedTasksByPriority() {
    string tasks_elements;
    vector<Task> unfinished_tasks;
    for (int list_counter = 0; list_counter < lists.size(); list_counter++) {
        for (int task_counter = 0; task_counter < lists[list_counter].get_tasks().size(); task_counter++)
            if (!lists[list_counter].get_tasks()[task_counter].is_finished())
                unfinished_tasks.push_back(lists[list_counter].get_tasks()[task_counter]);
    }
    sort_vector_by_priority(unfinished_tasks);
    tasks_elements = unfinishedTasks(unfinished_tasks);
    return tasks_elements;
}


