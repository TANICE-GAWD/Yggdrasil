// signal blockers inside PID1 controller
// with notes for myself
#include <signal.h>
#include <cstdlib>
#include <cstdio>
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

}