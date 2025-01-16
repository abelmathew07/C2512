#include<iostream>
#include <iomanip>

using namespace std;
const int MAX_YEAR_EXPERIENCE = 100;

class Doctor {
    friend class DoctorManager;
private:
    string DoctorID;
    int YearsOfExperience;

public:
    bool GreaterThan(const Doctor& other);
    bool LessThan(const Doctor& other);

    // Getters and Setters
    string GetDoctorID();
    int GetYearsOfExperience();
};


class DoctorManager {
    friend class DoctorAggregator;
    friend int main();
private:
    Doctor doctors[MAX_YEAR_EXPERIENCE]; // Array of doctors (reusing MAX_YEAR_EXPERIENCE constant for simplicity)
    int numDoctors;

public:
    int findIndexById(string DoctorID);

    void create();
    void displayAll();
    void editById();
    void deleteById();

    DoctorManager();
};


class DoctorAggregator {
public:
    int findMin(DoctorManager& manager);
    int findMax(DoctorManager& manager);
    int findSecondMin(DoctorManager& manager);
    int findSecondMax(DoctorManager& manager);
};

void printMenu();

int main() {
    DoctorManager manager;
    DoctorAggregator aggregator;
   
    int choice;

    do {
        printMenu(); 
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.create();    break;
            case 2: manager.displayAll();  break;
            case 3: manager.editById();      break;
            case 4: manager.deleteById();    break;
            case 5: 
                cout << "Doctor with Min Experience: " 
                     << manager.doctors[aggregator.findMin(manager)].GetDoctorID() 
                     << " with Years of Experience: " 
                     << manager.doctors[aggregator.findMin(manager)].GetYearsOfExperience() 
                     << endl;
                break;
            case 6: 
                cout << "Doctor with Max Experience: " 
                     << manager.doctors[aggregator.findMax(manager)].GetDoctorID() 
                     << " with Years of Experience: " 
                     << manager.doctors[aggregator.findMax(manager)].GetYearsOfExperience() 
                     << endl;
                break;
            case 7: 
                cout << "Doctor with 2nd Min Experience: " 
                     << manager.doctors[aggregator.findSecondMin(manager)].GetDoctorID() 
                     << " with Years of Experience: " 
                     << manager.doctors[aggregator.findSecondMin(manager)].GetYearsOfExperience() 
                     << endl;
                break;
            case 8: 
                cout << "Doctor with 2nd Max Experience: " 
                     << manager.doctors[aggregator.findSecondMax(manager)].GetDoctorID() 
                     << " with Years of Experience: " 
                     << manager.doctors[aggregator.findSecondMax(manager)].GetYearsOfExperience() 
                     << endl;
                break;
            case 9:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}


void DoctorManager::create() {
    if (numDoctors >= MAX_YEAR_EXPERIENCE) {
        cout << "Error: Maximum doctor limit reached.\n";
        return;
    }

    string DoctorID;
    int YearsOfExperience;

    cout << "Enter Doctor ID: ";
    cin >> DoctorID;

    if (findIndexById(DoctorID) != -1) {
        cout << "Error: Doctor ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter Years of Experience: ";
    cin >> YearsOfExperience;

    doctors[numDoctors].DoctorID = DoctorID;
    doctors[numDoctors].YearsOfExperience = YearsOfExperience;
    numDoctors++;

    cout << "Doctor added successfully.\n";
}

void DoctorManager::displayAll() {
    if (numDoctors == 0) {
        cout << "No doctors available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   Doctor ID    | Years Of Experience         |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numDoctors; i++) {
        cout << "| " << setw(13) << doctors[i].DoctorID << " | "
             << setw(23) << doctors[i].YearsOfExperience << " |\n";
    }
    cout << "------------------------------------------------\n";
}

int DoctorManager::findIndexById(string DoctorID) {
    for (int i = 0; i < numDoctors; i++) {
        if (doctors[i].DoctorID == DoctorID) {
            return i;
        }
    }
    return -1;
}

void DoctorManager::editById() {
    string DoctorID;
    cout << "Enter Doctor ID to edit: ";
    cin >> DoctorID;

    int index = findIndexById(DoctorID);
    if (index == -1) {
        cout << "Error: Doctor ID not found.\n";
        return;
    }

    cout << "Current Years of Experience: " << doctors[index].YearsOfExperience << "\n";

    cout << "Enter New Years of Experience: ";
    cin >> doctors[index].YearsOfExperience;

    cout << "Doctor updated successfully.\n";
}

void DoctorManager::deleteById() {
    string DoctorID;
    cout << "Enter Doctor ID to delete: ";
    cin >> DoctorID;

    int index = findIndexById(DoctorID);
    if (index == -1) {
        cout << "Error: Doctor ID not found.\n";
        return;
    }

    for (int i = index; i < numDoctors - 1; i++) {
        doctors[i] = doctors[i + 1];
    }
    numDoctors--;

    cout << "Doctor deleted successfully.\n";
}

DoctorManager::DoctorManager() {
    numDoctors = 0;
}


bool Doctor::GreaterThan(const Doctor& other) {
    return (YearsOfExperience > other.YearsOfExperience);
}

bool Doctor::LessThan(const Doctor& other) {
    return (YearsOfExperience < other.YearsOfExperience);
}

string Doctor::GetDoctorID() {
    return DoctorID;
}

int Doctor::GetYearsOfExperience() {
    return YearsOfExperience;
}


int DoctorAggregator::findMin(DoctorManager& manager) {
    Doctor* arr = manager.doctors;
    int& n = manager.numDoctors;
    int minIndex = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i].LessThan(arr[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}

int DoctorAggregator::findMax(DoctorManager& manager) {
    Doctor* arr = manager.doctors;
    int& n = manager.numDoctors;
    int maxIndex = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i].GreaterThan(arr[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int DoctorAggregator::findSecondMin(DoctorManager& manager) {
    Doctor* arr = manager.doctors;
    int& n = manager.numDoctors;
    int minIndex = findMin(manager);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;

    for (int i = 0; i < n; ++i) {
        if (i != minIndex && arr[i].LessThan(arr[secondMinIndex])) {
            secondMinIndex = i;
        }
    }
    return secondMinIndex;
}

int DoctorAggregator::findSecondMax(DoctorManager& manager) {
    Doctor* arr = manager.doctors;
    int& n = manager.numDoctors;
    int maxIndex = findMax(manager);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;

    for (int i = 0; i < n; ++i) {
        if (i != maxIndex && arr[i].GreaterThan(arr[secondMaxIndex])) {
            secondMaxIndex = i;
        }
    }
    return secondMaxIndex;
}


void printMenu() {
    cout << "\n=== Doctor Management System ===\n";
    cout << "1. Add Doctor\n";
    cout << "2. Display All Doctors\n";
    cout << "3. Edit Doctor by ID\n";
    cout << "4. Delete Doctor by ID\n";
    cout << "5. Find Doctor with Minimum Experience\n";
    cout << "6. Find Doctor with Maximum Experience\n";
    cout << "7. Find Doctor with Second Minimum Experience\n";
    cout << "8. Find Doctor with Second Maximum Experience\n";
    cout << "9. Exit\n";
}
