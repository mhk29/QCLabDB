#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

int num = 100;
int count = 0;

void work(void* argv) {
	cout << "work" << endl;
	thread_lock(1);
	count = count + 1;
	thread_yield(); // go back to start
	if (count != 0) {
		cout << "correct" << endl;
	}
	count = 0;
	thread_unlock(1);
	return;
}

void end(void* argv) {
	cout << "end" << endl;
	thread_lock(1);
	if (count == 0) {
		cout << "correct" << endl;
		thread_unlock(1);
		return;
	}
	cout << "bad" << endl;
	thread_unlock(1);
	return;
}

void start(void* argv) {
	thread_create((thread_startfunc_t) work, (void *) argv);
	thread_create((thread_startfunc_t) end, (void*) argv);
}

int main(int argc, char** argv) {
  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}