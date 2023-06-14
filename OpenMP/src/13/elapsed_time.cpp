#include <iostream>
#include <chrono> 
#include <thread>
void independentThread()
{
    std::cout << "Starting concurrent thread. \n";
    std::cout << "Sleeping 7 seconds\n";
    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::cout << "Exiting concurrent thread. \n";
}
void threadCaller()
{
    std::cout << "Starting thread caller. \n";
    std::thread t(independentThread);
    t.detach();
    std::cout << "Sleeping 10 seconds\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Exiting thread caller.\n";
}
int main()
{
    auto time_s = std::chrono::high_resolution_clock::now();
    threadCaller();
    std::cout << "Sleeping 5 seconds\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto time_e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = time_e - time_s;
    std::cout << "Elapsed time: " << elapsed_time.count() << " sec\n";
}