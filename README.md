Runtime Analysis Table (Big O)
 
Operation: Load File and Create Course Objects
---------------------------------------------------------------
Data Structure        | Cost per Line | Executions | Worst-Case Big O
---------------------------------------------------------------
Vector                |         1      |        n  |      O(n)
Hash Table            |         1      |        n  |      O(n)
Binary Search Tree    |      log n     |        n  |      O(n log n)


Runtime Evaluation
The runtime evaluation focuses on the operations required to load the input file, parse each line, and create the corresponding course objects. Since each course occupies one line in the file, all three data structures must process n lines. For the vector implementation, each line of data is read and appended to the end of the vector, which is an O(1) operation. Because this constant-time insertion occurs n times, the total runtime for file loading and object creation is O(n). The hash table implementation also provides a constant-time average insertion. As each course object is created, it is inserted into the hash table using the course number as the key. Since this insertion occurs once per course, the resulting runtime for loading the file is also O(n), assuming the hash function distributes keys evenly.
The binary search tree exhibits slightly different behavior. For each course, the program must follow the tree’s structure to locate the correct position for insertion. In a balanced tree, this traversal requires O(log n) comparisons, making the total file-loading runtime O(n log n). This is more expensive than the vector and hash table for initial loading, but the BST compensates with superior in-order traversal performance when printing the sorted list of courses. It is important to note that the BST may degrade to O(n) insertion times if the input data is already sorted, though this evaluation assumes average-case balanced behavior unless otherwise stated.
Overall, the vector and hash table provide the fastest loading times, while the BST requires more processing during insertion but delivers future benefits in sorted traversal and organization.

Recommendation
Based on the requirements of the ABCU advising application and the results of the runtime evaluation, the binary search tree is the strongest choice for the final implementation. Although the BST does not load data as quickly as a vector or hash table, it uniquely satisfies both major advisor needs in a single structure. First, it maintains natural alphanumeric ordering through its internal node arrangement, allowing the program to print all courses in sorted order using a simple in-order traversal without requiring a separate sorting step. Second, it provides more efficient search capabilities than a vector and avoids the unordered nature of a hash table. While the hash table is ideal for quick lookup of an individual course, its inability to maintain order adds additional work when generating the sorted list of all courses.
The BST offers a balanced combination of efficiency, organization, and flexibility. Its O(log n) average search performance meets the requirement of retrieving course details quickly, and its inherent ordering directly supports printing the course catalog in ascending alphanumeric sequence. Despite having a more complex implementation and a potentially higher loading cost, the BST provides the clearest long-term advantages for both functionality and maintainability. For these reasons, the binary search tree is recommended as the data structure to use in the final coded version of the ABCU course-planning program.



