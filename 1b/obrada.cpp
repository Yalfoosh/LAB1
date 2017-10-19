/* 
 * File:   obrada.cpp
 * Author: Miljenko Šuflaj
 */

#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <unistd.h>

#define N 6
#define TIMEOUT 100

int sig[5] = {SIGUSR1, SIGUSR2, SIGSYS, SIGURG, SIGINT};

int retPriority(int sig)
{
    switch(sig)
    {
        case SIGUSR1:
            return 1;
        case SIGUSR2:
            return 2;
        case SIGSYS:
            return 3;
        case SIGURG:
            return 4;
        case SIGINT:
            return 5;
        default:
            return 0;
    }
}

char space[] = "       ";

bool isWaiting[N];
int context[N];
int currPriority;

enum mode
{
    zabrani = 0,
    dozvoli = 1
};

using namespace std;

void prekidanje(mode m)
{
    for(int i = 0; i < 5; i++)
        (m == zabrani) ? sighold(sig[i]) : sigrelse(sig[i]);
}

void prekid(int sig)
{
        int i = retPriority(sig);
        prekidanje(zabrani);
        
        for(int j = 0; j < 5; ++j, printf("       "))
        {
            if(j == i)
                printf("X");
            else
                printf("-");
        }
        
        printf("\n");
}

int main ()
{
        for(int i = 0; i < 5; i++)
                sigset(sig[i], prekid);
 
        printf("Proces obrade prekida, PID = %d\n\n\n", getpid());
        printf("GP      P1      P2      P3      P4      P5\n__________________________________________\n");
        
        
        for(int i = 1; i < TIMEOUT; i++)
        {
            while(currPriority != 0)
                pause();
            
            printf("%2d       -       -       -       -       -\n", i);
            sleep(1);
        }
 
   printf ("Zavrsio osnovni program\n");
   return 0;
}