#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

int num = 100;
//the numbers are arbitrary
static const int LOCK_NUMBER = 5;
static const int COND_NUMBER = 6;   


void broadtest(void* argv) {

	cout << "check broadcast" << endl;

	thread_lock(1);
	thread_wait(1,1);
	thread_unlock(1);

	if (thread_broadcast(1,1) == -1) {
		cout << "failed" << endl;
	} else {
		cout << "success" << endl;
	}

	return;
}

void jump(void* argv) {
	cout << "try2" << endl;
	thread_lock(1);
	thread_wait(1,1);
	thread_unlock(1);
	return;
}

void done(void* argv) {
	cout << "try3" << endl;
	thread_lock(1);
	thread_broadcast(1,1);
	thread_unlock(1);
	return;
}

void start(void* argv) {
	cout << "begin" << endl;
	if (thread_create( (thread_startfunc_t) broadtest, (void *) argv)) {
		exit(1);
	}

	if (thread_create( (thread_startfunc_t) jump, (void *) argv)) {
		exit(1);
	}

	if (thread_create( (thread_startfunc_t) done, (void *) argv)) {
		exit(1);
	}

	return;
}

int main(int argc, char** argv) {
  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}