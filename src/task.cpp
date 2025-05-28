#include "Task.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Default constructor: sets safe defaults for everything
Task::Task() : id(0), description(""), completed(false), creationDate(0), completionDate(0) {}

// Main constructor: ensures every task has a valid ID and description
Task::Task(int id, const std::string& description)
    : id(id), description(description), completed(false), completionDate(0) {

    if (id <= 0) {
        throw std::invalid_argument("Task ID must be positive");
    }
    if (description.empty()) {
        throw std::invalid_argument("Task description cannot be empty");
    }

    creationDate = time(nullptr); // Timestamp when task is created
}

// Getters
int Task::getId() const { return id; }
std::string Task::getDescription() const { return description; }
bool Task::isCompleted() const { return completed; }
time_t Task::getCreationDate() const { return creationDate; }
time_t Task::getCompletionDate() const { return completionDate; }

// Setters with validation
void Task::setId(int id) {
    if (id <= 0) throw std::invalid_argument("Task ID must be positive");
    this->id = id;
}

void Task::setDescription(const std::string& description) {
    if (description.empty()) throw std::invalid_argument("Task description cannot be empty");
    this->description = description;
}

// Marks the task complete and records the time
void Task::markAsCompleted() {
    completed = true;
    completionDate = time(nullptr);
}

// Converts creation time to readable string
std::string Task::getFormattedCreationDate() const {
    struct tm* timeinfo = localtime(&creationDate);
    if (!timeinfo) return "Invalid date";

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

// Converts completion time to readable string, or shows it's not done
std::string Task::getFormattedCompletionDate() const {
    if (!completed) return "Not completed";

    struct tm* timeinfo = localtime(&completionDate);
    if (!timeinfo) return "Invalid date";

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

// Serializes the task to a string for saving to file
std::string Task::toString() const {
    std::stringstream ss;
    ss << id << "|" << description << "|" << (completed ? "1" : "0") << "|"
       << creationDate << "|" << completionDate;
    return ss.str();
}

// Parses a task from a string (e.g. when loading from file)
Task Task::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> parts;

    // Split on |
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