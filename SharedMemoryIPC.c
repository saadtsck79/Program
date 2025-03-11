#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>
#define SHM_SIZE 1024
void write_to_shared_memory(key_t key) {
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char * shmaddr = (char*)shmat(shmid, NULL, 0);
    if(shmaddr == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Write to shared memory...\n");
    strcpy(shmaddr, "Hello, Shared Memory!");
    if(shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
}
void read_from_shared_memory(key_t key) {
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char *shmaddr = (char*)shmat(shmid, NULL, 0);
    if(shmaddr == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Reading from shared memory: %s\n", shmaddr);
    if(shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
}
int main() {
    key_t key = ftok("shmfile", 65);
    pid_t pid = fork();
    if(pid == -1) {
        perror("fork");
        exit(1);
    }
    if(pid == 0) {
        read_from_shared_memory(key);
    } else {
        write_to_shared_memory(key);
        wait(NULL);
        int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
        if(shmid != -1) {
            if(shmctl(shmid, IPC_RMID, NULL) == -1) {
                perror("shmctl");
                exit(1);
            }
        }
    }
    return 0;
}