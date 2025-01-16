#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <climits>
#include <functional>

class Doctor {
private:
    std::string doctorId;
    int yearOfExperience;

public:
    Doctor(std::string id, int experience) : doctorId(id), yearOfExperience(experience) {}
    int getYearOfExperience() const { return yearOfExperience; }
};

template <class T>
T accumulate(const std::vector<Doctor>& doctors, std::function<T(T, Doctor)> elementOperation, T init) {
    T result = init;
    for (const auto& doctor : doctors) {
        result = elementOperation(result, doctor);
    }
    return result;
}

void client(int write_fd, int read_fd, const std::vector<Doctor>& doctors) {
    
    int size = doctors.size();
    write(write_fd, &size, sizeof(size)); 

    for (const auto& doc : doctors) {
        int experience = doc.getYearOfExperience();
        write(write_fd, &experience, sizeof(experience)); 
    }

    close(write_fd); 

   
    int sumResult, minResult,mulResult;
    read(read_fd, &sumResult, sizeof(sumResult));
    read(read_fd, &minResult, sizeof(minResult));
    read(read_fd, &mulResult, sizeof(mulResult));
    close(read_fd); 

    std::cout << "Sum of years of experience received from server: " << sumResult << std::endl;
    std::cout << "Minimum years of experience received from server: " << minResult << std::endl;
    std::cout << "Multiplied years of experience received from server: " << mulResult << std::endl;
}

void server(int read_fd, int write_fd) {
    
    int size;
    read(read_fd, &size, sizeof(size));


    std::vector<Doctor> doctors;
    for (int i = 0; i < size; ++i) {
        int experience;
        read(read_fd, &experience, sizeof(experience));
        doctors.emplace_back("D" + std::to_string(i + 1), experience); // Create Doctor objects
    }

    
    auto sumOp = [](int sum, Doctor doctor) {
        return sum + doctor.getYearOfExperience();
    };
    int sumResult = accumulate<int>(doctors, sumOp, 0);

    auto minOp = [](int min, Doctor doctor) {
        return doctor.getYearOfExperience() < min ? doctor.getYearOfExperience() : min;
    };
    int minResult = accumulate<int>(doctors, minOp, INT_MAX);
     auto mulOp = [](int product , Doctor doctor) {
        return product * doctor.getYearOfExperience();
    };
    int mulResult = accumulate<int>(doctors, mulOp, 1);
    write(write_fd, &sumResult, sizeof(sumResult));
    write(write_fd, &minResult, sizeof(minResult));
    write(write_fd, &mulResult, sizeof(mulResult));
    close(read_fd); 
    close(write_fd); 
}

int main() {
    int pipe_client_to_server[2]; 
    int pipe_server_to_client[2]; 

    if (pipe(pipe_client_to_server) == -1 || pipe(pipe_server_to_client) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
       
        close(pipe_client_to_server[1]); 
        close(pipe_server_to_client[0]); 
        server(pipe_client_to_server[0], pipe_server_to_client[1]); 
        return 0;
    } else {
       
        close(pipe_client_to_server[0]); 
        close(pipe_server_to_client[1]);

        std::vector<Doctor> doctors = {
            Doctor("D001", 1),
            Doctor("D002", 2),
            Doctor("D003", 3),
            Doctor("D004", 4),
            Doctor("D005", 5)
        };

        client(pipe_client_to_server[1], pipe_server_to_client[0], doctors); // Send data and read results
        wait(nullptr); 
    }

    return 0;
}
