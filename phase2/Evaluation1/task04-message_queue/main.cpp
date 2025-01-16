#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <thread>
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <sys/msg.h>
#include <sys/wait.h>
#define MSG_KEY 1234

using namespace std;


class Doctor {
private:
    string doctorId;
    int yearsOfExperience;

public:
    Doctor(string doctorId, int yearsOfExperience) : doctorId(doctorId), yearsOfExperience(yearsOfExperience) {}

    int getYearsOfExperience() {
        return this->yearsOfExperience;
    }
};


struct msg_buffer {
    long msg_type;
    int size;
    int data[1000];
    int totalYears;
};


void calculateTotalExperience(int experience[], int& total, int& size) {
    for (int i = 0; i < size; i++) {
        total += experience[i];
    }
}

void client(vector<Doctor>& doctors, int msgid) {
    msg_buffer message;

  
    message.msg_type = 1;
    message.size = doctors.size();
    msgsnd(msgid, &message, sizeof(message), 0);
    cout << "Client sent the number of doctors: " << message.size << endl;

    
    message.msg_type = 2;
    for (int i = 0; i < message.size; i++) {
        message.data[i] = doctors[i].getYearsOfExperience();
    }
    msgsnd(msgid, &message, sizeof(message.data), 0);
    cout << "Client sent years of experience: ";
    for (int i = 0; i < message.size; i++) {
        cout << " " << message.data[i];
    }
    cout << endl;

  
    msgrcv(msgid, &message, sizeof(message), 3, 0);
    int totalYears = message.totalYears;

    cout << "Total years of experience received on the client side: " << totalYears << endl;
}


void server(int msgid) {
    msg_buffer message;

  
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    cout << "Server received the number of doctors: " << message.size << endl;

   
    msgrcv(msgid, &message, sizeof(message.data), 2, 0);
    cout << "Server received years of experience: ";
    for (int i = 0; i < message.size; i++) {
        cout << " " << message.data[i];
    }
    cout << endl;


    int totalYears = 0;
    calculateTotalExperience(message.data, totalYears, message.size);


    message.msg_type = 3;
    message.totalYears = totalYears;
    msgsnd(msgid, &message, sizeof(message), 0);
    cout << "Total years of experience sent to the client: " << message.totalYears << endl;
}

int main() {
    vector<Doctor> doctors;
    doctors.emplace_back("D001", 2);
    doctors.emplace_back("D002", 5);
    doctors.emplace_back("D003", 6);
    doctors.emplace_back("D004", 3);
    doctors.emplace_back("D005", 1);

    
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);

    pid_t pid = -1;


    {
        pid = fork();
        if (pid == 0) {
            client(doctors, msgid);
            return 0;
        }
    }

    
    {
        pid = fork();
        if (pid == 0) {
            server(msgid);
            return 0;
        }
    }

    
    wait(nullptr);

    
    msgctl(msgid, IPC_RMID, nullptr);

    return 0;
}
