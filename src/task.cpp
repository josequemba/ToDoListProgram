#include "Task.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Constructors
Task::Task() : id(0), description(""), completed(false), creationDate(0), completionDate(0) {}

Task::Task(int id, const std::string& description)
    : id(id), description(description), completed(false), completionDate(0) {
    if (id <= 0) {
        throw std::invalid_argument("Task ID must be positive");
    }
    if (description.empty()) {
        throw std::invalid_argument("Task description cannot be empty");
    }
    creationDate = time(nullptr);
}

// Getters
int Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

time_t Task::getCreationDate() const {
    return creationDate;
}

time_t Task::getCompletionDate() const {
    return completionDate;
}

// Setters
void Task::setId(int id) {
    if (id <= 0) {
        throw std::invalid_argument("Task ID must be positive");
    }
    this->id = id;
}

void Task::setDescription(const std::string& description) {
    if (description.empty()) {
        throw std::invalid_argument("Task description cannot be empty");
    }
    this->description = description;
}

// Methods
void Task::markAsCompleted() {
    completed = true;
    completionDate = time(nullptr);
}

std::string Task::getFormattedCreationDate() const {
    struct tm* timeinfo;
    char buffer[80];

    timeinfo = localtime(&creationDate);
    if (timeinfo == nullptr) {
        return "Invalid date";
    }

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return std::string(buffer);
}

std::string Task::getFormattedCompletionDate() const {
    if (!completed) {
        return "Not completed";
    }

    struct tm* timeinfo;
    char buffer[80];

    timeinfo = localtime(&completionDate);
    if (timeinfo == nullptr) {
        return "Invalid date";
    }

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return std::string(buffer);
}

// Conversion to string for file operations
std::string Task::toString() const {
    std::stringstream ss;
    ss << id << "|" << description << "|" << (completed ? "1" : "0") << "|"
       << creationDate << "|" << completionDate;
    return ss.str();
}

Task Task::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> parts;

    while (std::getline(ss, item, '|')) {
        parts.push_back(item);
    }

    if (parts.size() < 5) {
        throw std::invalid_argument("Invalid task string format: " + str);
    }

    try {
        Task task;
        task.id = std::stoi(parts[0]);
        task.description = parts[1];
        task.completed = (parts[2] == "1");
        task.creationDate = std::stol(parts[3]);
        task.completionDate = std::stol(parts[4]);

        if (task.id <= 0) {
            throw std::invalid_argument("Invalid task ID: " + parts[0]);
        }

        return task;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Error parsing task: " + std::string(e.what()));
    }
}