# MINITALK

The purpose of this project is to code a small data exchange using UNIX signals

# MINITALTK NOTES

INTERPROCESS COMMUNICATION

ipc systems :
posix: uses shared memory method
mach: uses message passing
windows xp: uses message passing using local procedural calls

communication in client/sever architecture
pipe; socket; remote procedural calls (RPCs)

processes can be of two types:

- independent process which is not affected by other processes
- co-operating process which can be affected by others

There are many situations where co-operating one can be more efficient for increasing computational speed,
convenience and modularity.
Interprocess communication(IPC) is a mechanism that allows processes to communicate with each other
by synchronizing their actions.
communication == co-operation

methods:
- SHARED MEMORY
process1 generates info about computation or resources being used and keep it as a record in a shared memory.
process2 will check in shared memory and take note of generated info by process1 and act accordingly.
    two processes : producer and consumer
    producer produces some elements and consumer utilizes those elements. both share a common memory location (buffer)
    where the producer produce that element and from which consumer consumes it if needed.
    two problems:
    1. unbounded buffer problem-> producer can keep producing elements and there is no limit on buffer_size
    2. bounded buffer problem-> producer can up to a certain number of items
       before it starts waiting for consumer to consume it.
    first producer and consumer will share common memory then producer start producing items.
    if total produced items are equal to buffer_size, producer will wait to get it consumed by consumer.
    at the same time consumer will check elements' availability.
    if no element is available consumer waits; if elements are available consumer consume them.

- message passing
start exchanging mex using basic primitives
send(mex, destination) receive(mex, host)

message size can be fixed or unfixed.
communication links: a link has a capacity of determining the number of mex that can reside in it,
for which every link has a queue associated with it.
- in zero capacity, sender waits until the receiver informs back that it has received the mex.
- in non-zero capacity, process doesn't know if the message has been received or not after send operation.

- Direct communication link is implemented when processes use a specific process identifier for the communication
- In-direct communication is done via a shared port which consists of a queue of mex,
sender keeps mex in mailbox and receiver pick it up.

Processes work in same computer and not; processes may and may not be blocked while sending mex.
- Blocking is considered synchronous and blocking send means the sender will be blocked
until mex is received by receiver.
in the other hand blocking receive has the receiver blocked til mex is available.
- Non blocking is considered asynchronous and non-blocking send means sender sends and continue.
non-blocking receiver has the receiver receive a valid mex or NULL.

-Direct mex passing: send(p1, message) receive(p2, message)
process that communicate must explicitly name the recipient or sender of communication.
here link is established automatically.
if name of one process changes, this method won't work.
-Indirect mex passing: send(A, message) receiver(A, message)
process use mailboxes (ports) for send and receive mex. each mailbox has unique id
and processes communicate only if they share mailbox




struct sigaction

sigaction() function allows the calling process to examine and/or specify the action
to be assigned to a specified signal.
sig specifies the used signal.

sigaction {
               void     (*sa_handler)(int);                         /* pointer to a signal-catching function */
               int        sa_flags;                                 /* special flag to affect signal behavior */ 
               sigset_t   sa_mask;                                  /* additional set of signals to be blocked
                                                                       during execution of "sa_handler()" in question */
               void     (*sa_sigaction)(int, siginfo_t *, void *);  /* pointer to "sa_handler()" in question */
               void     (*sa_restorer)(void);
           }

Occupied storage by sa_handler and sa_sigaction may overlap, an application cannot use it simultaneously.

Argument act points to structure specifying the action to be associated with specified signal.
The action previously associated with the signal is stored in the location pointed to by the argument oact.


SIGUSR1 & SIGUSR2 -> signals set aside by you to be used as you want;
they're useful for interprocess communication if you write a signal handler for them in the program that receives signal.
Default action is to terminate the process.


struct siginfo
siginfo_t {
               int      si_signo;     /* Signal number */
               int      si_errno;     /* An errno value */
               int      si_code;      /* Signal code */
               int      si_trapno;    /* Trap number that caused
                                         hardware-generated signal
                                         (unused on most architectures) */
               pid_t    si_pid;       /* Sending process ID */
               uid_t    si_uid;       /* Real user ID of sending process */
               int      si_status;    /* Exit value or signal */
               clock_t  si_utime;     /* User time consumed */
               clock_t  si_stime;     /* System time consumed */
               union sigval si_value; /* Signal value */
               int      si_int;       /* POSIX.1b signal */
               void    *si_ptr;       /* POSIX.1b signal */
               int      si_overrun;   /* Timer overrun count;
                                         POSIX.1b timers */
               int      si_timerid;   /* Timer ID; POSIX.1b timers */
               void    *si_addr;      /* Memory location which caused fault */
               long     si_band;      /* Band event (was int in
                                         glibc 2.3.2 and earlier) */
               int      si_fd;        /* File descriptor */
               short    si_addr_lsb;  /* Least significant bit of address
                                         (since Linux 2.6.32) */
               void    *si_lower;     /* Lower bound when address violation
                                         occurred (since Linux 3.19) */
               void    *si_upper;     /* Upper bound when address violation
                                         occurred (since Linux 3.19) */
               int      si_pkey;      /* Protection key on PTE that caused
                                         fault (since Linux 4.6) */
               void    *si_call_addr; /* Address of system call instruction
                                         (since Linux 3.5) */
               int      si_syscall;   /* Number of attempted system call
                                         (since Linux 3.5) */
               unsigned int si_arch;  /* Architecture of attempted system call
                                         (since Linux 3.5) */
           }


sa_siginfo tells the system to use the signal action specified by sa_sigaction instead of sa_handler.


sigemptyset() --> initializes a signal set to the empty set; all recognized signals are excluded  


int kill(pid_t pid, int sig)
function is used to send a signal to another process or group of processes specified by pid. 
signal sent is specified by the signal and is one from the list given in signal.h or 0:
the latter permits to error check but no signal is sent. (useful to check pid validity).
if pid > 0 sig shall be sent to the process whose process ID is equal to pid.
fill() is successful if the process has permission to send sig to any process specified by pid.
if kill() fails no signal shall be sent.
return value success -> 0 return value unsuccess -> -1


sigaction() specifies more info than signal().
return value from signal cannot express the full range of sigaction possibilities.
If you use signal() to save and later reestablish an action,
it may not be able to reestablish properly a handler that was established with sigaction().
Since sigaction() is more general it can properly save and reestablish any action,
either way if it was set by signal or sigaction.
Signal() may not be versatile between different distros.

