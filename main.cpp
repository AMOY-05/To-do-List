#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>

using namespace std;

// Single Todo Item
struct Task {
    string description;
    string dueDate;
    bool completed;
};

// Adding New task
void AddTask(vector<Task>& tasks){
    Task newTask;
    cout << "Enter Description: " << flush;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, newTask.description);

    cout << "Enter due date (DD/MM/YY): " << flush;
    getline(cin, newTask.dueDate);

    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task Added Successfully....\n" << endl;
}
// Viewing Tasks
void viewTask(const vector<Task>& tasks){
    if (tasks.empty()){
        cout << "No tasks in the list.....\n" << endl;
    }
    cout << "\n----Your Todo List----\n" << endl;
    for(size_t i = 0; i < tasks.size(); i++){
        cout << (i +  1) << ". ";
        cout << "[";
        if(tasks[i].completed){
            cout << "X";
        }else{
            cout << " ";
        }
        cout << "]";
        cout << tasks[i].description;
        if(!tasks[i].dueDate.empty()){
            cout << "(Due Date: " << tasks[i].dueDate << ")" ;
        }
        cout << "\n";
    }
    cout << "--------------------------" << endl;
}
// Mark a task as complete
void markTaskComplete(vector<Task>& tasks){
    viewTask(tasks);  // Show tasks first so that the one to be marked will be known by the user
    if(tasks.empty()){
        return;
    }

    cout << "Enter the number of tasks you want to mark to be completed: " << flush;
    int TaskNumber;
    cin >> TaskNumber;

    if(TaskNumber > 0 && TaskNumber <= tasks.size()){
        tasks[TaskNumber - 1].completed = true;

        cout << "Task marked Completed" << endl;
    }else{
        cout << "Task Number not available." << endl;
    }
}
// To delete Task
void deleteTask(vector<Task>& tasks){
    viewTask(tasks);
    if(tasks.empty()){
        return;
    }
    cout << "Enter the number of the task to be deleted: " << flush;
    int TaskNumber;
    cin >> TaskNumber;

    if(TaskNumber > 0 && TaskNumber <= tasks.size()){
        tasks.erase(tasks.begin() + (TaskNumber-1));
        cout << "Task Deleted Successfully...\n" << endl;
    }else{
        cout << "Invalid Task Number.....\n" <<endl;
    }
}
// Display Menu
void displayMenu(){
    cout << "\n---Todo Lists Menu----\n" << endl;
    cout << "1. Add Task\n" << endl;
    cout << "2. View Task\n" << endl;
    cout << "3. Mark Test Completed\n" << endl;
    cout << "4. Delete Task\n" << endl;
    cout << "5. Save Tasks\n" << endl;
    cout << "6. Load Tasks\n" << endl;
    cout << "7. Exit\n" << endl;

    cout << "Enter your choice: " << flush;

}
// Save file
void saveTask(const vector<Task>& tasks, const string& filename = "tasks.txt"){
    ofstream outFile(filename);
    if(!outFile.is_open()){
        cerr << "Error: Could not open file for saving.\n";
        return;
    }
    for(const auto& task: tasks){
        outFile << task.description << "|"
                << task.dueDate << "|"
                << task.completed << "\n";
    }
    outFile.close();
    cout  << "Tasks save to " << filename << endl;
}
// Load file
void LoadTask(vector<Task>& tasks, const string& filename = "tasks.txt"){
    ifstream inFile(filename);
    if(!inFile.is_open()){
        cerr << "The tasks file does not exist. \n";
        return;
    }

    tasks.clear(); // clear existing tasks before loading.
    string line;
    while(getline(inFile, line)){
        Task loadedTask;
        size_t firstDoLimiter = line.find('|');
        size_t secondDoLimiter = line.find('|', firstDoLimiter + 1);

        if(firstDoLimiter == string::npos || secondDoLimiter == string::npos){
            cerr << "Warning: Malformed line in tasks file: " << line << "\n";
            continue;
        }

        loadedTask.description = line.substr(0, firstDoLimiter);
        loadedTask.dueDate = line.substr(firstDoLimiter + 1, secondDoLimiter - (firstDoLimiter + 1));
        loadedTask.completed = (line.substr(secondDoLimiter + 1) == "1");  // Convert 1 to true, 0 to false

        tasks.push_back(loadedTask);
    }
    inFile.close();
    cout << "Tasks loaded from " << filename << "\n" ;
}

int main()
{
    cout <<  "\t ===============" << endl;
    cout << "\t    TODO LIST " << endl;
    cout << "\t ===============" << endl;

    vector <Task> tasks;
    int choice;

    LoadTask(tasks);

    do{
        displayMenu();
        cin >> choice;

        switch(choice){
        case 1:
            AddTask(tasks);
            break;
        case 2:
            viewTask(tasks);
            break;
        case 3:
            markTaskComplete(tasks);
            break;
        case 4:
            deleteTask(tasks);
            break;
        case 5:
            saveTask(tasks);
            break;
        case 6:
            LoadTask(tasks);
            break;
        case 7:
            saveTask(tasks);
            cout << "Exiting Todo list......Bye" << endl;
        default:
            cout << "Choice not recognized.....Please Try again" << endl;
            break;
        }
    }while(choice != 7);

    return 0;
}
