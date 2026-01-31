// signal blockers inside PID1 controller
// with notes for myself
#include <signal.h>
void blockSignals(){
    sigset_t sig_set; //imma use ts to keep all my blocker signals
    sigemptyset(&sig_set);

    sigaddset(&sig_set,SIGTERM); //used ts to add the SIGTERM into the set

    pthread_sigmask(SIG_BLOCK, &sig_set, NULL);
    // above line blocked ts sig

    

}