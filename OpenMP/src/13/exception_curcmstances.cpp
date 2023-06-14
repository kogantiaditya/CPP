#include <iostream>

#include <thread>

void hello()

{

    std::cout << "Hello Concurrent World\n";
}

int main()

{
    
    std::thread t1(hello); 

    try
    {

        for (int i = 0; i < 100; i++)

            std::cout << "from main: " << i << std::endl;
    }

    catch (...)
    {
        t1.join();

        throw;
    }

    t1.join(); 
}