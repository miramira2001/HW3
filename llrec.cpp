#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot){

	if(head == nullptr){
		smaller = nullptr;
		larger = nullptr;
		return;
	}

	if(head-> val <= pivot){
		smaller = head;
		head = head-> next;
		smaller-> next = nullptr;
		llpivot(head, smaller-> next, larger, pivot);
	}

	else if(head-> val > pivot){
		larger = head;
		head = head-> next;
		larger-> next = nullptr;
		llpivot(head, smaller, larger-> next, pivot);
	}

	else if(head-> next == nullptr){
		if(head-> val <= pivot){
			smaller = head;
			larger = nullptr;
		}else{
			larger = head;
			smaller = nullptr;
		}
		head = nullptr;
	}

}
