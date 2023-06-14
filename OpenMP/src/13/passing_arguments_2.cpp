#include <iostream>
#include <thread>
#include <string>

class Fctor
{
public:
    void operator()(std::string &msg)
    {
        std::cout << "t1 says: " << msg << std::endl;
        msg = "t1 somehow updated string s";
    }
};

int main()
{
    std::string s = "Let's enjoy CSCI-4610/5610";
    Fctor fct;
    std::thread t1(fct, std::ref(s)); 
    t1.join();
    std::cout << "main says: " << s << std::endl;
    return 0;
}