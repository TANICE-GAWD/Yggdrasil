#include <iostream>
#include <unistd.h>
using namespace std;
#define INFINITE_FORK 10
int main() {
    pid_t p_id = fork();
    int gen = 0;
    int spawn_children = 0;
    Spawning_forks(p_id, gen, spawn_children);

    return 0;
}

pid_t Spawning_forks(pid_t p_id, int gen, int spawn_children){
    // for (int i=0;i<INFINITE_FORK;i++){
    //     pid_t p_id = fork();
    //     pid_t parent = p_id;
    //     int parent_gen = gen;
        // if(p_id){
        //     Spawning_forks(p_id, gen);
        // }
        // else if(!p_id){
        //     Spawning_forks(p_id, gen);
        // }
    // }
    for (int i=0;i<INFINITE_FORK;i++){
        if(spawn_children) return;
        else{
            spawn_children = 1;
            p_id = fork();
            if(p_id){
                Spawning_forks(p_id, gen, spawn_children);
            }
            else if(!p_id){
                Spawning_forks(p_id, gen, spawn_children);
            }
            
        }
    }
}