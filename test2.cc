#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

static int num = 100;
static int threadsmade = 5;
int numorders = 0;
static int maxorders = 3;
int count = 0;


void first(void* argv) {
	thread_lock(1);

	while(count == 0) {
		cout << "entered while() loop 1" << endl;
		count = count + 1;
		thread_signal(1,1);
		thread_wait(1,1);
	}

	cout << "count:" << count << endl;
    thread_unlock(1); 
    return;
}

void second(void* argv) {
	thread_lock(1);
	while(count == 1) {
		cout << "entered while() loop 2" << endl;
		count = count - 1;
		thread_signal(1,1);
		thread_wait(1,1);
	}

	cout << "count:" << count << endl;
    thread_unlock(1); 
    return;
}



void start(void* argv) {
	cout << "begin" << endl;
	if (thread_create((thread_startfunc_t) first, (void*) argv)) {
		exit(1);
	}
	if (thread_create((thread_startfunc_t) second, (void*) argv)) {
		exit(1);
	}
}

// back and forth cases
int main(int argc, char** argv) {
  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}