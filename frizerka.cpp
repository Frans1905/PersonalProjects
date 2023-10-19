#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void update_queue();
void frizerka();
void klijent(int num);

sem_t *sem;
sem_t *fsem;
sem_t *csem;
sem_t *qsem;
sem_t *osem;

struct pod {
    int open;
    int queue[5];
    int total_clients;
};

int id;

struct pod *data;


void frizerka() {

    printf("Frizerka: Otvaram salon\n");
    printf("Postavljam znak: OTVORENO\n");

    sem_wait(csem);
    sem_wait(osem);
    while(data->open == 1 || data->total_clients > 0) {

        if(data->total_clients == 0) {
            printf("Frizerka: Spavam dok klijenti ne dođu\n");
        }

        sem_post(osem);
        sem_post(csem);

        sem_wait(sem);
 
        sem_wait(osem);
        if (data->open == 0) {
            break;
        }
        sem_post(osem);

        sem_wait(qsem);
        int client_num = data->queue[0];
        sem_post(qsem);

        printf("Frizerka: Idem raditi na klijentu %d\n", client_num);
        sem_post(fsem);

        sleep(3);
        printf("Frizerka: Klijent %d gotov\n", client_num);

        sem_wait(csem);
        sem_wait(osem);

    }

    sem_post(osem);
    sem_post(csem);
    printf("Frizerka: Postavljam znak ZATVORENO\n");
    printf("Frizerka: Zatvaram salon\n");
    return;

}

void klijent(int num) {


    sem_wait(osem);
    if (data->open == 0) {
        return;
    }
    if (data->open == 1) {
        printf("    Klijent(%d): Želim na frizuru\n", num);
    }
    sem_post(osem);

    sem_wait(osem);
    if (data->open == 1 && data->total_clients < 5) {

        sem_post(osem);

        sem_wait(csem);
        sem_wait(qsem);
        (data->total_clients)++;
        data->queue[data->total_clients - 1] = num;
        printf("    Klijent(%d): Ulazim u čekaonicu(%d)\n", num, data->total_clients);
        sem_post(csem);
        sem_post(qsem);

        sem_post(sem);
        sem_wait(fsem);

        printf("    Klijent(%d): Frizerka mi radi frizuru\n", num);

        sem_wait(qsem);
        update_queue();
        sem_post(qsem);

        sem_wait(csem);
        (data->total_clients)--;
        sem_post(csem);
        return;
    }
    else {
        sem_post(osem);
        sem_wait(osem);
        if (data->open == 1) {
            printf("    Klijent(%d): Nema mjesta u čekaoni, vratit ću se sutra\n", num);
        }
        sem_post(osem);
        return;
    }

}


void update_queue() {
    for (int i = 0; i < 4; i++) {
        data->queue[i] = data->queue[i + 1];
    }
}

int main() {
    srand(time(NULL));
    id = shmget(IPC_PRIVATE, sizeof(sem_t) * 5 + sizeof(data->open) + sizeof(data->queue) + sizeof(data->total_clients), 0600);
    data = (struct pod *) shmat(id, NULL, 0);
    sem = (sem_t *)((char *)data + sizeof(pod));
    fsem = (sem_t *)((char *)sem + sizeof(sem_t));
    csem = (sem_t *)((char *)fsem + sizeof(sem_t));
    qsem = (sem_t *)((char *)csem + sizeof(sem_t));
    osem = (sem_t *)((char *)qsem + sizeof(sem_t));
    shmctl (id, IPC_RMID, NULL); //moze odmah ovdje, nakon shmat, ili na kraju nakon shmdt jer IPC_RMID oznacava da segment treba izbrisati nakon sto se zadnji proces odijeli od tog segmenta (detach)

    sem_init (sem, 1, 0); //početna vrijednost = 5, 1=>za procese
    sem_init (fsem, 1, 0);
    sem_init (csem, 1, 1);
    sem_init (qsem, 1, 1);
    sem_init (osem, 1, 1);
    data->open = 1;
    for (int i = 0; i < 5; i++) {
        data->queue[i] = 0;
    }
    data->total_clients = 0;

    int customer_count = 0;
    switch(fork()) {
        case 0:
            frizerka();
            exit(0);
        case -1:
            printf("Proces se ne može stvoriti!");
        default:
            if (fork() == 0) {
                while(data->open == 1) {
                    if (customer_count > 4) {
                        int client_wait = rand() % 5 + 3;
                        sleep(client_wait);
                    }
                    switch(fork()) {
                        case 0:
                            klijent(customer_count + 1);
                            exit(0);
                        case -1:
                            printf("Proces se ne može stvoriti!");
                        default:
                            customer_count++;
                }
            }
            }
    }

    sleep(20);
    sem_wait(osem);
    data->open = 0;
    sem_post(osem);
    sem_post(sem);
    for(int i = 0; i < 2 + customer_count; i++) {
        wait(NULL);
    }

    sem_destroy(sem);
    sem_destroy(fsem);
    sem_destroy(csem);
    sem_destroy(qsem);
    sem_destroy(osem);
    shmdt(data);

    return 0;
}