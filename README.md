# QuickSortC
Piece of university coursework that implements QuickSort in C, tests it for correctness, measures performance and defines totality for the floating point standard.

## Usage
Launching the compiled .exe presents the testing menu. From there, the correctness of the algorithm can be tested, such as sorting arrays with varying sizes, handling edge cases (+/-zero, +/-infinity, NaNs with varying mantisas).
Otherwise, the program can accept command-line variables and execute functions without any further user interation, i.e.
```powershell
./Algorithms.exe -s 50                      # Generates and sorts an array of size 50 and closes
./Algorithms.exe -s 250000 -l 10            # Generates and sorts an array of size 250,000 10 times
./Algorithms.exe -s 100 -min -100 -max 100  # Generates and sorts 100 elements ranging from -100 to 100
```

## Algorithm
The sorting algorithm uses the Hoare partition scheme and implements a custom comparitor.
Pseudocode for the quicksort algorithm is as follows:
```
algorithm quicksort(array, low, high) 
    if low < high then 
        partition := partition(array, low, high) 
        quicksort(array, low, partition) 
        quicksort(array, partition + 1, high)
    end if
```
Pseudocode for the Hoare partition scheme is as follows:
```
algorithm partition(array, low, high) 
    pivot := array[low] 
    i := low – 1 
    j := high + 1 
    loop while true 
        do 
            i := i + 1 
        while compareFloat(array[i], pivot) 
        do 
            j := j – 1 
        while compareFloat(pivot, array[j]) 
        if i >= j then 
            return j 
        end if 
        swap array[i] with array[j] 
    end loop
```
Pseudocode for the comparitor is as follows:
```
algorithm compareFloat(float1, float2) 
    if float1 and float2 are both NANs then 
        return float1.mantissa < float2.mantissa 
    else if float1 is NAN then 
        return false 
    else if float2 is NAN then 
        return true 
    else if float1 and float2 are both equal to 0 then 
        return float1.sign == 1 and not float2.sign == 1 
    else 
        return float1 < float2 
    end if
```
This, along with the sorting and partitioning algorithms, is implemented in `sort.c`.

## Time Orders
The time it takes for quicksort to sort an array heavily depends on how balanced the array is.
### Best-case balance
If the array is perfectly balanced, then it will partition into two subarrays smaller than n/2. Solving a recurrance relation, the predicted time order is O(n*logn).
### Worst-case balance
If the array is perfectly inbalanced, then it will continually partition into two subarrays of size 1 and n-1. Solving a recurrance relation, the predicted time order is O(n^2).
### General performance
On average, bad splits can be absorbed by good splits, resulting in the time order O(n*logn).
### Real-world performance
Curiously, this implementation of the algorithm takes on a linear time order, as seen on the below graph.
[![Time vs elements](http://i.imgur.com/c042W9z.png)](http://i.imgur.com/c042W9z.png)


