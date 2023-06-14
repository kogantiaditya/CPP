# include<iostream>
# include<thread>

void hello()
{
    std::cout<<"Hello concurrent world"<<std::endl;
}

int main()
{
    std::thread t1(hello);
     std::thread t2(hello);
     t1.detach();
     if(t1.joinable())
       t1.join();
    else
   std:: cout<<"not joinable"<<"\n";
}