#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/types.h>
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

void client(int write_fd, int read_fd, const std::vector<Doctor>& doctors) {
        int size = doctors.size();
    write(write_fd, &size, sizeof(size));

    for (const auto& doc : doctors) {
        int experience = doc.getYearOfExperience();
        write(write_fd, &experience, sizeof(experience)); 
    }

    close(write_fd); 
    
    int result;
    read(read_fd, &result, sizeof(result));
    close(read_fd); 
    std::cout << "Sum of years of experience received from server: " << result << std::endl;
}

void server(int read_fd, int write_fd) {
       int size;
    read(read_fd, &size, sizeof(size));

    
    std::vector<Doctor> doctors;
    for (int i = 0; i < size; ++i) {
        int experience;
        read(read_fd, &experience, sizeof(experience));
        doctors.emplace_back("D" + std::to_string(i + 1), experience);     }

    
    int result = sum(doctors);

       write(write_fd, &result, sizeof(result));

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

    {
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

        std::vector<Doctor> exp;
    exp.emplace_back("D001", 1);
    exp.emplace_back("D002", 2);
    exp.emplace_back("D003", 3);
    exp.emplace_back("D004", 4);
    exp.emplace_back("D005", 5);
        

        client(pipe_client_to_server[1], pipe_server_to_client[0], exp); 
        wait(nullptr); 
    }
}
    return 0;
}
