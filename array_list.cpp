#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <math.h>

using namespace std;

class ArrayList
{
public: // declaration of the class method
    int capacity;
    int *data = NULL; //pointer to the first element in the array
    int grow;
    int size;

public: // definition of the constructor
    ArrayList (){
        size = 0;
        capacity = 1;
        grow = 2;
        data = new int[capacity];
      }

    int length(){
        return size;
    }

    void append (int n) {
        if (size >= capacity) {
            resize();
        }
        data[size] = n;
        size += 1;
    }

    void resize() {
        capacity *= grow;
        int *tmparray = new int[capacity];
        for (int i=0; i<size; i++) {
            tmparray[i] = data[i];
            capacity *= grow;
        }
        delete[] data;
        data = tmparray;
    }

    ArrayList(vector<int> vec) {
        capacity = 1;
        size = 0;
        grow = 2;
        data = new int[capacity];
        for (int i: vec){
            append(i);
            capacity *= grow;
        }
    }
    ~ArrayList (){ // addition of the destructor
        delete[] data;
    }

    int& operator[] (int i) {
        if (0 <= i and i < size) {
          return data[i];
        } else {
          throw out_of_range("IndexError");
        }
    }

    void insert(int val, int index) {
        int *tparr = new int[capacity];
        if (index >= size+1) {
          throw out_of_range("IndexError");
        }
        if (index == 0) {
            size += 1;
            tparr[0] = val;
            for (int i=1; i<size; i++) {
                tparr[i] = data[i-1];
            }
            delete[] data;
            data = tparr;
        } else {
            size += 1;
            for (int i=0; i<index; i++) {
                tparr[i] = data[i];
            }
            tparr[index] = val;
            for (int i = index+1; i<size; i++) {
                tparr[i] = data[i-1];
            }
            delete[] data;
            data = tparr;
        }
    }

    void remove(int index) {
        int *tparr2 = new int[capacity];
        if (index == 0) {
            for (int i=0; i<size-1; i++) {
                tparr2[i] = data[i+1];
            }
            size -= 1;
            delete[] data;
            data = tparr2;
        } else {
            for (int i=0; i<index; i++) {
                tparr2[i] = data[i];
            }
            size -= 1;
            for (int i=index; i<size; i++) {
                tparr2[i] = data[i+1];
            }
            tparr2[size] = data[size+1];
            delete[] data;
            data = tparr2;
        }
        int cap = capacity * 0.25;
        int DesiredCap = pow(2, size);
        if (DesiredCap < cap) {
            shrink_to_fit();
        }

    }

    int pop(int index) {
        int tmp = data[index]; //store removed value in the old list
  //      size += 1;
        remove(index);
        int cap = capacity * 0.25;
        int DesiredCap = pow(2, size);
        if (DesiredCap < cap) {
            shrink_to_fit();
        }
        return tmp;
    }

    int pop() {
        return data[size-1];
    }

    void print(){
      cout << "[ ";
      for (int i=0; i<size-1; i++) {
          cout << data[i];
          cout << ", ";
      }
      cout << data[size-1] << " ]" << endl;

    }

    void shrink_to_fit(){
        capacity = pow(2, size);
    }
};

//------------ Primes -------------------------------

