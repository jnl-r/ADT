#include <iostream>
#include "../src/arraystack.h"

using namespace std;

int main()
{
    ArrayStack<int> st;

    st.add(0, 10); // test >> add 10 at position 0
    st.add(1, 20);
    st.add(2, 30);

    cout << "Size: " << st.size() << endl;
    cout << "Element at index 1: " << st.get(1) << endl;

    int removed = st.remove(1);
    cout << "Removed: " << removed << endl;

    cout << "New size: " << st.size() << endl;
    cout << "Element at index 1: " << st.get(1) << endl;

    cout << "\ntesing FILO" << endl;
    st.push(100);
    st.push(200);
    cout << "Pushed 100 and 200. New size: " << st.size() << endl;
    
    cout << "Popped: " << st.pop() << " (Expected 200)" << endl;
    cout << "Popped: " << st.pop() << " (Expected 100)" << endl;
    cout << "Size after pops: " << st.size() << endl;

    return 0;
}