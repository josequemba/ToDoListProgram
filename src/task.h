#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

class Task {
private:
    int id;
    std::string description;
    bool completed;
    time_t creationDate;
    time_t completionDate;

public:
    // Constructors
    Task();
    Task(int id, const std::string& description);

    // Getters
    int getId() const;
    std::string getDescription() const;
    bool isCompleted() const;
    time_t getCreationDate() const;
    time_t getCompletionDate() const;

    // Setters
    void setId(int id);
    void setDescription(const std::string& description);

    // Methods
    void markAsCompleted();
    std::string getFormattedCreationDate() const;
    std::string getFormattedCompletionDate() const;

    // Conversion to string for file operations
    std::string toString() const;
    static Task fromString(const std::string& str);
};

#endif // TASK_H