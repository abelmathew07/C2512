 //1.3 Programmer { string* tasks; int taskCount; } : Employee | tasks is the multiple tasks - array of task 
        // swap function overloadable
        // here, create the dynamic programmer object assigned to employee pointer.
        // field 'tasks' is dynamic memoery.
        // operator << overloadable, swap is overridden.


#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

// Employee class
class Employee {
private:
    int* id;
    int* age;     
    char* name;

public:
    // Constructor
    Employee(int id, int age, const char* name) {
        this->id = new int(id);                  
        this->age = new int(age);   
        this->name = new char[strlen(name) + 1]; 
        strcpy(this->name, name);
    }

    // Destructor
    virtual ~Employee() {
        delete id;   // Free memory for id
        delete age;  // Free memory for age
        delete[] name; // Free memory for name
    }

    // Move Constructor
    Employee(Employee&& other) noexcept 
        : id(other.id), age(other.age), name(other.name) {
        other.id = nullptr;
        other.age = nullptr;
        other.name = nullptr; // Nullify the source to prevent double deletion
    }

    // Move Assignment Operator
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            // Free existing memory
            delete id;
            delete age;
            delete[] name;

            // Steal resources from other
            id = other.id;
            age = other.age;
            name = other.name;

            // Nullify the source
            other.id = nullptr;
            other.age = nullptr;
            other.name = nullptr;
        }
        return *this;
    }

    // Swap Function using Move Constructor
    virtual void swap(Employee& other) {
        Employee temp(std::move(other)); // Move other into temp
        other = std::move(*this);       // Move this into other
        *this = std::move(temp);        // Move temp back into this
    }

    // << operator to display Employee details
    friend ostream& operator<<(ostream& os, const Employee& emp);
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << *emp.id << " " << *emp.age << " " << emp.name;
    return os;
}

// Programmer class (derived from Employee)
class Programmer : public Employee {
private:
    string* tasks; // Array of tasks
    int taskCount; // Number of tasks

public:
    // Constructor
    Programmer(int id, int age, const char* name, int taskCount, const string* tasks)
        : Employee(id, age, name), taskCount(taskCount) {
        this->tasks = new string[taskCount];
        for (int i = 0; i < taskCount; ++i) {
            this->tasks[i] = tasks[i];
        }
    }

    // Destructor
    ~Programmer() {
        delete[] tasks; // Free dynamically allocated memory for tasks
    }

    // Move Constructor
    Programmer(Programmer&& other) noexcept
        : Employee(std::move(other)), taskCount(other.taskCount), tasks(other.tasks) {
        other.tasks = nullptr; // Nullify the source's tasks to prevent double deletion
    }

    // Move Assignment Operator
    Programmer& operator=(Programmer&& other) noexcept {
        if (this != &other) {
            // Free existing resources
            delete[] tasks;

            // Move base class resources
            Employee::operator=(std::move(other));

            // Steal tasks array from other
            tasks = other.tasks;
            taskCount = other.taskCount;

            // Nullify the source's tasks
            other.tasks = nullptr;
        }
        return *this;
    }

    // Swap function using Move Constructor
    void swap(Programmer& other) {
        Programmer temp(std::move(other)); // Move other into temp
        other = std::move(*this);          // Move this into other
        *this = std::move(temp);           // Move temp back into this
    }

    // Overload << operator to display Programmer details
    friend ostream& operator<<(ostream& os, const Programmer& prog);
};

ostream& operator<<(ostream& os, const Programmer& prog) {
    os << static_cast<const Employee&>(prog) << " | Tasks: ";
    for (int i = 0; i < prog.taskCount; ++i) {
        os << prog.tasks[i] << (i < prog.taskCount - 1 ? ", " : "");
    }
    return os;
}

int main() {
    // Creating Employee and Programmer objects
    const string tasks1[] = {"Code", "Debug", "Test"};
    Programmer p1(101, 30, "Alice", 3, tasks1);

    const string tasks2[] = {"Design", "Develop", "Deploy"};
    Programmer p2(102, 28, "Bob", 3, tasks2);

    cout << "Before swapping:" << endl;
    cout << p1 << endl; // Output: 101 30 Alice | Tasks: Code, Debug, Test
    cout << p2 << endl; // Output: 102 28 Bob | Tasks: Design, Develop, Deploy

    p1.swap(p2);

    cout << "After swapping:" << endl;
    cout << p1 << endl; // Output: 102 28 Bob | Tasks: Design, Develop, Deploy
    cout << p2 << endl; // Output: 101 30 Alice | Tasks: Code, Debug, Test

    return 0;