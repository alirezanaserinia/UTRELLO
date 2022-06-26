#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "list.hpp"
#include "task.hpp"
#include "user.hpp"
// #include <bits/stdc++.h>

class UTrelloInterface {
private:
	vector<List> lists;
	vector<User> users;
public:
	UTrelloInterface() {};
	
	bool is_user_exists(string username);
	bool is_task_exists(string task_name);
	bool is_list_exists(string list_name);
	bool is_task_assigned(string task);

	string addUser(string username);

	void addNewTaskToList(Task task, string list);
	string addTask(string list, string name, unsigned int estimated_time, unsigned int priority, string description);
	
	string addList(string name);

	void editTaskInList(string task, unsigned int estimatedTime, unsigned int priority, string description);
	void editTaskItemsInUserAssignedToIt(string task, unsigned int estimatedTime, unsigned int priority, string description);
	string editTask(string task, unsigned int estimatedTime, unsigned int priority, string description);

	Task changeTaskAssignStatus(string task, string user);
	string assignTask(string task, string user);

	void addTaskToNewList(string task, string list);
	void deleteTaskFromOldList(string task);
	void editTaskListInUserAssignedToIt(string task, string list);
	string moveTask(string task, string list);

	void changeTaskFinishingStatusInList(string task);
	void changeTaskFinishingStatusInUserAssignedToIt(string task);
	string completeTask(string task);

	void deleteTaskFromUserAssignedToIt(string task);
	string deleteTask(string task);

	void deleteTasksFromUsersAssignedToThem(string list);
	void deleteListFromLists(string list);
	string deleteList(string list);

	string printTaskUserAssignedToIt(string task);
	string printTask(string task);

	int printTotalEstimatedTime();
	
	int printTotalRemainingTime();

	string printList(string list);

	string printAllLists();

	string printUserTasks(string user);

	string printUserUnfinishedTasks(string user);

    int printUserWorkload(string user);

	void exchange_in_users(vector<User> &list_of_users, int index);
	void sort_users_by_workload(vector<User> &list_of_users);
	string printUsersByWorkload();


	void sort_users_by_performance(vector<User> &list_of_users);
	string printUsersByPerformance();

	void exchange_in_tasks(vector<Task> &unassigned_tasks, int index);
	void sort_vector_by_priority(vector<Task> &unassigned_tasks);	
	string printUnassignedTasksByPriority();

	string unfinishedTasks(vector<Task> unfinished_tasks);
	string printAllUnfinishedTasksByPriority();

};
#endif
