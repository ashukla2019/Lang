#include <mutex>
#include <condition_variable>

class ReadWriteLock {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int readers = 0;
    bool writer = false;

public:
    // Shared lock (for readers)
    void lock_shared() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer; }); // wait until no writer
        ++readers;
    }

    void unlock_shared() {
        std::unique_lock<std::mutex> lock(mtx);
        --readers;
        if (readers == 0) {
            cv.notify_all(); // notify writers waiting
        }
    }

    // Exclusive lock (for writer)
    void lock_exclusive() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer && readers == 0; }); // wait for readers and writers
        writer = true;
    }

    void unlock_exclusive() {
        std::unique_lock<std::mutex> lock(mtx);
        writer = false;
        cv.notify_all(); // notify all waiting readers/writers
    }
};
