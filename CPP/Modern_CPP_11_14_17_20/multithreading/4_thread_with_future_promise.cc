#include <iostream>
#include <future>
#include <thread>

// Function to run in thread
void computeSquare(std::promise<int> prom) {
    prom.set_value(100);  // Set result in promise
}

int main() {
    std::promise<int> prom;              // Create promise
    std::future<int> fut = prom.get_future(); // Get future from promise

    // Start thread and pass promise to it
    std::thread t(computeSquare, std::move(prom));

    // Get result from future
    int result = fut.get();
    std::cout << "result is: " << result << std::endl;

    t.join(); // Wait for thread to finish
    return 0;
}
