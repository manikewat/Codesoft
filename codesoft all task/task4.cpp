#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Task structure to hold task information
struct Task {
    string description;
    bool completed;
};

// Function prototypes
void displayMenu();
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);

int main() {
    vector<Task> tasks;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // To ignore any leftover newline character in the input buffer

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "\nTo-Do List Manager" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to add a task
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully." << endl;
}

// Function to view all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    cout << "\nTask List:" << endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description << " [" 
             << (tasks[i].completed ? "Completed" : "Pending") << "]" << endl;
    }
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    viewTasks(tasks);

    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;
    cin.ignore();  // To ignore any leftover newline character in the input buffer

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Task marked as completed." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

// Function to remove a task
void removeTask(vector<Task>& tasks) {
    viewTasks(tasks);

    int index;
    cout << "Enter task number to remove: ";
    cin >> index;
    cin.ignore();  // To ignore any leftover newline character in the input buffer

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task removed successfully." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}
