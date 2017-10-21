/* 
 * File:   obrada.cpp
 * Author: SOUL
 * 
 * Komentar: Treba kompajlirati s argumentom "-std=C++11"
 * Comment: You need to compile with "-std=C++11" argument.
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string>

#define N 6
#define TIMEOUT 100     //Ovo je do kojeg broja GP ide, slobodno mozete staviti i na 10.

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

int isWaiting[N];
int context[N];
int currPriority;

enum mode           //Samo da netrebam 2 funkcije za regulaciju prihavacanja prekida.
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

string constructXatY(string X, int Y)
{
    string toRet = "";
    X = " " + X;
    
    for(int i = 0; i < N; ++i, toRet += "      ")
        toRet += ((i == Y) ? X : " -");
    
    return toRet;
}

string constructXatY(int X, int Y)
{
    return constructXatY(to_string(X), Y);
}

void obrada(int sig)
{
    string toPrint = constructXatY ("P", sig);
    cout << toPrint << "\n";
    
    for(int i = 1; i < N; ++i)
    {
        sleep(1);
        
        toPrint = constructXatY(i, sig);
        cout << toPrint << "\n";
    }
    
    toPrint = constructXatY("K", sig);
    cout << toPrint << "\n";
}

void prekid(int sig)
{
        int i = retPriority(sig), x = 0;
        prekidanje(zabrani);
        
        string toPrint = constructXatY("X", i);
        cout << toPrint << "\n";
        
        ++isWaiting[i];
        
        do
        {
            x = 0;
            
            for(int j = currPriority + 1; j < N; ++j)
                if(isWaiting[j])
                    x = j;
            
            if(x)
            {
                --isWaiting[x];
                
                context[x] = currPriority;
                currPriority = x;
                
                prekidanje(dozvoli);
                obrada(x);
                prekidanje(zabrani);
                
                currPriority = context[x];
            }
        }
        while(x);
}

int main ()
{
        for(int i = 0; i < 5; i++)
                sigset(sig[i], prekid);
        
        currPriority = 0;
 
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