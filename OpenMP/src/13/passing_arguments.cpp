#include <iostream>
#include <thread> 
#include <string>

class Fctor
{
public:
    void operator()(std::string msg)
    {
        std::cout << "t1 says: "<< msg << std::endl;
    }
};

int main()
{
    std::string s = "Let's enjoy CSCI-4610/5610";
    Fctor fct;
    std::thread t1(fct, s); 
    try
    {
        std::cout << "from main: " << s << std::endl;
    }
    catch (...)
    {
        t1.join();
        throw;
    }

    t1.join();
    return 0;
}