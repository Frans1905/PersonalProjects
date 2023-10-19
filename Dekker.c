#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int id;
struct container *ad;

struct container {
    atomic_int *zastavica;
    atomic_int pravo;
    int m;
    int a;
}

void udi_u_kriticni_odsjecak(int i, int j) {
    zastavica[i] = 1;
    while (zastavica[i] != 0) {
        if (pravo == j) {
            zastavica[i] = 0
            while (pravo == j) {
                
            }
            zastavica[i] = 1;
        }
    }
}

void izadi_iz_kriticnog_odsjecka(int i, int j) {
    pravo = j;
    zastavica[i] = 0;
}

int main(int argc, char *argv[]) {
    id = smhget(IPC_PRIVATE, sizeof(container), 0600);

    if (id == -1) {
        printif("Nema zajednicke memorije!\n")
    }

    ad = (struct container*) shmat(id, NULL, 0);

    ad->a = 0;
    

    M = atoi(argv[1]);
    printf("Vrijednost M: %d\n", m);

    for (int i = 1; i <= 2; i++) {
        switch (fork()) {
            case 0:
                if (i == 1) {
                    proces(0);
                }
                else {
                    proces(1);
                }
                exit(0);
            case -1:
                printf("Proces se ne može stvoriti!\n");
        }
    }

    while (i--) {
        wait(NULL);
    }

    printf("Vrijednost A: %d\n", ad->a);

    brisi();
    return 0;

}

void brisi(int sig) {
    shmdt ((container*) ad);
    shmctl(id, IPC_RMID, NULL);
}