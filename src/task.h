#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

// Task represents a single to-do item with metadata like timestamps and completion status
class Task {
private:
    int id;                         // Unique task identifier
    std::string description;        // Task details
    bool completed;                 // Flag for completion status
    time_t creationDate;            // When the task was created
    time_t completionDate;          // When it was marked completed (if at all)

public:
    // Constructors
    Task(); // Default constructor for flexibility (e.g. file loading)
    Task(int id, const std::string& description); // Main constructor with validation

    // Basic accessors
    int getId() const;
    std::string getDescription() const;
    bool isCompleted() const;
    time_t getCreationDate() const;
    time_t getCompletionDate() const;

    // Mutators with validation
    void setId(int id);
    void setDescription(const std::string& description);

    // Actions
    void markAsCompleted();                         // Sets completion and timestamps it
    std::string getFormattedCreationDate() const;   // For readable display
    std::string getFormattedCompletionDate() const;

    // For saving/loading to disk
    std::string toString() const;                   // Serialize to string
    static Task fromString(const std::string& str); // Parse from string
};

#endif // TASK_H