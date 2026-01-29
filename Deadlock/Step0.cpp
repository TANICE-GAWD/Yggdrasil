#include <iostream>
#include <unistd.h>
using namespace std;
#define INFINITE_FORK 1000
int main() {
    pid_t p_id = fork();
    
    

    return 0;
}

pid_t Spawning_forks(pid_t p_id){
    for (int i=0;i<INFINITE_FORK;i++){
        if(fork){
            Spawning_forks(p_id);
        }
        else if(!fork){
            Spawning_forks(p_id)
        }
    }
}