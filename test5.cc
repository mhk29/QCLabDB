#include <stdlib.h>
#include <iostream>
#include "thread.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

int g=0;
int max_order;
int current_orders;
int num_threads;
char **gargv = NULL; 
int gargc;
int ready = 0;

int firsttime = 0;
int last_made;

const unsigned int cond = 1;
const unsigned int mylock = 5; 
long last_cashier = -1;
int changer = 0;

vector< pair<long, int> > v;

int main(int argc, char *argv[]);
void start_thread(void *a);
void change();
void start(void *a);
void maker();
int nextsandwich();
int order(long order);

void start_thread(void *a) {
  
  long id = (long) a;

  int sandwich;
  ifstream is(gargv[(long) id + 2], std::ios::in);
  	
  while(is >> sandwich) {
  thread_lock(mylock);


	while (current_orders >= max_order) {
	  thread_wait(mylock,cond);
	}
	current_orders = current_orders + 1;
	cout << "POSTED: cashier " << id << " sandwich " << sandwich << endl;
	v.push_back( make_pair(id, sandwich) );


    thread_broadcast(mylock,cond);
  	while (order(id) == 0) {
	  thread_wait(mylock,cond);
	}

  thread_unlock(mylock);
  }
    thread_broadcast(mylock,cond);
  	thread_unlock(mylock);

  	change();
}

void change() {
  num_threads = num_threads - 1;

  if (num_threads < max_order) {
  	max_order = num_threads;
  }
}

void maker() {

	do {
		thread_lock(mylock);
		while(current_orders < max_order ) {
			thread_wait(mylock,cond);
		}
		  int mynum = nextsandwich();
		  current_orders = current_orders - 1; 
		  if (current_orders < 0) {
		  	break;
		  }
		  cout << "READY: cashier " << v[mynum].first << " sandwich " << v[mynum].second << endl;
		  v.erase(v.begin()+mynum);
		thread_broadcast(mylock,cond);
		thread_unlock(mylock);
	 } while (1);
    thread_broadcast(mylock,cond);
  	thread_unlock(mylock);
}

int nextsandwich() {

  int distance = 1001;
  int next = 0;

  for (unsigned int k = 0; k < v.size(); k = k + 1) {
    if (abs(v[k].second - last_made) < distance) {
      distance = abs(v[k].second - last_made);
      next = k;
    }
  }
  last_made = v[next].second;
  return next;
}

int order(long order) {
	int returnable;
	for (unsigned int m = 0; m < v.size(); m = m + 1) {
		if (order == v[m].first) {
			returnable = 0;
			return returnable;
		}
	}
	returnable = 1;
	return returnable;
}

void start(void *a) {
  for (long i = 0; i < gargc - 2; i = i + 1) {
    if (thread_create((thread_startfunc_t) start_thread, (void *) i)) {
      cout << "thread_create failed\n";
      exit(1);
    }
  }
  maker();
}

int main(int argc, char *argv[]) {

  max_order = 5;
  gargc = 7;
  num_threads = gargc - 2;

  char gargvin[5][10] = {
    "sw.in0",
    "sw.in1",
    "sw.in2",
    "sw.in3",
    "sw.in4"
  };

  **gargv = **gargvin;

  if (max_order == 0) {
  	cout << "Can't take 0 orders" << endl;
  	return 0;
  }

  if (max_order > num_threads) {
  	max_order = num_threads;
  }

  if (thread_libinit( (thread_startfunc_t) start, (void *) 100)) {
    cout << "thread_libinit failed\n";
    exit(1);
  }
}

