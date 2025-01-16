#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>

#define SHM_KEY 1234


class Doctor {
public:
    std::string doctorId;
    int patientsTreated;

    Doctor(std::string id, int patients) : doctorId(id), patientsTreated(patients) {}

    std::string getDoctorId() const { return doctorId; }
    int getPatientsTreated() const { return patientsTreated; }
};

struct SharedMemory {
    int patients[5];
    int totalPatients;
    bool dataReady;       
    bool serverDone;      
};

void client(int& shmid) { 
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);

    std::vector<Doctor> doctors = {
        Doctor("D001", 4),
        Doctor("D002", 5),
        Doctor("D003", 6),
        Doctor("D004", 15),
        Doctor("D005", 1)
    };

    
    for (int i = 0; i < 5; ++i) {
        sharedMem->patients[i] = doctors[i].getPatientsTreated();
    }

    std::cout << "Client sent patients treated: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->patients[i] << " ";
    }
    std::cout << std::endl;

    
    sharedMem->dataReady = true;

    
    while (!sharedMem->serverDone) {
        sleep(1);  
    }

    
    std::cout << "Client received total patients treated from server: " << sharedMem->totalPatients << std::endl;

    shmdt(sharedMem);
}

void server(int& shmid) { 
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);

    
    while (!sharedMem->dataReady) {
        sleep(1);  
    }

    
    std::cout << "Server received patients treated: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->patients[i] << " ";
    }
    std::cout << std::endl;

    
    sharedMem->totalPatients = 0;
    for (int i = 0; i < 5; ++i) {
        sharedMem->totalPatients += sharedMem->patients[i];
    }

    std::cout << "Server calculated total patients treated: " << sharedMem->totalPatients << std::endl;

    
    sharedMem->serverDone = true;

    shmdt(sharedMem);
}

int main() {
   
    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666 | IPC_CREAT);

    if (shmid == -1) {
        std::cerr << "Shared memory allocation failed!" << std::endl;
        return 1;
    }


    {
        pid_t pid = fork();
        if (pid == 0) {
            server(shmid);
            shmctl(shmid, IPC_RMID, nullptr);  
            return 0;
        }
    }

    
    sleep(1);

    
    {
        pid_t pid = fork();
        if (pid == 0) {
            client(shmid);
            return 0;
        }
    }

   
    wait(nullptr);
    wait(nullptr);

    return 0;
}
