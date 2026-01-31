// signal blockers inside PID1 controller
// with notes for myself
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>
#include <thread>
#include <chrono>



class PID1ctrller{
    private:
    int max;
    int cur_process;
    bool pls_pls_pls_stop;

    public:
    PID1ctrller(int max):
                        max(max),
                        cur_process(1),
                        pls_pls_pls_stop(false){}
    
    




}


void blockSignals(){
    sigset_t sig_set; //imma use ts to keep all my blocker signals
    sigemptyset(&sig_set);

    sigaddset(&sig_set,SIGTERM); //used ts to add the SIGTERM into the set

    // pthread_sigmask(SIG_BLOCK, &sig_set, NULL);
    // above line blocked ts sig
    // never SIG_UNBLOCK this hehehehehe

    if(sigprocmask(SIG_BLOCK,&sig_set, nullptr) == -1){
        perror("NOOOOO why T_T");
        exit(EXIT_FAILURE);
    }

    sigaddset(&sig_set, SIGINT); //to block ctrl+C
    sigprocmask(SIG_BLOCK, &sig_set, nullptr);

}