#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <string>
#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t m;
pthread_cond_t lijeviRed;
pthread_cond_t desniRed;
pthread_cond_t camacCond;

queue<string> lijevaObala;
queue<string> desnaObala;
queue<string> camacQ;
int ukrcaniKanibali;
int ukrcaniMisionari;
int obala;

void *camac(void *p);
void *kanibal(void *p);
void *misionar(void *p);

void print_state();
void print_queue(queue<string> q);
queue<string> remove_element(string id, queue<string> q);

void *camac(void *p)
{

    while (1)
    {

        pthread_mutex_lock(&m);

        if (obala == 1)
        {
            pthread_cond_broadcast(&desniRed);
        }
        else
        {
            pthread_cond_broadcast(&lijeviRed);
        }
        while (ukrcaniKanibali + ukrcaniMisionari < 3)
        {
            pthread_cond_wait(&camacCond, &m);
        }
        cout << "C: tri putnika ukrcana, polazim za jednu sekundu" << endl;
        print_state();
        pthread_mutex_unlock(&m);

        sleep(1);

        pthread_mutex_lock(&m);
        int temp = obala;
        if (temp == 0) {
            obala = 2;
        }
        else {
            obala = 3;
        }
        if (temp == 1)
        {
            cout << "C: prevozim s desne na lijevu obalu: ";
        }
        else
        {
            cout << "C: prevozim s lijeve na desnu obalu: ";
        }
        print_queue(camacQ);
        cout << endl;
        pthread_mutex_unlock(&m);

        sleep(2);

        pthread_mutex_lock(&m);
        if (temp == 1)
        {
            cout << "C: preveo s desne na lijevu obalu: ";
            print_queue(camacQ);
            cout << endl;
            obala = 0;
            ukrcaniKanibali = 0;
            ukrcaniMisionari = 0;
            while (!camacQ.empty())
            {
                camacQ.pop();
            }
            cout << "C: prazan na lijevoj obali" << endl;
            print_state();
        }
        else
        {
            cout << "C: preveo s lijeve na desnu obalu: ";
            print_queue(camacQ);
            cout << endl;
            obala = 1;
            ukrcaniKanibali = 0;
            ukrcaniMisionari = 0;
            while (!camacQ.empty())
            {
                camacQ.pop();
            }
            cout << "C: prazan na desnoj obali" << endl;
            print_state();
        }
        pthread_mutex_unlock(&m);
    }
}

void *kanibal(void *p)
{

    pthread_mutex_lock(&m);

    int kanibalNum = *((int *)p);
    int i = rand() % 2;
    string id = "K" + to_string(kanibalNum);
    if (i == 0)
    {
        lijevaObala.push(id);
        cout << id << ": došao na lijevu obalu " << endl;
    }
    else
    {
        desnaObala.push(id);
        cout << id << ": došao na desnu obalu " << endl;
    }

    print_state();

    while ((ukrcaniKanibali == ukrcaniMisionari && ukrcaniKanibali != 0) ||
           obala != i || ukrcaniKanibali + ukrcaniMisionari >= 7)
    {
        if (i == 0)
        {
            pthread_cond_wait(&lijeviRed, &m);
        }
        else
        {
            pthread_cond_wait(&desniRed, &m);
        }
    }

    ukrcaniKanibali++;
    camacQ.push(id);

    if (i == 0)
    {
        lijevaObala = remove_element(id, lijevaObala);
    }
    else
    {
        desnaObala = remove_element(id, desnaObala);
    }

    cout << id << " : ušao u čamac " << endl;
    print_state();
    pthread_cond_signal(&camacCond);

    pthread_mutex_unlock(&m);

    pthread_mutex_lock(&m);

    if (i == 0)
    {
        pthread_cond_broadcast(&lijeviRed);
    }
    else
    {
        pthread_cond_broadcast(&desniRed);
    }

    pthread_mutex_unlock(&m);

    return NULL;
}

void *misionar(void *p)
{

    pthread_mutex_lock(&m);

    int misionarNum = *((int *)p);
    int i = rand() % 2;
    string id = "M" + to_string(misionarNum);
    if (i == 0)
    {
        cout << id << ": došao na lijevu obalu" << endl;
        lijevaObala.push(id);
    }
    else
    {
        cout << id << ": došao na desnu obalu" << endl;
        desnaObala.push(id);
    }

    print_state();

    while ((ukrcaniKanibali > ukrcaniMisionari && ukrcaniMisionari > 0) || (ukrcaniKanibali > 1 && ukrcaniMisionari == 0) || 
            obala != i || ukrcaniKanibali + ukrcaniMisionari >= 7)
    {
        if (i == 0)
        {
            pthread_cond_wait(&lijeviRed, &m);
        }
        else
        {
            pthread_cond_wait(&desniRed, &m);
        }
    }

    ukrcaniMisionari++;
    camacQ.push(id);

    if (i == 0)
    {
        lijevaObala = remove_element(id, lijevaObala);
    }
    else
    {
        desnaObala = remove_element(id, desnaObala);
    }

    cout << id << ": ušao u čamac" << endl;
    print_state();
    pthread_cond_signal(&camacCond);

    pthread_mutex_unlock(&m);

    pthread_mutex_lock(&m);
    if (i == 0)
    {
        pthread_cond_broadcast(&lijeviRed);
    }
    else
    {
        pthread_cond_broadcast(&desniRed);
    }
    pthread_mutex_unlock(&m);

    return NULL;
}

void print_queue(queue<string> q)
{
    queue<string> temp = q;

    if (!temp.empty())
    {
        cout << temp.front();
        temp.pop();
    }

    while (!temp.empty())
    {
        cout << " ";
        cout << temp.front();
        temp.pop();
    }

    return;
}

void print_state()
{
    string obalastr;
    if (obala == 0 || obala == 2)
    {
        obalastr = "L";
    }
    else if (obala == 1 || obala == 3)
    {
        obalastr = "D";
    }

    cout << "C[" << obalastr << "]=";
    cout << "{";
    if (!camacQ.empty())
    {
        print_queue(camacQ);
    }
    cout << "} ";

    cout << "LO={";
    if (!lijevaObala.empty())
    {
        print_queue(lijevaObala);
    }
    cout << "} ";

    cout << "DO={";
    if (!desnaObala.empty())
    {
        print_queue(desnaObala);
    }
    cout << "}" << endl;
    cout << endl;

    return;
}

queue<string> remove_element(string id, queue<string> q)
{
    queue<string> temp = q;
    queue<string> newq;
    string el;
    while (!temp.empty())
    {
        el = temp.front();
        temp.pop();
        if (el != id)
        {
            newq.push(el);
        }
    }
    return newq;
}

int main()
{

    srand(time(NULL));

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&lijeviRed, NULL);
    pthread_cond_init(&desniRed, NULL);
    pthread_cond_init(&camacCond, NULL);

    obala = 1;

    pthread_t camacD;
    pthread_create(&camacD, NULL, camac, NULL);

    int i = 0;
    int j = 0;
    while (1)
    {
        sleep(1);
        pthread_t kanibal1;
        pthread_create(&kanibal1, NULL, kanibal, &i);
        i++;
        sleep(1);
        pthread_t kanibal2;
        pthread_create(&kanibal2, NULL, kanibal, &i);
        i++;
        pthread_t misionar1;
        pthread_create(&misionar1, NULL, misionar, &j);
        j++;
    }

    return 0;
}