#pragma once
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring> 

#include "Department.h"

class DepartmentFileRepo 
{
public:
   std::string repo_file_name = "Department.dat";

   void CreateFile_()
    {
        std::ofstream output(repo_file_name, std::ios::binary | std::ios::app);
        output.close();
    }

        int GetLastId_() {
        CreateFile_(); 

        std::fstream file(repo_file_name, std::ios::binary | std::ios::in);
        if (!file) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();

        if (fileSize == 0)
        {
            file.close();
            return 0; 
        }

        size_t lastRecordPos = fileSize - sizeof(FileDepartment);

        file.seekg(lastRecordPos, std::ios::beg);

        FileDepartment fileDepartment;
        file.read((char*)&fileDepartment, sizeof(FileDepartment));

        file.close();
        return fileDepartment.id;
    }

    void Create(Department& entity)
    {
        int lastnumber = GetLastId_();
        std::ofstream output(repo_file_name, std::ios::binary | std::ios::app);
        if (!output) {
            throw std::runtime_error("Failed to open file for writing.");
        }
        entity.SetId(lastnumber + 1);
        FileDepartment fileAccount = DepartmentConverter::ConvertDepartmentToFileDepartment(entity);
        fileAccount.id = lastnumber + 1; 
        output.write((char*)&fileAccount, sizeof(fileAccount));
        output.close();
    }

    std::vector<Department> SearchByName(const std::string& name) {
        CreateFile_(); // Ensure the file exists
        std::vector<Department> matchingDepartments;

        std::ifstream file(repo_file_name, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        FileDepartment fileDepartment;
        while (file.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            // Compare names using strcmp for C-style strings
            if (strcmp(fileDepartment.name, name.c_str()) == 0) {
                // Convert FileDepartment to Department and add to the vector
                matchingDepartments.push_back(DepartmentConverter::ConvertFileDepartmentToDepartment(fileDepartment));
            }
        }
        file.close();
        return matchingDepartments;
    }

    std::vector<Department> ReadAll() {
        CreateFile_(); // Ensure the file exists
        std::vector<Department> matchingDepartments;

        std::ifstream file(repo_file_name, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        FileDepartment fileDepartment;
        while (file.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            matchingDepartments.push_back(DepartmentConverter::ConvertFileDepartmentToDepartment(fileDepartment));
        }
        file.close();
        return matchingDepartments;
    }

    Department ReadByName(std::string name)
    {
        CreateFile_(); 

        std::ifstream input(repo_file_name, std::ios::binary);
        if (!input) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        FileDepartment fileDepartment;

        while (input.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            
            if (name == fileDepartment.name) {
                input.close();
                return DepartmentConverter::ConvertFileDepartmentToDepartment(fileDepartment);
            }
        }

        input.close();
        throw std::runtime_error("Department with given ID not found.");
    }
    
    

    Department ReadById(int id)
    {
        CreateFile_(); 

        std::ifstream input(repo_file_name, std::ios::binary);
        if (!input) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        FileDepartment fileDepartment;

        while (input.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            
            if (id == fileDepartment.id) {
                input.close();
                return DepartmentConverter::ConvertFileDepartmentToDepartment(fileDepartment);
            }
        }

        input.close();
        throw std::runtime_error("Department with given ID not found.");
    }
    


    void Update(Department& entity)
    {
        CreateFile_(); 

        std::fstream file(repo_file_name, std::ios::binary | std::ios::in | std::ios::out);
        if (!file) {
            throw std::runtime_error("Failed to open file for reading/writing.");
        }

        FileDepartment fileDepartment;
        bool updated = false;

        while (file.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            if (fileDepartment.name == entity.GetName()) {
                std::strncpy(fileDepartment.head, entity.GetHead().c_str(), sizeof(fileDepartment.head) - 1);
                fileDepartment.head[sizeof(fileDepartment.head) - 1] = '\0';  

                std::strncpy(fileDepartment.description, entity.GetDescription().c_str(), sizeof(fileDepartment.description) - 1);
                fileDepartment.description[sizeof(fileDepartment.description) - 1] = '\0';  

                file.seekp(static_cast<std::streamoff>(file.tellg()) - sizeof(FileDepartment));
                file.write((char*)&fileDepartment, sizeof(FileDepartment));
                updated = true;
                break;
            }
        }

        file.close();

        if (!updated) {
            throw std::runtime_error("Department with given name not found.");
        }
    }

    void DeleteByName(const std::string& name)
    {
        CreateFile_(); 

        std::fstream file(repo_file_name, std::ios::binary | std::ios::in | std::ios::out);
        if (!file) {
            throw std::runtime_error("Failed to open file for reading/writing.");
        }

        std::vector<FileDepartment> departments;
        FileDepartment fileDepartment;
        bool found = false;

        while (file.read((char*)&fileDepartment, sizeof(FileDepartment))) {
            if (fileDepartment.name == name) {
                found = true; 
            } else {
                departments.push_back(fileDepartment);  
            }
        }

        file.close();

        if (!found) {
            throw std::runtime_error("Department with the given name not found.");
        }

        std::ofstream output(repo_file_name, std::ios::binary | std::ios::trunc);
        if (!output) {
            throw std::runtime_error("Failed to open file for writing.");
        }

        for (const auto& dept : departments) {
            output.write((char*)&dept, sizeof(FileDepartment));
        }

        output.close();
    }
};
