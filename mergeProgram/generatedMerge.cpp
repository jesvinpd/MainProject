#include <iostream>
using namespace std;

struct Node { int data; Node* next; Node(int d): data(d), next(NULL) {} };

Node* push(Node* head, int val) { Node* n = new Node(val); n->next = head; return n; }
void print(Node* head) { while(head){ cout<<head->data<<" "; head=head->next;} cout<<endl; }
Node* merge(Node* a, Node* b) {
    if(!a) return b;
    if(!b) return a;
    if(a->data < b->data) { a->next = merge(a->next, b); return a; }
    else { b->next = merge(a, b->next); return b; }
}

int main() {
    Node* list1 = NULL;
    list1 = push(list1, 9);
    list1 = push(list1, 7);
    list1 = push(list1, 5);
    list1 = push(list1, 3);
    list1 = push(list1, 1);
    Node* list2 = NULL;
    list2 = push(list2, 10);
    list2 = push(list2, 8);
    list2 = push(list2, 6);
    list2 = push(list2, 4);
    list2 = push(list2, 2);
    Node* merged = merge(list1, list2);
    print(merged);
}
