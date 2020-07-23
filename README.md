# Basic C programs related to OS and Device Driver concepts

### Operating System Concepts

1. [Building Static and Dynamic Libraries](/Operating_System/Build)
2. [Writing a Makefile](/Operating_System/Stack) (Example: Stack Operations)
3. [System vs. Library call](/Operating_System/copy_util...sys_vs_lib/)
4. fork() system call
    - [Demo](/Operating_System/fork/)
    - [Creating Parent-Child Processes](/Operating_System/fork2/)
5. [Inter-process Communication]
    - [pipe()](/Operating_System/pipe) system call: between related processes (parent-child)
    - mkfifo: between unrelated processes
        - demo(Operating_System/fifo_demo)
        - addition(Operating_System/fifo_add)
6. [Zombie and Orphan Processes](/Operating_System/zombie_orphan/)
7. [wait API's](/Operating_System/wait_API/)
    - [Relation between Parent-Child Processes](/Operating_System/wait_API/wait.c)
    - [Process status](/Operating_System/wait_API/wait_WIF.c)
    - [waitpid API](/Operating_System/wait_API/waitpid.c)
8. [exec()](/Operating_System/exec/) system call
    - [Demo](/Operating_System/exec/exec.c)
    - [Paren-Child Processes](/Operating_System/exec/exec2.c)
9. [shell](/Operating_System/shell/)
    - [Demo](/Operating_System/shell/simple.c)
    - [Creating own shell gui](/Operating_System/shell/shell.c)
10. [POSIX Threads](/Operating_System/pthread,race_cond/)
    - [Demo](/Operating_System/pthread,race_cond/demo.c)
    - [Creating a race condition](/Operating_System/pthread,race_cond/race_cond.c)
11. [Mutex](/Operating_System/mutex/)
    - [Futex](/Operating_System/mutex/futex/)
    - [Recursive Mutex](/Operating_System/mutex/rec_mutex/)
12. Semaphores
    - [Unnamed](/Operating_System/sem_unnamed/)
        - [Mutually Exclusive Semaphore](/Operating_System/sem_unnamed/me_sem/)
        - [Signaling Semaphore](/Operating_System/sem_unnamed/sig_sem/)
        - [Counting Semaphores](/Operating_System/sem_unnamed/count_sem/)
    - [Named](/Operating_System/sem_named/)
        - [Mutually Exclusive Semaphore](/Operating_System/sem_named/me_sem_unn/)
        - [Signaling Semaphores](/Operating_System/sem_named/sig_sem_unn/)
13. [Read-Write locks](/Operating_System/rwlocks/)
14. [Barriers](/Operating_System/barrier/)
    - [Demo](/Operating_System/barrier/barrier.c)
    - [without using barrier API's](/Operating_System/barrier/own_barr_func.c)
15. [Conditional Variables](/Operating_System/cond_var/)
16. [Shared Memory](/Operating_System/sh_mem/)
17. [Message Queues](/Operating_System/msg_q/)
18. [Sockets](/Operating_System/sockets/)
    - [Multiple Clients](/Operating_System/sockets/mult_client/)
19. [Lab Exam](/Operating_System/lab_exam/)
    - To find alphabet occurrences in a dictionary file by using suitable concepts from above
