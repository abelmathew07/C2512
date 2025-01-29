#ifndef DEPARTMENT_MAIN_H
#define DEPARTMENT_MAIN_H

#include <string>
#include<iostream>

#include "./../headers/department_file_repo.h"
#include "ui_common.h" 

class DepartmentController {
    public:
        std::string generateDepartmentNumber(int id);
        static void Read(std::string& name, std::string& description, std::string& head) {
            std::cout <<  "Enter Department Name:";
            getline(std::cin, name);
            std::cout <<  "Enter Department Head:";
            getline(std::cin, head);
            std::cout <<  "Enter Department Description:";
            getline(std::cin, description);
        }

        void Create();
        void ReadAll();
    };

void ManageDepartment();
int ReadDepartmentMenu();

#endif 