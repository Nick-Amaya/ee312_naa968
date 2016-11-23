
#ifndef _linkedlist
#define _linkedlist

#include <stdio.h>
#include <stdlib.h>

// Node struct needed to be outside of class in order for getHead()
// to be able to return a Node_t *.

typedef struct node {
  int value;
  struct node * next;
} Node_t;

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  void addToListAtPosition(int position, int value);
  void addToHead(int value);
  void appendToList(int value);

  void removeFromListAtPosition(int position);
  void removeFromHead();
  void removeFromEnd();

  int find(int value);
  void reverseList();

  int getListLength();
  Node_t * getHead();

  void print();

private:
  Node_t * head;
  int listLength;
};

#endif
