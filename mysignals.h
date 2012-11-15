#ifndef MYSIGNALS_H
#define MYSIGNALS_H

typedef void (*sighandler_func)(unsigned int, void*, void*);

#define MAX_HANDLERS 64

#define DFL_SIG (sighandler_func)0
#define IGN_SIG (sighandler_func)1


void rw_raise(unsigned int sig, void* local_data);

sighandler_func rw_signal(unsigned int sig, sighandler_func func, void* bound_data);


void rw_init_signals(sighandler_func def_sighandler);











#endif