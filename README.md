# basics.cpp
A collection of data structures and related algorithms demonstrating understanding of basic concepts of programming theory. 

# Content

## Static array
An array of fixed size determined at compilation. Equivalent of std::array.

### Algorithmic complexity: 
Insertion: N/A  
Deletion: N/A  
Access: O(1)  
Search: O(N) if the array is unsorted  
Sort: The sort algorithm chosen for this data structure is insertion sort  
&ensp;&ensp;&ensp;Time: O(N) in best case, O(N^2) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(1) auxiliary  

[code](https://github.com/de-passage/basics.cpp/blob/master/include/static_array.hpp)



## Dynamic array
An array of variable size determined during execution. Equivalent of std::vector. 
The specificity of an array over a list is the access in constant time of random elements. However the representation in memory (aligned block of addresses) makes it so that adding elements passed the end of the currently allocated block requires a new allocation and the copy of the content of the array to the new address block which is inherently an O(N) operation in time. To sidestep the problem we store both a size (the number of elements in the array) and a capacity (the size of the array in memory), and as the number of elements exceeds the available space, we allocate a new array significantly bigger than the current one to accomodate later insertions. The factor chosen here is (N + 1) * 2. As the array grows in memory, exponentialy less operations are needed to insert new elements, making the time complexity of adding new elements at the end of the array leaning to O(1), or amortized constant time.

### Algorithmic complexity: 
Insertion: O(1) at the end, O(N) at random index  
Deletion: O(1) at the end, O(N) at random index  
Access: O(1)  
Search: O(N) if the array is unsorted  
Sort: The sort algorithm here is quicksort  
&ensp;&ensp;&ensp;Time: O(N*log(N)) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(log(N)) auxiliary  

[code](https://github.com/de-passage/basics.cpp/blob/master/include/dynamic_array.hpp)



## Single linked list
The singled linked list is a straightforward data structure: a value and a pointer to the next element in the list. This entails that the list can only be iterated forward from any given element, but also that inserting elements at random positions in the list can be done in constant time, provided a pointer to the position before which the new element is to be inserted is available. This makes the single linked list a very space efficient implementation for LIFO (last in first out) stacks.

### Algorithmic complexity: 
Insertion: O(1) with appropriate pointer  
Deletion: O(1) with appropriate pointer  
Access: O(N) at random index, O(1) at beginning  
Search: O(N)  
Sort: Bubble sort is used here.  
&ensp;&ensp;&ensp;Time: O(N) in best case, O(N^2) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(1) auxiliary  

[code](https://github.com/de-passage/basics.cpp/blob/master/include/single_linked_list.hpp)



## Double linked list
The double linked list is similar to the single linked list, with the only difference that every link stores an additional pointer to the previous element in the list. This allows the list to be iterated backward from any element in the list and justifies keeping readily available both the first and the last elements. As a result this data structure is an apt implementation for a FIFO (first in first out) queue.

### Algorithmic complexity: 
Insertion: O(1) with appropriate pointer  
Deletion: O(1) with appropriate pointer  
Access: O(N) at random index, O(1) at beginning or end  
Search: O(N)  
Sort: Here, heapsort is used  
&ensp;&ensp;&ensp;Time: O(N*log(N)) in average, O(N^2) in worst case  
&ensp;&ensp;&ensp;Space: O(N) auxiliary  

[code](https://github.com/de-passage/basics.cpp/blob/master/include/double_linked_list.hpp)



## Balanced Binary Tree
A balanced binary tree is a special kind of tree where each node contains exactly two children and the depth of any given branch is about the same (in this case the difference is never bigger than 2). These structures can be implemented to be sorted by default which garantees than subsequent search operations will perform at most in O(log(N)). There are a lot of different possible implementations for balanced binary search trees, the one presented here is an AVL tree, which stores in each node the unbalance between its left and right branch and rebalances itself as needed on insertions and deletions. Although theoretically operarating with the complexity indicated below, in practice the constant rebalancing of the tree can make it slower than other possible implementations when a lot of insertions/deletions are performed.

### Algorithmic complexity: 
Insertion: O(log(N))  
Deletion: O(log(N))  
Access: O(log(N)), access and search are the same operation  
Search: O(log(N)), access and search are the same operation  
Sort: N/A, already sorted

[code](https://github.com/de-passage/basics.cpp/blob/master/include/balanced_binary_tree.hpp)



## Hash table
The hash table, also called dictionary, is a structure in which elements are stored according to a hash function, a function transforming its input in an unsigned integer. The collected hash is then constrained to a range corresponding to an address block in memory and the element is then stored at the appropriate address. A hash function is typically required to operate in constant time, and the underlying array allowing random access in constant time to its elements, a hash table theoretically performs most operations in constant time. However in practice it can be difficult to provide constant time hash functions and an array of appropriate size to significantly avoid collisions (instances where two different elements share the same hash). In this case we deal with such collisions simply by storing the various possibilities in a linked list, which is likely to degrade performances.

### Algorithmic complexity: 
Insertion: O(1) amortized in average, O(N) in worst case  
Deletion: O(1) amortized in average, O(N) in worst case  
Access: O(1) amortized in average, O(N) in worst case, access and search are the same operation  
Search: O(1) amortized in average, O(N) in worst case, access and search are the same operation  
Sort: N/A, sorting a hash table means converting it to a different data structure

[code](https://github.com/de-passage/basics.cpp/blob/master/include/hash_table.hpp)




Note: No optimization effort has been made and the present classes can in no way be considered production ready.
