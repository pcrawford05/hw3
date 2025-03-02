#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    if(!head){
        return;
    }
    if(head->val <= pivot) {
        smaller = head;
        head = head->next;
        smaller->next = NULL; // Make sure we cut off list so as not to include remaining parts of head
        llpivot(head, smaller->next, larger, pivot);
    }
    else {
        larger = head;
        head = head->next;
        larger->next = NULL; // Make sure we cut off list so as not to include remaining parts of head
        llpivot(head, smaller, larger->next, pivot);
    }
}