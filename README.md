# basics.cpp
A collection of data structures and related algorithms demonstrating understanding of basic concepts of programming theory. 

# Content

## Static array
An array of fixed size determined at compilation. Equivalent of std::array.

### Algorithmic complexity: 
Insertion: N/A  
Deletion: N/A  
Access: O(1)  
Search: O(N)  
Sort: The sort algorithm chosen for this data structure is insertion sort  
&ensp;&ensp;&ensp;Time: O(N) in best case, O(N^2) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(1) auxiliary  

## Dynamic array
An array of variable size determined during execution. Equivalent of std::vector. 
The specificity of an array over a list is the access in constant time of random elements. However the representation in memory (aligned block of addresses) makes it so that adding elements passed the end of the currently allocated block requires a new allocation and the copy of the content of the array to the new address block which is inherently an O(N) operation in time. To sidestep the problem we store both a size (the number of elements in the array) and a capacity (the size of the array in memory), and as the number of elements exceeds the available space, we allocate a new array significantly bigger than the current one to accomodate later insertions. The factor chosen here is (N + 1) * 2. As the array grows in memory, exponentialy less operations are needed to insert new elements, making the time complexity of adding new elements at the end of the array leaning to O(1), or amortized constant time.

### Algorithmic complexity: 
Insertion: O(1) at the end, O(N) at random index  
Deletion: O(1) at the end, O(N) at random index  
Access: O(1)  
Search: O(N)  
Sort: The sort algorithm here is quicksort  
&ensp;&ensp;&ensp;Time: O(N*log(N)) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(log(N)) auxiliary  

## Single linked list
The singled linked list is a straightforward data structure: a value and a pointer to the next element in the list. This entails that the list can only be iterated forward from any given element, but also that inserting elements at random positions in the list can be done in constant time, provided a pointer to the position before which the new element is to be inserted is available. This makes the single linked list a very space efficient implementation for LIFO (last in first out) stacks.

### Algorithmic complexity: 
Insertion: O(1) with appropriate pointer  
Deletion: O(1) with appropriate pointer  
Access: O(N)  
Search: O(N)  
Sort: Bubble sort is used here.  
&ensp;&ensp;&ensp;Time: O(N) in best case, O(N^2) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(1) auxiliary  

## Double linked list
The double linked list is similar to the single linked list, with the only difference that every link stores an additional pointer to the previous element in the list. This allows the list to be iterated backward from any element in the list and justifies keeping readily available both the first and the last elements. As a result this data structure is an apt implementation for a FIFO (first in first out) queue.

### Algorithmic complexity: 
Insertion: O(1) with appropriate pointer  
Deletion: O(1) with appropriate pointer  
Access: O(N)  
Search: O(N)  
Sort: Here, heapsort is used  
&ensp;&ensp;&ensp;Time: O(N*log(N)) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(N) auxiliary  


No optimization effort has been made and the present classes can in no way be considered production ready.
