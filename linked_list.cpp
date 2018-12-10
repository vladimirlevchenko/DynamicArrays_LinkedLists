#include <iostream>
using namespace std;
//a singly linked list

struct Node{
  int value;
  Node* next;

  Node(int n) {
    value = n;
    next = nullptr;
  }

  Node(int n, Node* p) {
    value = n;
    next = p;
  }

};

class LinkedList{
private:
  Node* head;
  Node* tail;
  int size = 0;

  Node* get_node(int index){
    if (index<0 or index>=size){
      throw range_error("Index ouf of range");
    }

    Node* current = head;
    for (int i=0; i<index; i++){
      current = current->next;
    }

    return current;
  }


public:
  LinkedList(){
    head = nullptr;
    tail = nullptr;
  }

  int length() {
    return size;
  }

  void append(int val){
    if (head == nullptr){
      head = new Node(val);
      size+=1;
      return;
    }

    //Iterating to the end of the list without changing the head pointer
    Node* current = head;
    while (current->next != nullptr){
      current = current->next;
    }

    //Adding the value to the end of the list
    current->next = new Node(val);
    size+=1;
  }

  void print(){
    Node* current = head;
    cout << "[";
    while (current->next != nullptr){
      cout << current->value;
      cout << ",";
      current = current->next;
    }
    cout << current->value << "]" << endl;
  }

  ~LinkedList(){
    Node* current;
    Node* next;
    current = head;

    while (current != nullptr){
      next = current->next;
      delete current;
      current = next;
    }
  }

  int& operator[](int index){
    return get_node(index)->value;
  }

  void insert(int val, int index){
    if (index == 0){
      head = new Node(val,head);
      return;
    }

    Node* prev = get_node(index-1);
    Node* next = prev->next;
    prev->next = new Node(val, next);
    size+=1;
  }

  void remove(int index){
    Node* current = head;
    if(index==0){
      head = current->next;
      return;
    }

    for (int i=1; i<index; i++){
      current = current->next;
    }

    Node* current2 = current->next; //current2 is the element we want to remove
    current->next = current2->next;
    delete current2;
    size-=1;
  }

  int pop(int index){
    Node* prev = get_node(index-1); //get node of the element before the one we want to "pop"
    Node* current = prev->next;
    int value = current->value;
    prev->next = current->next; //excludes the element we want to "pop" from the linked list
    delete current;
    size-=1;
    return value;
  }

  void pop(){
    Node* prev = get_node(size-2); //get node of the second last element
    Node* current = prev->next;
    prev->next = nullptr; //makes the second last element the last element
    size-=1;
  }

};

int main(){
  LinkedList numbers;
  numbers.append(1);
  numbers.append(2);
  numbers.append(3);
  numbers.append(5);
  numbers.append(6);
  cout << "Initial list:" << endl;
  numbers.print();

  numbers.insert(4,3);
  numbers.insert(7,6);
  cout << "List after inserting two elements:" << endl;
  numbers.print();

  cout << "List after removing index 2:" << endl;
  numbers.remove(2);
  numbers.print();

  cout << "List after poping element with index 4 and the last element:" << endl;
  numbers.pop(4);
  numbers.pop();
  numbers.print();


  cout << "The length of the list is now " << numbers.length() << endl;


  return 0;
}
