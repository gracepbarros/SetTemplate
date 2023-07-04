#  Name: Grace K. P. Barros \t Instructor: Arezoo Ariafar
Date: June 27 - 2023

## SetTemplate
This repo is a demonstration of some abilities I have learned in C++ course.   

## What is a "Set"
A set is a container in which the order of items does not matter and no duplicate values exist.  

### Set characteristics
- Set will be a class template. So it can be created with int, char, double...
- Each class Set<> has a global shared ID.
- There is a limit for wasted memory on the dynamic memory allocation, this is represented by a global constant MAX_WASTED_MEMORY  

### Set attributes
- Size  
: the actual size of the Set, anything extra, even though allocate, is garbage.
- Capacity  
: the capacity of the memory, or the limits for the memory allocation.
: If more space than capacity is needed, shrunk or expand internal methods need to be called.
- Id  
: The unique ID for each type of that object. It starts with 1.
- Start  
: The pointer for the start point of memory allocated for that Set object

### Set methods
- Shrunk and Expand  
: Utilize dynamic memory allocation for your set and consider expanding and shrinking your set to use memory efficiently.
: MAX_WASTED_MEMORY should be considered in all the methods of the class and if required the allocated memory should be shrunk or expanded.
- No-arg Constructor  
: A no-arg constructor that creates an empty set.
- Parameterized Constructor  
: Overload of the no-arg constructor with a parameterized constructor with two input parameters: an array of items and the size of the array.
: This method creates a set with a capacity equal to the size of the array and includes the unique values included in the input array in the created object.
- Copy Constructor  
: A constructor that copies all arguments from another instance, except the ID that is unique. 
- Destructor  
: Since Set is dynamically allocated, a destructor is essential to avoid data lacking.
- Insert  
: Method to add one single element to the class
- Insert  
: overload of previous method, to add one array of elements to the class.
- Remove  
: Implement a method to remove a specific item from the set.
: The function returns a Boolean that shows if the removal was successful.
- isSubset  
: Implement a method that accepts another set as its input parameter and checks if the current set is a subset of the input set.
: Set "A" is a subset of set "B" if all its items of "A" are included in "B". 
- isSuperset  
: Implement a method that accepts another set as its input parameter and checks if the current set is a superset of the input set.
: Set "A" is a superset of set "B" if all its items of "B" are included in "A".
- Subtraction  
: Implement a method that accepts another set as its input parameter and calculates the result of subtracting the input set from the current set.
: "A - B" is a set including all the items of "A" that do not exist in "B".
- Addition  
: Implement a method that accepts another set as its input parameter and calculates the union of the input set with the current set.
: The union of set "A" and set "B" is a set including all the items that are either in "A" or "B" or both.
- Intersection  
: Implement a method that accepts another set as its input parameter and calculates the intersection of the input set with the current set.
: The intersection of set "A" and set "B" is a set including all the items that are common in both sets.
- isEqual  
: Implement a method that compares the current set with an input set for equality.
: Two sets are equal if they both have the same length and disregarding the order, they include the same items.
- Display  
: Implement a method that displays the set on the screen. The format of the output is: {a, b, c, ...}; i.e. 
- getSize  
: getter for the size of the object.
- getId  
: getter for the Id of the object.

#### Thanks for reading! Check the .cpp file to see the implementation and tests.
