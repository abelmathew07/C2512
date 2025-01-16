#include <iostream>
#include <cstring>
#include <utility>
#include <memory>  // For smart pointers
#include <vector>  // For dynamic array of tasks

using namespace std;

// Employee class
class Employee {
private:
    unique_ptr<int> id;
    unique_ptr<int> age;
    unique_ptr<char[]> name;

public:
    // Constructor
    Employee(int id, int age, const char* name) {
        this->id = make_unique<int>(id);
        this->age = make_unique<int>(age);
        this->name = make_unique<char[]>(strlen(name) + 1);
        strcpy(this->name.get(), name);
    }

    // Default constructor
    Employee() : id(nullptr), age(nullptr), name(nullptr) {}

    // Move Constructor
    Employee(Employee&& other) noexcept
        : id(std::move(other.id)), age(std::move(other.age)), name(std::move(other.name)) {}

    // Move Assignment Operator
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            id = std::move(other.id);
            age = std::move(other.age);
            name = std::move(other.name);
        }
        return *this;
    }

    // << operator to display Employee details
    friend ostream& operator<<(ostream& os, const Employee& emp);

    // >> operator to read Employee details
    friend istream& operator>>(istream& is, Employee& emp);

    // Getter methods for private members
    int getId() const { return *id; }
    int getAge() const { return *age; }
    const char* getName() const { return name.get(); }
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << *emp.id << " " << *emp.age << " " << emp.name.get();
    return os;
}

istream& operator>>(istream& is, Employee& emp) {
    int id, age;
    string name;
    cout << "Enter Employee ID: ";
    is >> id;
    cout << "Enter Employee Age: ";
    is >> age;
    cout << "Enter Employee Name: ";
    is.ignore();  // To ignore the newline after age
    getline(is, name);
    
    emp.id = make_unique<int>(id);
    emp.age = make_unique<int>(age);
    emp.name = make_unique<char[]>(name.length() + 1);
    strcpy(emp.name.get(), name.c_str());
    return is;
}

// Programmer class (derived from Employee)
class Programmer : public Employee {
private:
    vector<string> tasks; // Vector for tasks (no need for dynamic memory management)

public:
    // Default constructor
    Programmer() : Employee(), tasks() {}

    // Constructor
    Programmer(int id, int age, const char* name, int taskCount, const string* tasksArray)
        : Employee(id, age, name) {
        tasks.reserve(taskCount);
        for (int i = 0; i < taskCount; ++i) {
            tasks.push_back(tasksArray[i]);  // Populate tasks vector
        }
    }

    // Move Constructor
    Programmer(Programmer&& other) noexcept
        : Employee(std::move(other)), tasks(std::move(other.tasks)) {}

    // Move Assignment Operator
    Programmer& operator=(Programmer&& other) noexcept {
        if (this != &other) {
            Employee::operator=(std::move(other));
            tasks = std::move(other.tasks);
        }
        return *this;
    }

    // << operator to display Programmer details
    friend ostream& operator<<(ostream& os, const Programmer& prog);

    // >> operator to read Programmer details
    friend istream& operator>>(istream& is, Programmer& prog);
};

ostream& operator<<(ostream& os, const Programmer& prog) {
    os << static_cast<const Employee&>(prog) << " | Tasks: ";
    
    if (prog.tasks.empty()) {
        os << "No tasks available.";  // Debugging: Add check for empty task vector
    } else {
        for (size_t i = 0; i < prog.tasks.size(); ++i) {
            os << prog.tasks[i] << (i < prog.tasks.size() - 1 ? ", " : "");
        }
    }

    return os;
}

istream& operator>>(istream& is, Programmer& prog) {
    Employee tempEmp;
    is >> tempEmp;  // Read the base Employee data
    
    int taskCount;
    cout << "Enter number of tasks: ";
    is >> taskCount;

    string* tasksArray = new string[taskCount];
    cout << "Enter tasks:" << endl;
    for (int i = 0; i < taskCount; ++i) {
        is >> ws;  // to discard any leading whitespace (important for getline)
        getline(is, tasksArray[i]);
    }

    prog = Programmer(tempEmp.getId(), tempEmp.getAge(), tempEmp.getName(), taskCount, tasksArray);

    delete[] tasksArray;  // Clean up the dynamically allocated array
    return is;
}

int main() {
    int N;
    cout << "Enter the number of programmers: ";
    cin >> N;

    vector<Programmer> programmers(N);

    // Read programmers from the user input
    for (int i = 0; i < N; ++i) {
        cout << "Enter details for Programmer " << (i + 1) << endl;
        cin >> programmers[i];  // Overloaded >> operator
    }

    // Display all programmers
    cout << "\nProgrammer details:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << programmers[i] << endl;
    }

    return 0;
}