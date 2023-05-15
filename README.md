# Raytracer-
# Hyper-QuickSort
This is an implementation of a parallel quicksort algorithm on a d-dimensional hypercube topology using MPI and C programming language.

## Implementation 

This parallel quicksort algorithm takes advantage of the topology of a p process hypercube connected parallel computer. Let n be the number of elements to be sorted and $p = 2^d$ be the number of processes in a d -dimensional hypercube. Each process is assigned a block of $n \over p$ elements, and the labels of the processes define the global order of the sorted sequence. The algorithm starts by selecting a pivot element, which is broadcast to all processes. Each process, upon receiving the pivot, partitions its local elements into two blocks, one with elements smaller than the pivot and one with elements larger than the pivot. Then the processes connected along the d th communication link exchange appropriate blocks so that one retains elements smaller than the pivot and the other retains elements larger than the pivot. Specifically, each process with a 0 in the d th bit (the most significant bit) position of the binary representation of its process label retains the smaller elements, and each process with a 1 in the d th bit retains the larger elements. After this step, each process in the (d - 1)- dimensional hypercube whose d th label bit is 0 will have elements smaller than the pivot, and each process in the other (d - 1)-dimensional hypercube will have elements larger than the pivot. This procedure is performed recursively in each subcube, splitting the subsequences further. After d such splits – one along each dimension – the sequence is sorted with respect to the global ordering imposed on the processes. This does not mean that the elements at each process are sorted. Therefore, each process sorts its local elements by using sequential quicksort.

<img width="695" alt="Screenshot 2023-01-14 at 11 57 45 AM" src="https://user-images.githubusercontent.com/56271967/212485147-783e7b6d-d569-4074-aae4-1db4a2e4bc3b.png">

_Grama, Ananth. Introduction to Parallel Computing. Addison-Wesley, 2013._


## Time Complexity 

The time complexity of the parallel quicksort algorithm on a d-dimensional hypercube topology is 

$$ O( {N \over P} + {{N \over P} log {N \over P}} + {{N \over P} log P} + {log^2 P} ) = O( {{N \over P} log {N \over P}} ) $$


## Build

To compile the program, 
```
  mpicc Par.c -o Par
```
  
To run the program,
```
  mpirun -np <NumberOfProcesses> Par <InputSize>
```
  
## Results 

The execution time of the sequential quick sort algorithm is compared with the execution time of the parallel d-dimensional hypercube quick sort algorithm and the speedup is recorded. A graph of speedup against input size is shown below: 

<img width="925" alt="Screenshot 2023-01-14 at 11 37 47 AM" src="https://user-images.githubusercontent.com/56271967/212483947-29802a0e-d5c8-4ccf-81f4-3318de33ff0c.png">
