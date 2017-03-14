# QuickSortC
Implements QuickSort in C, tests it for correctness, measures performance and defines totality for the floating point standard.

## Algorithm
The sorting algorithm uses the Hoare partition scheme and implements a custom comparitor.
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


