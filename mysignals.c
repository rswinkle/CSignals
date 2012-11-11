#include "mysignals.h"
#include <stdio.h>

sighandler_func handlers[64];


void default_handler(unsigned int sig, void* data)
{
	printf("Received signal %u\n", sig);
}

sighandler_func def_handler = &default_handler;

void init_signals(sighandler_func def_sighandler)
{
	int i;
	if (def_sighandler)
		def_handler = def_sighandler;
	
	for (i=0; i<MAX_HANDLERS; i++)
		handlers[i] = def_handler;
	
}


void myraise(unsigned int sig, void* data)
{
	if (sig < MAX_HANDLERS)
		handlers[sig](sig, data);
}

int mysignal(unsigned int sig, sighandler_func func)
{
	if (sig < MAX_HANDLERS)
		handlers[sig] = func;
	
	return 0;
}

