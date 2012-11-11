#include "mysignals.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct
{
	int state;
	float more_state;
} state_data;

typedef struct
{
	int a;
	char b;
} test_struct;

#define MEM_ERR 10
#define TEST_1  32
#define TEST_2  12


test_struct* make_struct();

void myhandler(unsigned int sig, void* data, void* bound_data)
{
	state_data* mydata = data;
	int* g_data = bound_data;
	
	/*do something with data */
	fprintf(stderr, "Received signal %u\n", sig);
	fprintf(stderr, "%d\t%f\t%d\n", mydata->state, mydata->more_state, *g_data);
}

void mem_error(unsigned int sig, void* data, void* gdata)
{
	size_t* size = data;
	
	/*do something with data */
	fprintf(stderr, "Memory allocation error!\n", sig);
	fprintf(stderr, "Failed to allocate %u bytes\n", *size);
}

void some_default(unsigned int sig, void* data, void* gdata)
{
	fprintf(stderr, "My default, signal %u\n", sig);
}



int main()
{
	test_struct* mystruct;
	state_data somedata;
	size_t test;
	sighandler_func old;
	int caller_data = 1000;
	
	init_signals(&some_default);
	
	test = 100;
	somedata.state = 25;
	somedata.more_state = 75.5f;
	
	mysignal(TEST_1, &myhandler, &caller_data);
	mysignal(MEM_ERR, &mem_error, &caller_data);
	
	old = mysignal(TEST_2, IGN_SIG, NULL);
	assert(old == some_default);
	
	mystruct = make_struct();
	
	myraise(60, NULL);
	printf("\n\n");
	
	
	myraise(TEST_1, &somedata);
	printf("\n\n");
	myraise(MEM_ERR, &test);
	
	
	
	free(mystruct);
	printf("the end\n");
	
	
	return 0;
}


test_struct* make_struct()
{
	size_t sz = sizeof(test_struct);
	test_struct* tmp = malloc(sz);
	if (!tmp)
		myraise(MEM_ERR, &sz);

	return tmp;
}