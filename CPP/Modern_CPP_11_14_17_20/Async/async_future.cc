std::async: runs a function asynchronously (potentially on a separate thread) and returns a std::future to retrieve
the result.

#include <iostream>
#include <future>

    1. std::launch::async(Asynchronous Launch)
       Behavior: The function you pass to std::async is executed immediately in a separate thread.

        std::future::get() :  Calling.get() will block until the asynchronous operation(running on a separate thread)
        finishes and provides a result.

        The thread that executes the function is created and managed automatically by the C++ runtime, 
        and get() waits for the result from that thread.

    2. std::launch::deferred(Deferred Launch)
        Behavior: The function you pass to std::async does not execute immediately.Instead, it is deferredand will only
        be executed when you call.get() or .wait() on the std::future.

        std::future::get() :  Calling.get() will trigger the execution of the deferred task synchronously on the same thread that calls get().
        The computation is not asynchronous in this case — it runs synchronously in the calling thread only when get() is invoked.
    
    3.  std::future: is an object that acts as a placeholder for a result that will be computed asynchronously.

    //.get() retrieves the result and blocks if not ready.
    //.wait() just blocks until ready(without retrieving the value).
    //.valid() checks if the future still holds a result.

Why is std::async still considered asynchronous?
Even though .get() waits for the result, the task was still run asynchronously because it was launched on a 
separate thread. This separation of concerns—execution being asynchronous (in a separate thread) 
and retrieving the result being synchronous (blocking until the result is available)—is what makes 
std::async asynchronous.

int compute() {
    return 42;
}

int main() {
    //launch::async forces it to run on a new thread.
    //std::future<int> result = std::async(std::launch::async, compute);
    //No force it to run on a new thread.
    //std::future<int> result = std::async(compute);
    //std::launch::deferred: delays execution until get() or wait() is called
    std::future<int> result = std::async(std::launch::deferred, compute);
    std::cout << "Result: " << result.get() << std::endl;
}


//std::promise is used to communicate data between threads.It allows one thread(the producer) to send a value or
//an exception to another thread(the consumer) through a std::future

Ex:
#include <iostream>
#include <future>
#include <stdexcept>
#include <chrono>

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return a / b;
}

int main() {
    try {
        // Start async task with exception
        std::future<int> result = std::async(std::launch::async, divide, 10, 0);
        
        // Get the result (this will throw the exception)
        int value = result.get();
        std::cout << "Result: " << value << std::endl;
    }
    catch (const std::exception& e) {
        // Handle exception thrown by the async task
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}


-----------------------------------------------------------------------------------------------  
can we use promise with async

Yes, you can use std::promise with std::async, but usually you don’t need to — because std::async already returns 
a std::future that gives you the result of the asynchronous task automatically.

However, there are valid reasons to combine std::promise with std::async, especially in more complex workflows, 
such as:

Sharing a result across multiple threads
Setting a result manually from somewhere else
Handling multi-threaded pipelines

Ex:
#include <iostream>
#include <thread>
#include <future>

void async_work(std::promise<int> prom) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    prom.set_value(42);  // Set the result
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    // Pass the promise to async task
    std::async(std::launch::async, async_work, std::move(prom));

    std::cout << "Waiting for result...\n";
    int result = fut.get();  // Will wait until prom.set_value is called
    std::cout << "Result: " << result << std::endl;
}
------------------------------------------------------------------------------------------------
Feature	future.get()	                               future.wait()
Returns value	✅ Yes	                                ❌ No
Invalidates	✅ Yes (future can't be reused)	        ❌ No
Can rethrow exception	✅ Yes	                        ❌ No
Can be called multiple times❌ No	                    ✅ Yes

✅ When to Use Which?
Use .get() when you need the result of the asynchronous operation.

Use .wait() when you just want to wait for completion (e.g., before doing something else), but not yet retrieve the result.

------------------------------------------------------------------------------------------------------
std::async(std::launch::async, ...) vs. std::thread

Feature	std::async(std::launch::async, ...)	Vs                         std::thread
Thread creation	Yes (usually creates a new thread)	                   Yes (explicitly creates a thread)
Automatic thread management	✅ Yes	                                   ❌ No (you must join() or detach())
Returns result	✅ Yes, via std::future	                           ❌ No built-in return value
Exception handling ✅ Automatically captured by future	               ❌ You must handle them yourself
Synchronization	✅ Built-in via future::get()	                       ❌ Manual (mutex, condition_variable)
Launch policy control	Can defer or force async	                   Always async (thread starts immediately)
Destruction behavior: Waits on .get() or in destructor (if not called) You must call join() or detach() yourself
