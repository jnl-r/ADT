#include <iostream>
#include "arraystack.h"

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

    return 0;
}
