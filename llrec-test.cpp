#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;
#include "stack.h"


/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readListHelper(ifstream& ifile) {
    int v;
    if( ! (ifile >> v) ) return NULL;
    Node *h = new Node(v, NULL);
    h->next = readListHelper(ifile);
    return h;
}

Node* readList(const char* filename) {
    ifstream ifile(filename);
    return readListHelper(ifile);
}

void print(Node* head) {
    if(head == NULL) {
        cout << endl;
        return;
    }
    cout << head->val << " ";
    print(head->next);
}

void dealloc(Node* head) {
    if(head == NULL) {
        return;
    }
    Node* temp = head->next;
    delete head;
    dealloc(temp);
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

struct newFunc{
    bool operator()(int l){
        return !(l % 2);;
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    newFunc l;
 head = llfilter(head, l);
    print(head);
    int n = 2;
    int m = 3;
    Stack<int> htester;
    htester.push(n);
    htester.push(m);
    cout << endl << htester.top() << endl;
    dealloc(head) ; 
    return 0;

}

