#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "./../headers/department_main.h"

UiCommon uiCommon;

int departmentId = 1;

std::string DepartmentController::generateDepartmentNumber(int id) {
    std::stringstream DepartmentNumber;
    DepartmentNumber << "DPT" << std::setw(4) << std::setfill('0') << id;  // Prefix "DPT" and pad ID with leading zeros
    return DepartmentNumber.str();
}

void DepartmentController::Create()
{
    uiCommon.TitleBar("Department Management > Create Department");

    std::string name;
    std::string description;
    std::string head;

    Read(name, description, head);
    Department newDepartment;
    newDepartment.SetName(name);
    newDepartment.SetDescription(description);
    newDepartment.SetHead(head);


    DepartmentFileRepo fileDepartment;
    fileDepartment.Create(newDepartment);

    std::cout << "Department created successfully with ID " << newDepartment.GetId() << std::endl;
    uiCommon.PressAnyKey(true);

    ManageDepartment();    
}

void DepartmentController::ReadAll() {
    uiCommon.TitleBar("Department Management > Display Departments");

    // Search departments by name
    DepartmentFileRepo departmentRepo;
    std::vector<Department> matchingDepartments = departmentRepo.ReadAll();

    std::cout << "Departments:\n" << std::endl;
    for (size_t i = 0; i < matchingDepartments.size(); ++i) {
        std::cout << i + 1 << ". " << matchingDepartments[i].GetName() << " (ID: " 
                  << matchingDepartments[i].GetId() << ", Head: " 
                  << matchingDepartments[i].GetHead() << ")" << std::endl;
                  ;
    }

    uiCommon.PressAnyKey(true);
    ManageDepartment();

}

int ReadDepartmentMenu()
{
    int choice;

    uiCommon.TitleBar("Department Management");

    std::stringstream soutput;
    soutput << "1 - Create Department" << std::endl;
    soutput << "2 - Display Departments" << std::endl;
    soutput << "99 - Exit" << std::endl;
    soutput << "Your choice:";
    choice = uiCommon.in.Int(soutput.str());

    uiCommon.Line('~');
    uiCommon.PressAnyKey(true);
    return choice;
}

void ManageDepartment() {
    DepartmentController controller;

    uiCommon.TitleBar("Department Management");

    int choice = ReadDepartmentMenu();

    do {
        switch (choice) {
            case 99: {
                return;
            } break;
            case 1: {
                controller.Create();
            } break;
            case 2: {
                controller.ReadAll();
            } break;
        }
    } while (99 != choice);
}