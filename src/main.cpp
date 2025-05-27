#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <stdexcept>
#include "Task.h"
#include "TodoList.h"
#include "FileManager.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayHeader() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "         TO-DO LIST MANAGER v1.0        \n";
    std::cout << "========================================\n";
}

void displayMenu() {
    std::cout << "\nMAIN MENU:\n";
    std::cout << "1. Add a new task\n";
    std::cout << "2. View all tasks\n";
    std::cout << "3. Mark task as completed\n";
    std::cout << "4. Remove a task\n";
    std::cout << "5. Save tasks to file\n";
    std::cout << "6. Load tasks from file\n";
    std::cout << "7. Exit\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Enter your choice (1-7): ";
}

void displayTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "\nNo tasks to display.\n";
        return;
    }

    std::cout << "\n----- Your Tasks -----\n";
    std::cout << std::left << std::setw(5) << "ID" << " | "
              << std::setw(8) << "STATUS" << " | "
              << std::setw(30) << "DESCRIPTION" << " | "
              << "CREATED ON\n";
    std::cout << std::string(70, '-') << "\n";

    for (const auto& task : tasks) {
        std::string status = task.isCompleted() ? "DONE" : "PENDING";
        std::cout << std::left << std::setw(5) << task.getId() << " | "
                  << std::setw(8) << status << " | "
                  << std::setw(30) << (task.getDescription().length() > 27 ?
                      task.getDescription().substr(0, 27) + "..." :
                      task.getDescription()) << " | "
                  << task.getFormattedCreationDate() << "\n";
    }

    std::cout << std::string(70, '-') << "\n";
    std::cout << "Total: " << tasks.size() << " task(s)\n";
}

int getMenuChoice() {
    int choice;
    while (true) {
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        } else if (choice < 1 || choice > 7) {
            std::cout << "Invalid choice. Please enter a number between 1 and 7: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

int main() {
    TodoList todoList;
    FileManager fileManager;
    bool running = true;

    try {
        if (fileManager.fileExists()) {
            displayHeader();
            std::cout << "Loading saved tasks...\n";
            auto loadedTasks = fileManager.loadTasks();
            todoList.setTasks(loadedTasks);
            std::cout << "Loaded " << loadedTasks.size() << " task(s).\n";
            pauseScreen();
        }

        while (running) {
            displayHeader();
            displayMenu();

            int choice = getMenuChoice();

            switch (choice) {
                case 1: { // Add a task
                    displayHeader();
                    std::cout << "=== ADD NEW TASK ===\n\n";
                    std::string description;
                    std::cout << "Enter task description: ";
                    std::getline(std::cin, description);

                    if (!description.empty()) {
                        todoList.addTask(description);
                        std::cout << "\nTask added successfully!\n";
                    } else {
                        std::cout << "\nTask description cannot be empty.\n";
                    }

                    pauseScreen();
                    break;
                }

                case 2: { // View tasks
                    displayHeader();
                    std::cout << "=== VIEW ALL TASKS ===\n";
                    displayTasks(todoList.getAllTasks());
                    pauseScreen();
                    break;
                }

                case 3: { // Mark task as completed
                    displayHeader();
                    std::cout << "=== MARK TASK AS COMPLETED ===\n";
                    displayTasks(todoList.getAllTasks());

                    if (todoList.getTaskCount() == 0) {
                        pauseScreen();
                        break;
                    }

                    std::cout << "\nEnter the ID of the task to mark as completed: ";
                    int taskId;
                    if (std::cin >> taskId) {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (todoList.markTaskAsCompleted(taskId)) {
                            std::cout << "\nTask marked as completed!\n";
                        } else {
                            std::cout << "\nNo task found with ID: " << taskId << "\n";
                        }
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\nInvalid input.\n";
                    }

                    pauseScreen();
                    break;
                }

                case 4: { // Remove a task
                    displayHeader();
                    std::cout << "=== REMOVE TASK ===\n";
                    displayTasks(todoList.getAllTasks());

                    if (todoList.getTaskCount() == 0) {
                        pauseScreen();
                        break;
                    }

                    std::cout << "\nEnter the ID of the task to remove: ";
                    int taskId;
                    if (std::cin >> taskId) {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Are you sure you want to delete this task? (y/n): ";
                        char confirm;
                        std::cin >> confirm;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (confirm == 'y' || confirm == 'Y') {
                            if (todoList.removeTask(taskId)) {
                                std::cout << "\nTask removed successfully!\n";
                            } else {
                                std::cout << "\nNo task found with ID: " << taskId << "\n";
                            }
                        } else {
                            std::cout << "\nTask removal canceled.\n";
                        }
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\nInvalid input.\n";
                    }

                    pauseScreen();
                    break;
                }

                case 5: { // Save tasks
                    displayHeader();
                    std::cout << "=== SAVE TASKS TO FILE ===\n";

                    if (todoList.getTaskCount() == 0) {
                        std::cout << "No tasks to save.\n";
                    } else {
                        if (fileManager.saveTasks(todoList.getAllTasks())) {
                            std::cout << "Tasks saved successfully.\n";
                        } else {
                            std::cout << "Failed to save tasks.\n";
                        }
                    }

                    pauseScreen();
                    break;
                }

                case 6: { // Load tasks
                    displayHeader();
                    std::cout << "=== LOAD TASKS FROM FILE ===\n";

                    if (!fileManager.fileExists()) {
                        std::cout << "No saved file found.\n";
                    } else {
                        if (todoList.getTaskCount() > 0) {
                            std::cout << "This will overwrite current tasks. Continue? (y/n): ";
                            char confirm;
                            std::cin >> confirm;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            if (confirm != 'y' && confirm != 'Y') {
                                std::cout << "Load canceled.\n";
                                pauseScreen();
                                break;
                            }
                        }

                        auto loadedTasks = fileManager.loadTasks();
                        todoList.setTasks(loadedTasks);
                        std::cout << "Loaded " << loadedTasks.size() << " task(s).\n";
                    }

                    pauseScreen();
                    break;
                }

                case 7: { // Exit
                    displayHeader();
                    std::cout << "=== EXIT ===\n";

                    if (todoList.getTaskCount() > 0) {
                        std::cout << "Do you want to save your tasks before exiting? (y/n): ";
                        char save;
                        std::cin >> save;
                        if (save == 'y' || save == 'Y') {
                            if (fileManager.saveTasks(todoList.getAllTasks())) {
                                std::cout << "Tasks saved successfully.\n";
                            } else {
                                std::cout << "Failed to save tasks.\n";
                            }
                        }
                    }

                    std::cout << "\nGoodbye!\n";
                    running = false;
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}