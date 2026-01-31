// Process Tree Creation:

// PID 1 forks multiple child processes (first generation)

// Each child process immediately forks more child processes (second generation)

// Continue this pattern to create an exponentially growing process tree


#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <sys/resource.h>