#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
atomic_int *ULAZ;
atomic_int *BROJ;
int M;


void udi_u_kriticni_odsjecak(int i) {
    ULAZ[i] = 1;
    BROJ[i] = max(BROJ) + 1;
    ULAZ[i] = 0;

    for (int j = 0; j < ULAZ.length(); j++) {
        while (ULAZ[j] != 0) {

        }
        while (BROJ[j] != 0 && (BROJ[j] < BROJ[i] || (BROJ[j] == BROJ[i] && j < i))) {

        }
    }

}


void izadi_iz_kriticnog_odsjecka(i) {
    BROJ[i] = 0;
}

void *posaoDretve(void *arg) {
    int *BROJ = (int *)arg;
    for(int i = 0; i < M; i++) {
        udi_u_kriticni_odsjecak(BROJ);
        a++;
        izadi_iz_kriticnog_odsjecka(BROJ);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int broj_dretve = 0;
    pthread_t dretve[3];
    int broj_dretvi[3];

    M = atoi(argv[1]);
    printf("Vrijednost M: %d\n", m);

    for (int i = 0; i < N; i++) {
        broj_dretvi[i] = BROJ_dretve;
        pthread_create(&dretve[i], NULL, posaoDretve, &broj_dretvi[i]);
        broj_dretve++;
    }

    for (int i = 0; i < N; i++) {
        pthread_join(dretve[i], NULL);
    }
    printf("Roditelj: gotovo. Vrijednost BR: %ld\n", br);
 }

atomic_int max(int *array) {
    atomic_int max = 0;
    for (int i = 0; i < array.length(); i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}


