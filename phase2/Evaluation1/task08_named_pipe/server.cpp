#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

using namespace std;

int findSum(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    const char* pipe1 = "pipe1";
    const char* pipe2 = "pipe2";
    int pipe_one_read_fd, pipe_two_write_fd;

    pipe_one_read_fd = open(pipe1, O_RDONLY);
    pipe_two_write_fd = open(pipe2, O_WRONLY);

    if (pipe_one_read_fd == -1) {
        perror("pipe1 open failure");
        return 1;
    }

    if (pipe_two_write_fd == -1) {
        perror("pipe2 open failure");
        return 1;
    }

    int numOfElements;
    read(pipe_one_read_fd, &numOfElements, sizeof(int));
    cout << "Server received number of doctors: " << numOfElements << endl;

    int experiences[numOfElements] = {0};
    read(pipe_one_read_fd, experiences, sizeof(int) * numOfElements);
    cout << "Server received years of experience: ";
    for (int exp : experiences) {
        cout << exp << "\t";
    }
    cout << endl;
    close(pipe_one_read_fd);

    int sum = findSum(experiences, numOfElements);
    write(pipe_two_write_fd, &sum, sizeof(int));
    cout << "Total years of experience sent from server: " << sum << endl;

    close(pipe_two_write_fd);
    return 0;
}
