#ifndef MYSIGNALS_H
#define MYSIGNALS_H

typedef void (*sighandler_func)(unsigned int, void*);

#define MAX_HANDLERS 64



extern sighandler_func handlers[MAX_HANDLERS];


void myraise(unsigned int sig, void* data);

int mysignal(unsigned int sig, sighandler_func func);


void init_signals(sighandler_func def_sighandler);











#endif