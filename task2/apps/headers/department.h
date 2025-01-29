#pragma once
#include <string>
#include <cstring>

class Department {
    private:
        int id;
        std::string name;
        std::string head;
        std::string description;
        
    public: // getters | setters 
        
        void SetId(int id) { this->id = id; }
        int GetId() const { return this->id; }
        void SetName(const std::string name) { this->name = name; }
        std::string GetName() const { return this->name; }
        void SetHead(const std::string head) { this->head = head; }
        std::string GetHead() const{ return this->head; }
        void SetDescription(const std::string description) { this->description = description; }
        std::string GetDescription() const{ return this->description; }
};

class FileDepartment {
    public: 
        int  id;
        char name[100];
        char head[100];
        char description[256];

        int GetId() const { return id; }
        void SetId(int newId) { id = newId; }
};

class DepartmentConverter { 
    public: 
        static FileDepartment ConvertDepartmentToFileDepartment(const Department& Department){
            FileDepartment fileDepartment;

            fileDepartment.id = Department.GetId();
            strcpy(fileDepartment.name, Department.GetName().c_str());
            strcpy(fileDepartment.head, Department.GetHead().c_str());
            strcpy(fileDepartment.description, Department.GetDescription().c_str());
            
            return fileDepartment;
        }

        static Department ConvertFileDepartmentToDepartment(const FileDepartment& fileDepartment){
           Department Department;

           Department.SetId(fileDepartment.id);
           Department.SetName(fileDepartment.name);
           Department.SetHead(fileDepartment.head);
           Department.SetDescription(fileDepartment.description);

           return Department; 
        }
};