#include <iostream>
#include <unistd.h>
using namespace std;
#define INFINITE_FORK 10
int main() {
    pid_t p_id = fork();
    int gen = 0;
    Spawning_forks(gen);

    return 0;
}

void Spawning_forks(int gen){
    // // for (int i=0;i<INFINITE_FORK;i++){
    // //     pid_t p_id = fork();
    // //     pid_t parent = p_id;
    // //     int parent_gen = gen;
    //     // if(p_id){
    //     //     Spawning_forks(p_id, gen);
    //     // }
    //     // else if(!p_id){
    //     //     Spawning_forks(p_id, gen);
    //     // }
    // // }
    //     if(spawn_children) return;
    //     else{
    //         spawn_children = 1;
    //         p_id = fork();
    //         int parent_gen = gen;
    //         if(p_id == 0){
    //             gen = parent_gen + 1;
    //             Spawning_forks(p_id, gen, spawn_children);
    //         }
            
    // }

    for(int i=0;i<gen && )


}