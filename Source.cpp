/**
 Name: Grace K. P. Barros     
 Instructor: Arezoo Ariafar
 Date: July 4th - 2023
            
*/

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_WASTED_MEMORY = 10;
const int MAX_CSTRING_SIZE = 50;


/**Container in which order of items doesn't matter, no duplicate values exist.*/
template<typename T = int>
class Set
{
public:
    //Constructors and Destructors
    Set(); //default constructor
    Set(const T[], int);
    Set(const Set<T>&); //copy constructor
    ~Set();

    //Methods
    void insert(const T); //insert 1 item
    void insert(const T[], int); //insert array of itens
    /** Verify if there is the input parameter on the Set.
     * Since Set order does not matter, the Set is sorted
    */
    bool membership(const T) const;
    bool remove(const T); //remove 1 item
    bool isEmpty() const;
    bool isSubset(const Set<T>&) const;
    bool isSuperset(const Set<T>&) const;
    Set<T> subtraction(const Set<T>&) const;
    Set<T> addition(const Set<T>&) const;
    Set<T> intersection(const Set<T>&) const;
    bool isEqual(Set<T>&);

    void display() const;

    //Getters
    unsigned int getSize() const;
    unsigned int getId() const;

private:
    unsigned int size;
    unsigned int capacity;
    unsigned int id;
    T* start;

    static unsigned int trackerId;

    void sort(); //used internally to make easier to other required functions
    void shrunk(); //used internally when it is wasting more memory than max
    void expand(int howMuch = MAX_WASTED_MEMORY); //used internally when needs more space than capacity
};

template<typename T>
unsigned int Set<T>::trackerId = 1;
////////////////////////////////////how to make 3 available after 5 to 8 are created for example

//Constructors and Destructors
template<typename T>
Set<T>::Set() {
    size = 0;
    capacity = MAX_WASTED_MEMORY;
    start = new T[capacity];
    id = trackerId++;

    cout << "The object type " << typeid(T).name() << " and id " << id << " was created." << endl;
};

template<typename T>
Set<T>::Set(const T param[], int size) {
    this->size = 0;
    capacity = size;
    start = new T[capacity];
    id = trackerId++;

    for (int i = 0; i < size; i++){
        if (!this->membership(param[i])) {
            start[this->size++] = param[i];
        }
    }

    if (capacity - size > MAX_WASTED_MEMORY)
        shrunk();

    cout << "The object type " << typeid(T).name() << " and id " << id << " was created." << endl;
};

template<typename T>
Set<T>::Set(const Set<T>& original) {
    size = original.getSize();
    capacity = size + MAX_WASTED_MEMORY / 2;
    start = new T[capacity];
    id = trackerId++;

    for (int i = 0; i < size; i++) {
        start[i] = original.start[i];
    }
    cout << "The object type " << typeid(T).name() << " and id " << id << " was created." << endl;

};

template<typename T>
Set<T>::~Set() {
    ///////////////////////How make id available again
    delete[] start;
    cout << "The object type " << typeid(T).name() << " and id " << id << " was destroyed." << endl;
};

//Getters and Setters
template<typename T>
unsigned int Set<T>::getSize() const {
    return size;
};

template<typename T>
unsigned int Set<T>::getId() const {
    return id;
};

//Private Methods
template<typename T>
void Set<T>::sort() {
    for (int j = 0; j < size; j++) {
        T smaller = start[j];
        int smallerIndex = j;
        for (int i = j; i < size; i++) {
            if (start[i] < smaller) {
                smaller = start[i];
                smallerIndex = i;
            }
        }
        T temp = start[j];
        start[j] = smaller;
        start[smallerIndex] = temp;
    }
};

template<typename T>
void Set<T>::shrunk() {
    capacity = size + MAX_WASTED_MEMORY / 2;
    T* temp;
    temp = new T[capacity];
    for (int i = 0; i < size; i++)
        temp[i] = start[i];

    delete[] start;
    start = temp;
};

template<typename T>
void Set<T>::expand(int howMuch) {
    capacity += howMuch;
    T* temp = new T[capacity];

    for (int i = 0; i < size; i++)
        temp[i] = start[i];

    delete[] start;
    start = temp;
};

//Public Methods
template<typename T>
void Set<T>::insert(const T item) {
    if (!this->membership(item)) {
        if (capacity - size > 0)
            start[size++] = item;
        else {
            this->expand();
            start[size++] = item;
        }
    }
};

template<typename T>
void Set<T>::insert(const T listOfItens[], int listSize) {
    for (int i = 0; i < listSize; i++)
        this->insert(listOfItens[i]);
};

template<typename T>  //check existence
bool Set<T>::membership(const T item) const{
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (start[i] == item)
                return true;
        }
        return false;
    }
    return false;
};

template<typename T>
bool Set<T>::remove(const T item) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (start[i] == item) {
                for (int copy = i++; i < size; i++,copy++) {
                    start[copy] = start[i];
                }
                --size;
                if (capacity - size > MAX_WASTED_MEMORY) {
                    this->shrunk();
                }
                return true;
            }
        }
        return false;
    }
    return false;
};

template<typename T>
bool Set<T>::isEmpty() const {
    return size == 0;
};

