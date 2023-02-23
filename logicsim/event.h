#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};
typedef struct EventLess {
        bool operator()(Event* m, Event* n){
				if(m-> time < n-> time){
					return true;
					}
					return false;
				}
} EventLess;
	
#endif