#include <iostream>
#include <thread>

void hello()
{
        std::cout<<"Hello concurrent World\n";
}

int main()
{
        std::thread t1(hello);
        t1.detach();
}