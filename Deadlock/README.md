I am planning to make the code Un-Dockerable by using Deadlock

Plan for now is to 
spawn 100s of Zombie processes which do nothing except waiting on each other.


SIGTERM can be dealt with putting massive interlocking tree processes on PID 1.

but Docker Timeout calls SIGKILL
i have to figure that out.
idk yet