# Simple Vector Implementation in C++

A very basic implementation of a dynamic array (similar to `std::vector`).

```cpp
#include <iostream>

class Vector
{
private:
    int* arr;
    int size;
    int capacity;

public:
    Vector()
    {
        size = 0;
        capacity = 1;
        arr = new int[capacity];
    }

    ~Vector()
    {
        delete[] arr;
    }

    void push_back(int value)
    {
        // Resize if array is full
        if (size == capacity)
        {
            capacity *= 2;

            int* temp = new int[capacity];

            for (int i = 0; i < size; i++)
                temp[i] = arr[i];

            delete[] arr;
            arr = temp;
        }

        arr[size] = value;
        size++;
    }

    void pop_back()
    {
        if (size > 0)
            size--;
    }

    int get(int index)
    {
        return arr[index];
    }

    int getSize()
    {
        return size;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            std::cout << arr[i] << " ";

        std::cout << std::endl;
    }
};

int main()
{
    Vector v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    v.print();

    std::cout << "Size = " << v.getSize() << std::endl;

    v.pop_back();

    v.print();

    return 0;
}
```

## Output

```
10 20 30 40
Size = 4
10 20 30
```

## How `push_back()` Works

```
Initially

Capacity = 1

+----+
|    |
+----+

push_back(10)

+----+
|10  |
+----+

push_back(20)

Capacity becomes 2

+----+----+
|10  |20  |
+----+----+

push_back(30)

Capacity becomes 4

+----+----+----+----+
|10  |20  |30  |    |
+----+----+----+----+
```

### Time Complexity

| Operation | Complexity |
|-----------|------------|
| push_back() | O(1) amortized |
| pop_back() | O(1) |
| get() | O(1) |
| print() | O(n) |