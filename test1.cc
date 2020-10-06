
#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

static int num = 100;
static int threadsmade = 5;
int numorders = 0;
static int maxorders = 3;
int run = 0;
int count = 0;


void order(void* argv) {
	// thread_lock(1);
	int i;
	cout << "order called with " << (char*) argv << endl;

	for (i = 0; i < threadsmade; i = i + 1) {
		run = run + 1;
		cout << (char*) argv << ":\t" << i << "\t" << run << endl;
		if (thread_yield()) {
			cout << "thread_yield failed" << endl;
			exit(1);
		}
	}
	// thread_unlock(1);
}

void maker(void* argv) {
	cout << "maker called" << endl;
	thread_lock(1);
	count = count + 1;
	cout << "count increased" << count << endl;
	thread_wait(1,1);

	cout << "count to be decreased" << count << endl;
	count = count - 1;
	thread_broadcast(1,1);
	thread_unlock(1);
}

void done(void* argv) {
	cout << "done" << endl;
	thread_signal(1, 1);
}

void start(void* argv) {
	long arg = (long) argv;
    cout << "parent called with arg " << arg << endl;
    for (int i = 0; i < 5; i = i + 1) {
        if (thread_create((thread_startfunc_t) order, (void *) "start made thread")) {
            cout << "thread_create failed\n";
            exit(1);
        }
    }

    order((void *) "parent thread");

    cout<<"creating threads and signal"<<endl;
    for (int i = 0; i < 5; i = i + 1) {
        if (thread_create((thread_startfunc_t) maker, (void *) "signal thread")) {
            cout << "thread_create failed\n";
            exit(1);
        }
    }

    thread_create((thread_startfunc_t) done, (void *) "wake thread");

}

int main(int argc, char** argv) {
  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}