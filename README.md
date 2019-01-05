# Tech Test for Smartmatic by Ítalo Muñoz

### Build 
* cmake . && make clean all
<br>or<br>
* g++ -ggdb -O0 -Wall -std=c++11 -I. *.cpp -pthread -o SMTTest1


### Run
./SMTTest1 \<inPath\> \<outPath\> \<sortAlgorithm:{InsertionSort, MergeSort, QuickSort}\>

### Why such sort algorithms
* InsertionSort: Because it's one of the simplest. Easy to follow.(1)
* MergeSort: Because is one of the fastest, and it's well known. It requires more memory than other fast sort algorithms. Worst case: O(n*log(n)) (2)
* QuickSort: Because is one of the fastest, and probably, the most popular among them, however, it's not always the fastest. Worst case: O(n^2) (3)

(1) Good and easy to follow solution as long as data amount remains "low".
<br>
(2) Good solution in terms of performance (time complexity), not that good in terms of memory (space complexity). Not that easy to follow compared to (1),(3).
<br>
(3) Good but not the best solution in terms of performance (time complexity), good in terms of memory (space complexity). But much easier to follow than (2).

