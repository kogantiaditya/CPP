#include <iostream>
#include <omp.h>

int main(){
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        std::cout<<"Hello Easy c++ project" << id << std::endl;
    }
    return 0;
}
