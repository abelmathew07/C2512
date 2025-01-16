#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

class Doctor {
private:
    string doctorId;
    int yearsOfExperience;

public:
    Doctor(string doctorId, int yearsOfExperience) {
        this->doctorId = doctorId;
        this->yearsOfExperience = yearsOfExperience;
    }

    int getExperience() { return this->yearsOfExperience; }
};

int main() {
    vector<Doctor> doctors;
    doctors.emplace_back("D001", 5);
    doctors.emplace_back("D002", 8);
    doctors.emplace_back("D003", 3);
    doctors.emplace_back("D004", 10);
    doctors.emplace_back("D005", 2);

    int experiences[doctors.size()] = {0};

    for (int i = 0; i < doctors.size(); i++) {
        experiences[i] = doctors[i].getExperience();
    }

    int numOfElements = doctors.size();

    const char* pipe1 = "pipe1";
    const char* pipe2 = "pipe2";
    int pipe_two_read_fd, pipe_one_write_fd;

    pipe_one_write_fd = open(pipe1, O_WRONLY);
    pipe_two_read_fd = open(pipe2, O_RDONLY);

    if (pipe_one_write_fd == -1) {
        perror("pipe1 open failure at client");
        return 1;
    }
    if (pipe_two_read_fd == -1) {
        perror("pipe2 open failure at client");
        return 1;
    }

    write(pipe_one_write_fd, &numOfElements, sizeof(int));
    cout << "Client sent number of doctors: " << numOfElements << endl;

    write(pipe_one_write_fd, experiences, sizeof(experiences));
    cout << "Client sent years of experience: ";
    for (int exp : experiences) {
        cout << exp << "\t";
    }
    cout << endl;
    close(pipe_one_write_fd);

    sleep(1);

    int sum;
    read(pipe_two_read_fd, &sum, sizeof(int));
    cout << "Total years of experience received from server: " << sum << endl;

    close(pipe_two_read_fd);

    return 0;
}
