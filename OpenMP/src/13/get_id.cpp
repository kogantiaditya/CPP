#include <iostream>

#include <thread>

void hello()

{
    std::cout
        << "Hello Concurrent World\n";
    std::cout << "t1 thread ID again = " << std::this_thread::get_id() << std::endl;
}

int main()

{

    std::cout << "main thread ID = " << std::this_thread::get_id() << std::endl;

    std::thread t1(hello); 
    std::cout << "t1 thread ID = " << t1.get_id() << std::endl;
    t1.join(); 
    auto num_threads = std::thread::hardware_concurrency();
    std::cout << "Max concurrent threads num = " << num_threads << std::endl;

    return 0;
}