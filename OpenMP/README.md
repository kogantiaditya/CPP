## Commands

* Basic run:

  ```sh
  g++ -fopenmp -g <file> -o <file>
  ```
  ```sh
  ./<file>
  ```

### A05

* setting OMP_NUM_THREADS in terminal evn and run (file-name: prime_count_omp.cpp):

  ```sh
  export OMP_NUM_THREADS= <value>
  ```
  ```sh
  g++ -fopenmp -g prime_count_omp.cpp -o prime_count_omp
  ```
  ```sh
  ./prime_count_omp
  ```
