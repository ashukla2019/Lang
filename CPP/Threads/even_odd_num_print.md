#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
int num = 0;

void printEven() {
    while (num <= 10) {
        lock_guard<mutex> lock(mtx);

        if (num % 2 == 0) {
            cout << "Even: " << num << endl;
            num++;
        }
    }
}

void printOdd() {
    while (num <= 10) {
        lock_guard<mutex> lock(mtx);

        if (num % 2 != 0) {
            cout << "Odd: " << num << endl;
            num++;
        }
    }
}

int main() {
    thread t1(printEven);
    thread t2(printOdd);

    t1.join();
    t2.join();

    return 0;
}
