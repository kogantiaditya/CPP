#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

std::mutex mtx;  // Mutex to protect shared resources
std::condition_variable bufferNotEmpty;  // Condition variable for consumers
std::condition_variable bufferNotFull;   // Condition variable for producers
std::vector<int> buffer;  // Multi-size buffer
const int BUFFER_SIZE = 5;  // Maximum buffer size
const int SAMPLE_SIZE = 20; // Number of items to produce and consume
int itemsProduced = 0;  // Counter for items produced
int itemsConsumed = 0;  // Counter for items consumed

// Function for the producer thread
void producer(int id)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    while (itemsProduced < SAMPLE_SIZE) {
        // Generate data
        int data = dist(gen);

        // Acquire the lock
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is full
        bufferNotFull.wait(lock, []() { return buffer.size() < BUFFER_SIZE; });

        // Add data to the buffer
        buffer.push_back(data);

        // Print producer status
        std::cout << "Producer " << id << " produced: " << data << " (Thread ID: " << std::this_thread::get_id() << ")" << std::endl;

        // Notify consumers that the buffer is not empty
        bufferNotEmpty.notify_all();

        // Increment the items produced counter
        ++itemsProduced;

        // Release the lock
        lock.unlock();
    }
}

// Function for the consumer thread
void consumer(int id)
{
    while (itemsConsumed < SAMPLE_SIZE) {
        // Acquire the lock
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is empty
        bufferNotEmpty.wait(lock, []() { return !buffer.empty(); });

        // Consume data from the buffer
        int data = buffer.back();
        buffer.pop_back();

        // Print consumer status
        std::cout << "Consumer " << id << " consumed: " << data << " (Thread ID: " << std::this_thread::get_id() << ")" << std::endl;

        // Notify producers that the buffer is not full
        bufferNotFull.notify_all();

        // Increment the items consumed counter
        ++itemsConsumed;

        // Release the lock
        lock.unlock();
    }
}

int main()
{
    // Create producer threads
    std::vector<std::thread> producers;
    for (int i = 0; i < 3; ++i) {
        producers.emplace_back(producer, i);
    }

    // Create consumer threads
    std::vector<std::thread> consumers;
    for (int i = 0; i < 2; ++i) {
        consumers.emplace_back(consumer, i);
    }

    // Join the producer threads
    for (auto& producerThread : producers) {
        producerThread.join();
    }

    // Join the consumer threads
    for (auto& consumerThread : consumers) {
        consumerThread.join();
    }

    return 0;
}
