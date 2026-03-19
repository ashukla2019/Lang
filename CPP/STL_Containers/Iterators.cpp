1) Input Iterator: Can read values but only in one direction (forward).Suitable for single-pass algorithms (e.g., reading from a stream).

ex:
#include <iostream>
#include <iterator>
#include <sstream>

int main() {
    std::istringstream ss("10 20 30");
    std::istream_iterator<int> it(ss), end;
    while (it != end) {
        std::cout << *it << " ";
        ++it;
    }
}

2. Output Iterator:Write-only access, single-pass.Used to output values (e.g., to a stream or container).

Ex:
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    std::ostream_iterator<int> out_it(std::cout, " ");
    for (int val : v) {
        *out_it = val; // Writes to cout
    }
}
3. Forward Iterator:Can read/write, move forward only, multiple passes allowed.

Ex:
#include <iostream>
#include <forward_list>

int main() {
    std::forward_list<int> fl = {10, 20, 30};
    for (auto it = fl.begin(); it != fl.end(); ++it) {
        std::cout << *it << " ";
    }
}
4. Bidirectional Iterator:Can move forward and backward.Used in containers like list, set, map.

Ex:
#include <iostream>
#include <list>

int main() {
    std::list<int> l = {5, 10, 15};
    auto it = l.end();
    while (it != l.begin()) {
        --it;
        std::cout << *it << " ";
    }
}
5. Random Access Iterator:All operations supported: +, -, <, >, [].
Used in vector, deque, array.

Ex:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    auto it = v.begin();
    std::cout << it[2]; // Output: 3
}
