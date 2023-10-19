#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

char dohvati_sadrzaj(int p, int adress);
void zapisi_vrijednost(int p, int adress, char value);
int dohvati_fizicku_adresu(int p, int adress);
void resetiraj_lru();

short *tablica;
char *disk;
char *okvir;
int n;
int m;
int t;

int endv;


char dohvati_sadrzaj(int p, int adress) {

    int y = dohvati_fizicku_adresu(p, adress);
    return okvir[y];

}

void zapisi_vrijednost(int p, int adress, char value) {
    int y = dohvati_fizicku_adresu(p, adress);
    okvir[y] = value;
}

int dohvati_fizicku_adresu(int p, int adress) {


    int stranicaAddIndex = adress >> 6;
    int offset = adress & 0b111111;
    int bitP = tablica[p * 16 + stranicaAddIndex] & (1 << 5);

    int okvirIndex;
    
    if (bitP > 0 ) {

        int lruValue = t & 0b11111;
        tablica[p * 16 + stranicaAddIndex] &= ~(0b11111);
        tablica[p * 16 + stranicaAddIndex] |= lruValue;

        if (lruValue == 31) {
            resetiraj_lru();
        }

        okvirIndex = tablica[p * 16 + stranicaAddIndex] >> 6;
        return ((okvirIndex << 6) | offset);

    }
        
    cout << "        PROMASAJ!" << endl;
    int j;
    for(j = 0; j < m; j++){
        if (okvir[j * 64] == -1) {
            break;
        }
    }

    okvirIndex = j;
    int procesIndex;

    if (okvirIndex == m) {                                          // ako nema slobodnog okvira
            
        int stranicaDelIndex;
        int min = 32;

        for (int k = 0; k < 16 * n; k++) {                          // nalaženje okvira za zamjenu
            int bitP2 = (tablica[k] >> 5) & 1;
            if (bitP2 == 0) {
                continue;
            }
                if (k == 0) {
                okvirIndex = tablica[0] >> 6;
                stranicaDelIndex = 0;
                procesIndex = -1;
                break;
            }

            int lru = tablica[k] & 0b11111;
            if (lru < min) {
                okvirIndex = tablica[k] >> 6;
                stranicaDelIndex = k % 16;
                procesIndex = (int)(k / 16);
                min = lru;
            }
        }

        if (procesIndex == -1) {
            cout << "               Izbacujem okvir dijeljenog spremnika" << endl;
        }
        else {
            printf("               Izbacujem stranicu: 0x%x iz procesa %d", stranicaDelIndex, procesIndex);
            cout << endl; 
            cout << "               lru izbacene stranice: " << min << endl; 
        }

        for (int i = 0; i < 64; i++) {                                // kopiranje okvira koji izbacujemo na disk
            if (procesIndex == -1) {
                for (int j = 0; j < n; j++) {
                    disk[j * 1024 + i] = okvir[okvirIndex* 64 + i]; 
                }
                disk[n * 1024 + i] = okvir[okvirIndex * 64 + i];
            }
            else {
                disk[procesIndex * 1024 + stranicaDelIndex * 64 + i] = okvir[okvirIndex * 64 + i];
            }
        }

        if (procesIndex == -1) {                                         // brisanje bita prisutnosti izbačenog okvira
            for (int j = 0; j < n; j++) {
                tablica[j * 16] = tablica [j * 16] & ~(1 << 5);
            }
        }
        else {
            tablica[procesIndex * 16 + stranicaDelIndex] = tablica[procesIndex * 16 + stranicaDelIndex] & ~(1 << 5);
        }
    }


    for (int i = 0; i < 64; i++) {                                                      // kopiranje stranice sa diska u okvir
        okvir[okvirIndex * 64 + i] = disk[p * 1024 + stranicaAddIndex * 64 + i];
    }

    bitP = 0b1 << 5;
    int lruValue;

    if (stranicaAddIndex == 0) {                    // dodavanje indeksa okvira, bita prisutnosti i lru ako je zajednicki spremnik  
        for (int i = 0; i < n; i++) {

            lruValue = t & 0b11111;
            tablica[i * 16] &= 0b0;
            tablica[i * 16] |= lruValue;
            tablica[i * 16] |= bitP;
            tablica[i * 16] |= okvirIndex << 6;

        }
    }
    else {                                          // dodavanje indeksa okvira, bita prisutnosti i lru ako nije zajednicki spremnik
        tablica[p * 16 + stranicaAddIndex] |= bitP;
        lruValue = t & 0b11111;
        tablica[p * 16 + stranicaAddIndex] &= 0b0;
        tablica[p * 16 + stranicaAddIndex] |= lruValue;
        tablica[p * 16 + stranicaAddIndex] |= bitP;
        tablica[p * 16 + stranicaAddIndex] |= okvirIndex << 6;               
    }   

    printf("               dodijeljen okvir 0x%x", okvirIndex);
    cout << endl;
   

    if (lruValue == 31) {
        resetiraj_lru();
    }

    int fizAdresa =  (okvirIndex << 6) | offset;
    
    if (endv == 1) {
        printf("        fiz. adresa: 0x%x", fizAdresa);
        cout << endl;
        printf("        zapis tablice: 0x%x", tablica[p * 16 + stranicaAddIndex]);
        cout << endl;
        printf("        sadrzaj adrese: %d\n", okvir[fizAdresa]);
        cout << endl;
    }

    return fizAdresa;
}

