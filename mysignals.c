#include "mysignals.h"
#include <stdio.h>

static sighandler_func handlers[MAX_HANDLERS];
static void* bound_data[MAX_HANDLERS];

void default_handler(unsigned int sig, void* data, void* gdata)
{
	printf("Received signal %u\n", sig);
}



static sighandler_func def_handler = &default_handler;



void init_signals(sighandler_func def_sighandler)
{
	int i;
	if (def_sighandler)
		def_handler = def_sighandler;
	
	for (i=0; i<MAX_HANDLERS; i++) {
		handlers[i] = def_handler;
		bound_data[i] = NULL;
	}
}


void myraise(unsigned int sig, void* local_data)
{
	if (sig < MAX_HANDLERS && handlers[sig])
		handlers[sig](sig, local_data, bound_data[sig]);
}

sighandler_func mysignal(unsigned int sig, sighandler_func func, void* data)
{
	sighandler_func old_handler = NULL;
	if (sig < MAX_HANDLERS) {
		old_handler = handlers[sig];
		bound_data[sig] = data; 
		
		if (func == DFL_SIG) {
			handlers[sig] = def_handler;
		} else if (func == IGN_SIG) {
			handlers[sig] = NULL;
		} else {
			handlers[sig] = func;
		}
	}
		
	return old_handler;
}

