/*
NOTES:
1. Condition variables allow us to synchronize threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronize two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition
*/
	
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex to ensure thread-safe access

// Function to print even numbers
void printEven(int& current) {
    while (current <= 20) {
        mtx.lock();  // Lock to ensure mutual exclusion
        if (current % 2 == 0) {
            std::cout << "even"<<current << " ";
            current++;
        }
        mtx.unlock();  // Unlock after printing
    }
}

// Function to print odd numbers
void printOdd(int& current) {
    while (current <= 20) {
        mtx.lock();  // Lock to ensure mutual exclusion
        if (current % 2 != 0) {
            std::cout << "odd" <<current << " ";
            current++;
        }
        mtx.unlock();  // Unlock after printing
    }
}

int main() {
    int current = 1;  // Start from 1
    std::thread t1(printEven, std::ref(current));  // Thread for even numbers
    std::thread t2(printOdd, std::ref(current));   // Thread for odd numbers

    t1.join();  // Wait for the even number thread to finish
    t2.join();  // Wait for the odd number thread to finish

    std::cout << std::endl;
    return 0;
}

What is does:
Both threads constantly run and acquire the mutex.
If it's not their turn (e.g., even thread sees an odd number), they just skip and loop again.
This leads to busy-waiting: CPU cycles are wasted checking conditions rapidly.
It can also lead to thread starvation or contention, especially under high CPU load.
--------------------------------------------------------------------------------------------------------------------------------------  
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mt;
condition_variable cv;

bool isOddTurn = true;  // Start with odd number

void printOdd(int& x)
{
    while (x < 50)
    {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [&]() { return x % 2 != 0; });  // Wait for odd turn

        if (x >= 50) break;  // Re-check condition after wakeup

        cout << "Number printed by odd thread: " << x << endl;
        x++;
        cv.notify_all();  // Notify other thread
    }
}

void printEven(int& x)
{
    while (x < 50)
    {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [&]() { return x % 2 == 0; });  // Wait for even turn

        if (x >= 50) break;  // Re-check condition after wakeup

        cout << "Number printed by even thread: " << x << endl;
        x++;
        cv.notify_all();  // Notify other thread
    }
}

int main()
{
    int var = 1;
    thread odd(printOdd, std::ref(var));
    thread even(printEven, std::ref(var));

    odd.join();
    even.join();

    return 0;
}
❌ Without condition variable: Both are yelling "Is it my turn?!" repeatedly, wasting energy.
✅ With condition variable: One person speaks, then says "Now it's your turn", and waits quietly.

-------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitForSignal() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Waiting for signal...\n";
    cv.wait(lock, [] { return ready; });  // Wait until ready becomes true
    std::cout << "Received signal! Proceeding...\n";
}

void sendSignal() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Sending signal.\n";
    }
    cv.notify_one();  // Wake up one waiting thread
}

int main() {
    std::thread t1(waitForSignal);
    std::thread t2(sendSignal);

    t1.join();
    t2.join();

    return 0;
}
