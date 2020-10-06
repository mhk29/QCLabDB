#include <cstdlib>
#include <iostream>
#include "thread.h"
using namespace std;

int bad_create = 2;
unsigned int lock1 = 1;
unsigned int lock2 = 2;
unsigned int lock3 = 3;

unsigned int badcond = 100;
unsigned int goodcond = 4;

int count = 0;
int top = 10;
int totaler = 0;
int num = 1;

void check() {

// thread lock
// acquire already locked lock
if (thread_lock(lock1) == 0) {
	cout << "acquired already held lock" << endl;
}
else cout << "good: did not acquire lock" << endl;

if (thread_unlock(lock2) == 0) {
	cout << "unlocked lock2" << endl;
}
else cout << "good: did not unlock lock2" << endl;
// unlock failed
if (thread_unlock(lock3) == 0) {
	cout << "unlocked bad lock" << endl;
} 
else cout << "good: did not unlock lock3" << endl;

// failed wait
if (thread_wait(lock3, badcond)) {
	cout << "waiting on good variables" << endl;
}
else cout << "good: did not wait on lock3" << endl;

// failed wait
if (thread_wait(lock2, badcond) == 0) {
		cout << "waiting on bad variables" << endl;

}
else cout << "good: did not wait on lock2" << endl;

if (thread_wait(lock3, goodcond) == 0) {
	cout << "waiting on bad variables" << endl;
}
cout << "good: did not wait on lock2" << endl;

// failed wait
if (thread_wait(lock3, badcond) == 0) {
		cout << "waiting on bad variables" << endl;

}
else cout << "good: did not wait on lock3" << endl;

if (thread_wait(lock2,goodcond)) {
	cout << "waiting on good variables" << endl;
}
else cout << "good: did not wait on lock2" << endl;


// incorrect signal on bad condition
if (thread_signal(lock1, badcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;
if (thread_broadcast(lock1, badcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;

if (thread_signal(lock3, goodcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;
if (thread_broadcast(lock3, goodcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;

if (thread_signal(lock2, goodcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;
if (thread_broadcast(lock2, goodcond) != 0) {
	cout << "bad" << endl;
}
else cout << "good" << endl;

// thread unlock fails


// thread signal fails


// thread wait fails


// unlock on bad lock


// bad yield

}

void fourth(void* argv) {
	while(count < top) {
		thread_lock(lock1);
		totaler = totaler + 1;
		check();
		while (num != 3) {
			thread_wait(lock1, goodcond);
		}
		totaler = totaler - 1;
		count = count + 1;
		num = 1;
		thread_broadcast(lock1, goodcond);
		thread_unlock(lock1);
		thread_yield();
	}

	cout << "done3" << endl;

}

void third(void* argv) {
	while(count < top) {
		thread_lock(lock1);
		totaler = totaler + 1;
		check();
		while (num != 2) {
			thread_wait(lock1, goodcond);
		}
		totaler = totaler - 1;
		count = count + 1;
		num = 3;
		thread_broadcast(lock1, goodcond);
		thread_unlock(lock1);
		thread_yield();
	}

	cout << "done3" << endl;

}

void second(void* argv) {

	while(count < top) {
		thread_lock(lock1);
		totaler = totaler + 1;
		check();
		while (num != 1) {
			thread_wait(lock1, goodcond);
		}
		totaler = totaler - 1;
		count = count + 1;
		num = 2;
		thread_broadcast(lock1, goodcond);
		thread_unlock(lock1);
		thread_yield();
	}

	cout << "done2" << endl;
}

void first(void* argv) {

	cout << "first" << endl;
	thread_lock(lock2);
	thread_lock(lock1);

	while (count < top - 1) {
		thread_wait(lock1,goodcond);
	}
	thread_broadcast(lock1,goodcond);

	thread_unlock(lock1);
	thread_unlock(lock2);
	cout << "done1" << endl;
}

void bad() {
	cout << "bad" << endl;
}



void start() {

    thread_create((thread_startfunc_t) first, (void*) NULL);
    thread_create((thread_startfunc_t) second, (void*) NULL);
    thread_create((thread_startfunc_t) third, (void*) NULL);
    thread_create((thread_startfunc_t) fourth, (void*) NULL);

	thread_libinit( (thread_startfunc_t) bad, (void*) NULL);
}


// signal, lock, broadcast, unlock, create, wait before starting 
int main(int argc, char** argv) {

	if (thread_signal(1,1) == 0) {
		cout << "Bad Signal" << endl;
	}
	if (thread_broadcast(1,1) == 0) {
		cout << "Bad broadcast" << endl;
	}
	if (thread_wait(1,1) == 0) {
		cout << "Bad wait" << endl;
	}
	if (thread_lock(1) == 0) {
		cout << "Bad lock" << endl;
	}
	if (thread_unlock(1) == 0) {
		cout << "Bad unlock" << endl;
	}
	if (thread_create((thread_startfunc_t) start, (void *) bad_create) == 0) {
		cout << "Bad create" << endl;
	}

	if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
		cout << "thread_libinit failed\n";
		exit(1);
	}

}