void resetiraj_lru() {

    t = 0;

    for (int i = 0; i < n * 16; i++) {

        int lru = tablica[i] & 0b11111;

        tablica[i] &= ~(0b11111);

        if (lru == 31) {
            tablica[i] |= 1;
        }
    }
}


int main(int argc, char* argv[]) {

    srand(time(NULL));


    n = atoi(argv[1]);  
    m = atoi(argv[2]);


   /*
    n = 3;
    m = 2; 
    */

    /*
    *tablica = (short *) malloc(sizeof(short) * n * 16);  // 16 stranica maksimalno po procesu
    *disk = (char *) malloc(sizeof(char) * n * 1024 + sizeof(char) * 64);    //svaki proces - 1024 okteta maksimalno + dijeljeni spremnik - 64 okteta 
    *okvir = (char *) malloc(sizeof(char) * m * 64);     // svaki okvir - 64 okteta
    */
   short newtablica[n * 16];
   char newdisk[n * 1024 + 64];
   char newokvir[m * 64];

   tablica = newtablica;
   disk = newdisk;
   okvir = newokvir;

    for (int i = 0; i < m * 64; i++) {                         //inicijalizacija struktura
        okvir[i] = -1;
    }
    for (int i = 0; i < n * 1024 + 64; i++) {
        disk[i] = 0;
    }

    cout << disk[0] << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 16; j++) {
            tablica[i * 16 + j] = 0;
        }
        tablica[i * 16] = tablica[i * 16] | (1 << 5); 
    }

    for (int i = 0; i < 64; i++) {
        okvir[i] = 0;
    }

    t = 0;
    while (1) {
        for (int p = 0; p < n; p++) {

            endv = 0;
            cout << "proces: " << p << endl;
            cout << "        t:" << t << endl;

            if (p == 0) {
                for (int j = 0; j < n - 1; j++) {

                    unsigned short msg = (short) rand();
                    char gornji = msg >> 8;
                    char donji = (msg & 0b11111111);
                    int adress = 2 * j;
                    zapisi_vrijednost(p, adress, donji);
                    zapisi_vrijednost(p, adress + 1, gornji);  
                    cout << "        Poslao poruku: " << msg << endl;
                }
            }
            else {
                char gornji;
                char donji;
                donji = dohvati_sadrzaj(p, (p - 1) * 2);
                gornji = dohvati_sadrzaj(p, (p - 1) * 2 + 1);
                unsigned short msg = 0;
                msg |= gornji;
                msg = msg << 8;
                unsigned short donjiS = donji;
                donjiS = donjiS & 0b11111111;
                msg |= donjiS;
                cout << "        Primio poruku: " << msg << endl;
            }

            endv = 1;


            int adress = 0;
            while (adress <= 63) {
                adress = rand() & 0x3FE;
            }
        

            /// int adress = 0x1FE;

            char data = dohvati_sadrzaj(p, adress); 
            data++;
            zapisi_vrijednost(p, adress, data);
            t++;
            cout << "- - - - - - - - - - - - - -" << endl;
            sleep(1);

        }
    }



}

