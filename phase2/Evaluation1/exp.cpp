#include <iostream>
#include <unistd.h>
#include <vector>

int main() {
    int fd[2];
    pipe(fd); // Create pipe
    pid_t pid = fork();

    if (pid == 0) { // Child process
        close(fd[1]); // Close write end
        int size;
        read(fd[0], &size, sizeof(size)); // Read the size
        std::vector<int> vec(size);
        read(fd[0], vec.data(), size * sizeof(int)); // Read the vector data
        std::cout << "Child received vector: ";
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        close(fd[0]);
    } else { // Parent process
        close(fd[0]); // Close read end
        std::vector<int> vec = {10, 20, 30, 40, 50};
        int size = vec.size();
        write(fd[1], &size, sizeof(size)); // Write the size first
        write(fd[1], vec.data(), size * sizeof(int)); // Write the vector data
        close(fd[1]);
    }
    return 0;
}
