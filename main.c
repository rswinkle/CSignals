#include "mysignals.h"

#include <stdio.h>
#include <stdlib.h>


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


test_struct* make_struct();

void myhandler(unsigned int sig, void* data)
{
	state_data* mydata = data;
	
	/*do something with data */
	fprintf(stderr, "Received signal %u\n", sig);
	fprintf(stderr, "%d\t%f\n", mydata->state, mydata->more_state);
}

void mem_error(unsigned int sig, void* data)
{
	size_t* size = data;
	
	/*do something with data */
	fprintf(stderr, "Memory allocation error!\n", sig);
	fprintf(stderr, "Failed to allocate %u bytes\n", *size);
}

void some_default(unsigned int sig, void* data)
{
	fprintf(stderr, "My default, signal %u\n", sig);
}



int main()
{
	test_struct* mystruct;
	state_data somedata;
	size_t test;
	
	init_signals(&some_default);
	
	test = 100;
	somedata.state = 25;
	somedata.more_state = 75.5f;
	
	mysignal(32, &myhandler);
	mysignal(MEM_ERR, &mem_error);
	
	mystruct = make_struct();
	
	myraise(60, NULL);
	printf("\n\n");
	
	
	myraise(32, &somedata);
	printf("\n\n");
	myraise(MEM_ERR, &test); 
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