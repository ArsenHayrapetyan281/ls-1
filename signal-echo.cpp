#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <cstdint>
#include <ucontext.h>

void signal_handler(int signum, siginfo_t *info, void *context) {
    pid_t sender_pid = info->si_pid;
    uid_t sender_uid = info->si_uid;
    struct passwd *pwd = getpwuid(sender_uid);
    const char *username = (pwd != nullptr) ? pwd->pw_name : "Unknown";

    ucontext_t *uc = (ucontext_t *)context;
    uintptr_t eip = (uintptr_t)uc->uc_mcontext.gregs[REG_RIP];
    uintptr_t eax = (uintptr_t)uc->uc_mcontext.gregs[REG_RAX];
    uintptr_t ebx = (uintptr_t)uc->uc_mcontext.gregs[REG_RBX];

    std::cout << "Received a SIGUSR1 signal from process " << sender_pid 
              << " executed by " << sender_uid << " (" << username << ")." << std::endl;
    std::cout << "State of the context: EIP = " << eip 
              << ", EAX = " << eax << ", EBX = " << ebx << "." << std::endl;
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    std::cout << "PID: " << getpid() << std::endl;

    while (true) {
        sleep(10);
    }

    return 0;
}







































