#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Doctor {
    friend class DoctorManager;
private:
    string DoctorID;
    int YearsOfExperience;

public:
    // Getters and Setters
    string GetDoctorID();
    int GetYearsOfExperience();
};

class DoctorManager {
    friend int main();

private:
    vector<Doctor> doctors; // Using vector instead of array

public:
    int findIndexById(string DoctorID);

    void create();
    void displayAll();
    void editById();
    void deleteById();

    DoctorManager();
};
void printMenu();

int main() {
    DoctorManager manager;
    int choice;

    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.create();    break;
            case 2: manager.displayAll();  break;
            case 3: manager.editById();    break;
            case 4: manager.deleteById();  break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

void DoctorManager::create() {
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

    Doctor newDoctor;
    newDoctor.DoctorID = DoctorID;
    newDoctor.YearsOfExperience = YearsOfExperience;

    doctors.push_back(newDoctor); // Add to vector
    cout << "Doctor added successfully.\n";
}

void DoctorManager::displayAll() {
    if (doctors.empty()) {
        cout << "No doctors available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   Doctor ID    | Years Of Experience         |\n";
    cout << "------------------------------------------------\n";
    for (const auto& doctor : doctors) {
        cout << "| " << setw(13) << doctor.DoctorID << " | "
             << setw(23) << doctor.YearsOfExperience << " |\n";
    }
    cout << "------------------------------------------------\n";
}

int DoctorManager::findIndexById(string DoctorID) {
    for (size_t i = 0; i < doctors.size(); i++) {
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

    doctors.erase(doctors.begin() + index); // Remove from vector
    cout << "Doctor deleted successfully.\n";
}

DoctorManager::DoctorManager() {
    // No initialization required for vector
}

string Doctor::GetDoctorID() {
    return DoctorID;
}

int Doctor::GetYearsOfExperience() {
    return YearsOfExperience;
}

void printMenu() {
    cout << "\n=== Doctor Management System ===\n";
    cout << "1. Add Doctor\n";
    cout << "2. Display All Doctors\n";
    cout << "3. Edit Doctor by ID\n";
    cout << "4. Delete Doctor by ID\n";
    cout << "5. Exit\n";
}
