/* 
 * File:   prosti_brojevi.cpp
 * Author: SOUL
 */

#include <cstdlib>
#include<cstdio>
#include<csignal>
#include <cmath>
#include <unistd.h>
#include <sys/time.h>

#define wait_s 1
#define delay_s 1

typedef unsigned long long ull;
typedef itimerval it;

using namespace std;

ull currPrime = 3;
ull lastPrime = 2;
bool p = false;

it* setUp(double wait, double delay)
{
    it *t = (it*)malloc(sizeof(it));
    
    if(wait < 0.000001)     //Ne bi radilo da je value ili interval na 0s i 0us.
    {
        (*t).it_value.tv_sec = 0;
        (*t).it_value.tv_usec = 1;
    }
    else
    {
        (*t).it_value.tv_sec = (long)floor(wait);
        (*t).it_value.tv_usec = (long)((wait - floor(wait)) * 1000000);
    }
    
    if(delay < 0.000001)
    {
        (*t).it_interval.tv_sec = 0;
        (*t).it_interval.tv_usec = 1;
    }
    else
    {
        (*t).it_interval.tv_sec = (long)floor(delay);
        (*t).it_interval.tv_usec = (long)((delay - floor(delay)) * 1000000);
    }
    
    return t;
}

bool isPrime(ull x)
{
    if(x == 2 || x == 3)
        return true;
    else if(x > 3 && !(x % 2))
        return false;
    else if(x > 3) 
    {
        ull limit = (ull)ceil(sqrt(x));
        
        for(ull i = 3; i <= limit; i+= 2)
            if(x % i == 0)
                return false;
            
        return true;
    }
        
    return false;
}

void printLast()
{
    printf("Zadnji prosti broj bio je %llu.\n", lastPrime);
}

void regPrint(int sig)
{
    printLast();
}

void flip (int sig)
{
    p = !p;
}

void terminate(int sig)
{
    printLast(); 
    exit(0);
}

int main ()
{
    it* t = setUp(wait_s, delay_s);
    
    sigset(SIGALRM, regPrint);
    sigset(SIGINT, flip);
    sigset(SIGTERM, terminate);
    
    setitimer(ITIMER_REAL, t, NULL);
    
    for(ull i = lastPrime + 1, limit = (ull)0 - 2; i < limit; i+=2)
    {
        if(isPrime(i))
            lastPrime = i;
        
        while(p)
            pause();
    }
    
    return 0;
}