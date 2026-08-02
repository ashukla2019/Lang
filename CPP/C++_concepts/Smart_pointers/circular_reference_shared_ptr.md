#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    weak_ptr<Node> next;

    ~Node() {
        cout << "Node destroyed\n";
    }
};

int main()
{
    auto node = make_shared<Node>();

    // node reference count = 1
    // weak_ptr stores the reference but does not increase count.
    node->next = node;

    // When main ends, local shared_ptr "node" is destroyed.
    // Reference count becomes 0.
    // Object is deleted and destructor is called.

    return 0;
}