/**Implement a method that accepts another set as its input parameter and checks if the current set is a subset of the input set.
Set "A" is a subset of set "B" if all its items of "A" are included in "B"*/
template<typename T>
bool Set<T>::isSubset(const Set<T>& setB) const {
    for (int i = 0; i < size; i++) {
        if (!setB.membership(start[i]))
            return false;
    }
    return true;
};

/**Implement a method that accepts another set as its input parameter and checks if the current set is a superset of the input set.
Set "A" is a superset of set "B" if all its items of "B" are included in "A".*/
template<typename T>
bool Set<T>::isSuperset(const Set<T>& setB) const {
    for (int i = 0; i < setB.size; i++) {
        if (!this->membership(setB.start[i]))
            return false;
    }
    return true;
};

template<typename T>
Set<T> Set<T>::subtraction(const Set<T>& setB) const{
    Set<T> result = Set();
    for (int i = 0; i < size; i++) {
        if (!setB.membership(start[i]))
            result.insert(start[i]);
    }
    return result;
};

template<typename T>
Set<T> Set<T>::addition(const Set<T>& setB) const{
    Set<T> result = Set();
    for (int i = 0; i < setB.size; i++) {
        result.insert(setB.start[i]);
    }
    for (int i = 0; i < size; i++) {
        result.insert(start[i]);
    }
    return result;
};

template<typename T>
Set<T> Set<T>::intersection(const Set<T>& setB) const {
    Set<T> result = Set(); 
    for (int check = 0; check < size; check++) {
        if (setB.membership(start[check]))
            result.insert(start[check]);
    }
    return result;
};

template<typename T>
bool Set<T>::isEqual( Set<T>& setB) {
    if (size != setB.size) {
        return false;
    }
    else {
        this->sort();
        setB.sort();
        for (int i = 0; i < size; i++) {
            if (start[i] != setB.start[i])
                return false;
        }
    }
    return true;
};

template<typename T>
void Set<T>::display() const {
    const string DIV = ", ";

    if (size > 0) {
        cout << "{ ";
        for (int i = 0; i < size - 1; i++) {
            cout << start[i] << DIV;

        }
        cout << start[size - 1] << " }" << endl;
    }
    else {
        cout << "{}" << endl;
    }
};


//Testing
int main() {
    //1. Create a set of type "int" and and fill it with some data read from the keyboard.
    Set<> firstExercise = Set<>::Set();
    bool delimeter = true;
    int input;
    string stopInput;
    while (delimeter) {
        cout << "Please insert an int to fill your Set<int>: ";
        cin >> input;
        firstExercise.insert(input);
        cout << "If you would like to stop, insert \"S\" or \"STOP\" below. Otherwise, type anything to keep adding items.";
        cin >> stopInput;
        if (stopInput == "STOP" || stopInput == "s" || stopInput == "S")
            delimeter = false;
    }

    cout << "Thanks! That is the Set created: ";
    firstExercise.display();

    /*2. Use the class copy constructor to create a set of type "int" as a copy of the set
    created in the previous section.*/
    Set<> copyExercise(firstExercise);
    cout << "A copy was created! Copy is displayed below." << endl;
    copyExercise.display();

    /*3. Read a C-string from the keyboard and use the proper parameterized constructor to
    create a set object of type "char" initialized by the characters included in the input string.*/
    char userString[MAX_CSTRING_SIZE];
    cout << "Please enter the string, max size " << MAX_CSTRING_SIZE << ", for Exercise three: " << endl;
    cin >> userString;
    Set<char> thirdExercise = Set<char>::Set();
    for (int len = 0; userString[len] != '\0'; len++) {
        thirdExercise.insert(userString[len]);
    }
    cout << "Thanks! That is the Set<str> created: ";
    thirdExercise.display();

    /*4. Show the ids of the three sets on the screen*/
    cout << "IDs of the Set<int> created so far: " << firstExercise.getId() << ", " << copyExercise.getId() << endl;
    cout << "IDs of the Set<str> created so far: " << thirdExercise.getId() << endl << endl << endl;

    /*5. Use proper methods of the char set object created in section 3 to identify if the
    input C-string includes all the vowels. If required, you can create more set objects.*/
    char vogais[] = "aeiou";
    Set<char> vowels(vogais, 5);
    vowels.display();
    cout << "If result is 1 (true) has all the vowels, if 0 (false) it doesn't have all the vowels." << endl << "Result: " 
        << thirdExercise.isSuperset(vowels) << " or " << vowels.isSubset(thirdExercise) << endl << endl << endl;

    /*6. Add more values to the int set created using the copy constructor and then display
    the union, intersection, and difference sets on the screen.*/
    int moreItens[10] = { -99, -88, -77, -66, -55, -44, -33, -22, -11, 1000 };
    copyExercise.insert(moreItens, 10);

    cout << "Copy exercise with more itens is: ";
    copyExercise.display();
    
    Set<> uni = firstExercise.addition(copyExercise);
    cout << "Union is: ";
    uni.display();
    
    Set<> inter = firstExercise.intersection(copyExercise);
    cout << "Intersection is: ";
    inter.display();

    Set<> dif = firstExercise.subtraction(copyExercise);
    cout << "Difference between set1 and set 2 is: ";
    dif.display();

    Set<> dif2 = copyExercise.subtraction(firstExercise);
    cout << "Difference between set2 and set 1 is: ";
    dif2.display();

    return 0;
}