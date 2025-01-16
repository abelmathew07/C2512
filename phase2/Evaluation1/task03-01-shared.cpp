#include <iostream>
#include <vector>
#include <cstring>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

class Doctor {
private:
    std::string doctorId;
    int yearOfExperience;
public:
    Doctor(std::string id, int experience) : doctorId(id), yearOfExperience(experience) {}
    int getYearOfExperience() const { return yearOfExperience; }
};

int sum(const std::vector<Doctor>& exp) {
    int res = 0;
    for (const auto& doc : exp) {
        res += doc.getYearOfExperience();
    }
    return res;
}

void client(int* shared_memory, int size) {
    // Write the vector size
    shared_memory[0] = size;

    // Write each doctor's experience to shared memory
    for (int i = 0; i < size; ++i) {
        shared_memory[i + 1] = i + 1; // Example years of experience (1, 2, ...)
    }

    // Wait for the server to calculate the result
    while (shared_memory[size + 1] == 0) {
        usleep(100); // Wait for the result
    }

    std::cout << "Sum of years of experience received from server: " << shared_memory[size + 1] << std::endl;
}

void server(int* shared_memory) {
    // Read the vector size
    int size = shared_memory[0];

    // Read the experiences into a vector
    std::vector<Doctor> doctors;
    for (int i = 0; i < size; ++i) {
        doctors.emplace_back("D" + std::to_string(i + 1), shared_memory[i + 1]);
    }

    // Calculate the sum of experience
    int result = sum(doctors);

    // Write the result back to shared memory
    shared_memory[size + 1] = result;
}

int main() {
    const int SHARED_MEMORY_SIZE = 1024;

    // Create shared memory
    int* shared_memory = static_cast<int*>(mmap(nullptr, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process - Server
        server(shared_memory);
        return 0;
    } else {
        // Parent process - Client
        std::vector<Doctor> doctors = {
            Doctor("D001", 1),
            Doctor("D002", 2),
            Doctor("D003", 3),
            Doctor("D004", 4),
            Doctor("D005", 5)
        };

        client(shared_memory, doctors.size());
        wait(nullptr); // Wait for the child process to finish

        // Clean up shared memory
        munmap(shared_memory, SHARED_MEMORY_SIZE);
    }

    return 0;
}
