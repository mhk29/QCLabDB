#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

int num = 100;
int numorders = 0;
static int maxorders = 3;

void order(void* argv) {
	thread_lock(1);
	while(numorders == 0) {
		thread_wait(1,1);
	}

	numorders = numorders - 1;
	cout << (char*) argv << numorders;

	thread_signal(1,2);
	if (thread_signal(1,3)) {
		cout << "bad; unseen CV";
	}
	if (thread_signal(2,3)) {
		cout << "bad; unseen CV";
	}

	thread_unlock(1);
	cout << "correct" << endl;
	return;
}

void maker(void* argv) {
	thread_lock(1);

	while(numorders == maxorders) {
		thread_wait(1,2);
	}

	numorders = numorders + 1;
	cout << (char*) argv << numorders;

	thread_unlock(1);
	cout << "correct" << endl;
	return;
}

void start(void* argv) {
	thread_create((thread_startfunc_t) order, (void*) "order1");
	thread_create((thread_startfunc_t) order, (void*) "order2");
	thread_create((thread_startfunc_t) maker, (void*) "maker");
	cout << "correct" << endl;
}

int main(int argc, char** argv) {

  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}
