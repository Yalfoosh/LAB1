/* 
 * File:   generator_prekida.cpp
 * Author: Miljenko Šuflaj
 */

#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int pid = 0;
int sigs[4] = {SIGUSR1, SIGUSR2, SIGSYS, SIGURG};       //Nadam se da SIGSYS i 
                                                                                      //SIGURG nisu previše potrebni
void end(int sig)
{
        kill(pid, SIGKILL);
        exit(0);
}

int main(int argc, char *argv[])
{
        srand(time(NULL));
        
        if(argc != 2)
        {
                printf("Unos argumenata nije valjan!\n\n");
                exit(1);
        }
        
        pid = atoi(argv[1]);
        sigset(SIGINT, end);
        
        for(int i;;)
        {
                for(i = 3 + (rand() % 2000) / 1000; i > 0; i--)     //Radim s tisućama jer jer rand() 
                        sleep(1);                                                   //loš za male modove.
            
                kill(pid, sigs[(rand() % 4000) / 1000]);
        }
        
        return 0;
}