bool is_prime(int n) {
    if (n < 3)
        return false;

    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// --------------------------------------------------
// ------- Test functions ----------------------

void test_zerolength() {
    ArrayList testlist;
    assert(testlist.length() == 0);
}
void test_append() {
    ArrayList testlist;
    testlist.append(1);
    assert(testlist.length() == 1);
}

void test_primes() {
    std::vector<int> expected {3, 5, 7, 11, 13};
    ArrayList prime;
    for (int i = 0; i < 30; i++) {
        if (is_prime(i) == true && prime.length() < 5) {
            prime.append(i);
        }
    }
    for (int i = 0; i<expected.size(); i++) {
        assert(expected[i] == prime[i]);
    }
}

void test_insert() {
    std::vector<int> expected {3, 11, 5, 80, 200, 3, 11};
    ArrayList teslist({3, 11, 5, 80, 3, 11});

    teslist.insert(200, 4);
    for (int i=0; i<expected.size(); i++) {
        assert(expected[i] == teslist[i]);
    }
}

void test_insert_end() {
    std::vector<int> expected {3, 11, 5, 80, 3, 11, 100};
    ArrayList teslist({3, 11, 5, 80, 3, 11});

    teslist.insert(100, 6);
    for (int i=0; i<expected.size(); i++) {
        assert(expected[i] == teslist[i]);
    }
}

void test_remove() {
    std::vector<int> expected {1, 5, 80};
    ArrayList teslist({1, 6, 5, 80});

    teslist.remove(1);
    for (int i=0; i<expected.size(); i++) {
        assert(expected[i] == teslist[i]);
    }
    assert(expected.size() == teslist.length());
}

void test_popint() {
    std::vector<int> expected {10, 3, 800};
    ArrayList teslist({10, 3, 2, 800});

    teslist.pop(2);
    for (int i=0; i<expected.size(); i++) {
        assert(expected[i] == teslist[i]);
    }
    assert(expected.size() == teslist.length());
}

void test_pop() {
    int expected = 3;
    ArrayList teslist({11, 23, 1, 80, 18, 3});

    teslist.pop();
    assert(teslist.pop() == expected);
}

void test_shrink() {
    int capacityExpected = pow(2, 2);
    ArrayList teslist({11, 23, 1, 80, 18, 3});

    teslist.remove(0);
    teslist.remove(0);
    teslist.remove(0);
    teslist.remove(0);
    teslist.shrink_to_fit();
    assert(teslist.capacity == capacityExpected);
}

void test_autoshrinking() {
    std::vector<int> expected {3, 4};
    int capacityExpected = pow(2, expected.size()); //7

    ArrayList teslist({10, 3, 8, 1, 2, 3, 4});

    teslist.pop(0);
    teslist.pop(0);
    teslist.pop(0);
    teslist.pop(0);
    teslist.pop(0);

    for (int i=0; i<expected.size(); i++) {
        assert(expected[i] == teslist[i]);
    }
    assert(capacityExpected == teslist.capacity);
}

int main() {
    ArrayList arrl;

    test_zerolength();
    test_append();
    test_primes();
    test_insert();
    test_insert_end();
    test_remove();
    test_popint();
    test_pop();
    test_shrink();


    ArrayList primes({6, 6, 5, 80, 3,110});
    primes.print();

    cout << "Size before insert: " << primes.length() << endl;
    cout << "Capacity before insert: " << primes.capacity << endl;
    cout << "-----------insert test--------" << endl;
    cout << "List after insert: " << endl;
    primes.insert(200, 6);
    primes.print();
    cout << "Size after insert: " << primes.length() << endl;

    cout << "-----------REMOVE test--------" << endl;
    cout << "List before remove: " << endl;
    primes.print();
    cout << "Size before remove: " << primes.length() << endl;
    cout << "List after remove: " << endl;
    primes.remove(0);
    primes.remove(1);
    primes.remove(1);
    primes.print();
    cout << "Size after remove: " << primes.length() << endl;

    cout << "-----------pop(int) test--------" << endl;
    cout << "List before pop(int): " << endl;
    primes.print();
    cout << primes.pop(2) << endl;
    cout << "List after pop(int): " << endl;
    primes.print();
    cout << "Size after pop(int): " << primes.length() << endl;

    cout << "-----------pop() test--------" << endl;
    cout << "List before pop(): " << endl;
    primes.print();
    cout << "List after pop(): " << primes.pop() << endl;
    primes.print();

    cout << "-----------Final capacity--------" << endl;
    cout << "Capacity: " << primes.capacity << endl;

    cout << "-----------New capacity--------" << endl;
    primes.shrink_to_fit();
    cout << "New capacity: " << primes.capacity << endl;

    return 0;
}
