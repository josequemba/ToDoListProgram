#include "TodoList.h"
#include <algorithm>

// Constructor
TodoList::TodoList() : nextTaskId(1) {}

// Methods
void TodoList::addTask(const std::string& description) {
    Task newTask(nextTaskId, description);
    tasks.push_back(newTask);
    nextTaskId++;
}

bool TodoList::removeTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [id](const Task& task) { return task.getId() == id; });

    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }

    return false;
}

bool TodoList::markTaskAsCompleted(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.markAsCompleted();
            return true;
        }
    }

    return false;
}

std::vector<Task> TodoList::getAllTasks() const {
    return tasks;
}

Task* TodoList::getTaskById(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            return &task;
        }
    }

    return nullptr;
}

void TodoList::clearAllTasks() {
    tasks.clear();
    nextTaskId = 1;
}

int TodoList::getTaskCount() const {
    return tasks.size();
}

std::vector<Task> TodoList::getCompletedTasks() const {
    std::vector<Task> completedTasks;

    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            completedTasks.push_back(task);
        }
    }

    return completedTasks;
}

std::vector<Task> TodoList::getPendingTasks() const {
    std::vector<Task> pendingTasks;

    for (const auto& task : tasks) {
        if (!task.isCompleted()) {
            pendingTasks.push_back(task);
        }
    }

    return pendingTasks;
}

void TodoList::setTasks(const std::vector<Task>& tasks) {
    this->tasks = tasks;

    // Update nextTaskId to be greater than the maximum task ID
    nextTaskId = 1;
    for (const auto& task : tasks) {
        if (task.getId() >= nextTaskId) {
            nextTaskId = task.getId() + 1;
        }
    }
}