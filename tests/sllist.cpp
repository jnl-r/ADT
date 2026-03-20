#include <iostream>
    #include "../src/sllist.h"

using namespace std;

int main() {
    SLList<int> q;
    
    cout << "LINKED LIST TESTS" << endl;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Enqueued 10, 20, 30. Size: " << q.size() << " (Expected 3)" << endl;
    
    cout << "Dequeued: " << q.dequeue() << " (Expected 10)" << endl;
    cout << "Dequeued: " << q.dequeue() << " (Expected 20)" << endl;
    
    q.enqueue(40);
    cout << "Enqueued 40. Size: " << q.size() << " (Expected 2)" << endl;
    
    cout << "Dequeued: " << q.dequeue() << " (Expected 30)" << endl;
    cout << "Dequeued: " << q.dequeue() << " (Expected 40)" << endl;
    
    cout << "Final size: " << q.size() << " (Expected 0)" << endl;
    
    return 0;
}