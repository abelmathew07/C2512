#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define MAX_CONNS 5

using namespace std;

class Doctor {
private:
    string DoctorId;
    int YearsOfExperience;
public:
    Doctor(string id, int years) : DoctorId(id), YearsOfExperience(years) {}

    string getDoctorId() const { return DoctorId; }
    int getYearsOfExperience() const { return YearsOfExperience; }
};

void server(int port);
void serveClient(int& client_socket_fd);
void client(string server_ip, int port);
void sendDoctorData(int& client_socket_fd);

void server(int port) {
    int server_socket_fd;

    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_socket_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket_fd, MAX_CONNS) < 0) {
        perror("Listen failed");
        close(server_socket_fd);
        exit(EXIT_FAILURE);
    }

    int client_socket_fd;
    int addrlen = sizeof(address);
    if ((client_socket_fd = accept(server_socket_fd, (sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_socket_fd);
        exit(EXIT_FAILURE);
    }

    serveClient(client_socket_fd);

    close(server_socket_fd);
}

void serveClient(int& client_socket_fd) {
    char buffer[BUFFER_SIZE];
    int size;

    // Receive size of the array
    read(client_socket_fd, buffer, sizeof(int));
    memcpy(&size, buffer, sizeof(int));

    // Receive array of years of experience
    vector<int> years(size);
    read(client_socket_fd, buffer, size * sizeof(int));
    memcpy(years.data(), buffer, size * sizeof(int));

    // Display received data
    cout << "Server received years of experience: ";
    for (int year : years) {
        cout << year << " ";
    }
    cout << endl;

    // Calculate the total experience
    int totalExperience = 0;
    for (int year : years) {
        totalExperience += year;
    }

    // Send the total experience back to the client
    memcpy(buffer, &totalExperience, sizeof(int));
    write(client_socket_fd, buffer, sizeof(int));

    cout << "Server calculated total experience: " << totalExperience << endl;

    close(client_socket_fd);
}

void client(string server_ip, int port) {
    int client_socket_fd = 0;

    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    sendDoctorData(client_socket_fd);

    close(client_socket_fd);
}

void sendDoctorData(int& client_socket_fd) {
    char buffer[BUFFER_SIZE];

    // Create doctor data
    vector<Doctor> doctors = {
        Doctor("D001", 4),
        Doctor("D002", 7),
        Doctor("D003", 10),
        Doctor("D004", 2),
        Doctor("D005", 5)
    };

    int size = doctors.size();
    vector<int> years(size);
    for (int i = 0; i < size; ++i) {
        years[i] = doctors[i].getYearsOfExperience();
    }

    // Display data being sent
    cout << "Client sending years of experience: ";
    for (int year : years) {
        cout << year << " ";
    }
    cout << endl;

    // Send the size of the array
    memcpy(buffer, &size, sizeof(int));
    write(client_socket_fd, buffer, sizeof(int));

    // Send the array of years of experience
    memcpy(buffer, years.data(), size * sizeof(int));
    write(client_socket_fd, buffer, size * sizeof(int));

    // Receive the total experience from the server
    int totalExperience;
    read(client_socket_fd, buffer, sizeof(int));
    memcpy(&totalExperience, buffer, sizeof(int));

    cout << "Client received total experience from server: " << totalExperience << endl;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "Usage:\n\t./doctorApp server 8080\n\t./doctorApp client 127.0.0.1 8080" << endl;
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "server") == 0) {
        if (argc != 3) {
            cout << "Usage:\n\t./doctorApp server <port>" << endl;
            return EXIT_FAILURE;
        }

        cout << "Server listening on port " << argv[2] << endl;
        server(atoi(argv[2]));
    }

    if (strcmp(argv[1], "client") == 0) {
        if (argc != 4) {
            cout << "Usage:\n\t./doctorApp client <server_ip> <port>" << endl;
            return EXIT_FAILURE;
        }

        cout << "Client connecting to server at " << argv[2] << ":" << argv[3] << endl;
        client(argv[2], atoi(argv[3]));
    }

    return EXIT_SUCCESS;
}
