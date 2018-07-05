
/*
  Nicholas Amaya
  naa968
  16300
  Dr. Barber
*/

#include "linkedlist.h++"

// Constructor
// Constructs an empty list.
LinkedList::LinkedList() {
  listLength = 0;
  head = NULL;
}

// Destructor
// Free any allocated nodes.
LinkedList::~LinkedList() {
  Node_t * cur, * next_node;
  cur = head;

  if(cur == NULL) return;

  next_node = cur->next;
  while(next_node != NULL) {
    free(cur);
    cur = next_node;
    next_node = next_node->next;
  }
  free(cur);
}

// Add to list functions
void LinkedList::addToListAtPosition(int position, int value) {

  if(position > listLength || position < 0) {
    printf("Error: Position out of bounds.\n");
    return;
  }

  if(position == 0) {
    this->addToHead(value);
    return;
  }

  int i = 0;
  Node_t * iterator = head;
  for(int i = 0; i < position - 1; i++) {
    iterator = iterator->next;
  }

  Node_t * new_node = (Node_t *) malloc(sizeof(Node_t));
  new_node->value = value;
  new_node->next = iterator->next;
  iterator->next = new_node;

  listLength++;
}
void LinkedList::addToHead(int value) {
  Node_t * new_node = (Node_t *) malloc(sizeof(Node_t));
  new_node->value = value;
  new_node->next = head;
  head = new_node;

  listLength++;
}
void LinkedList::appendToList(int value) {

  if(listLength == 0) {
    this->addToHead(value);
    return;
  }

  Node_t * iterator;
  for(iterator = head; iterator->next != NULL; iterator = iterator->next);

  Node_t * new_node = (Node_t *) malloc(sizeof(Node_t));
  new_node->value = value;
  new_node->next = NULL;
  iterator->next = new_node;

  listLength++;
}

// Remove from list functions
void LinkedList::removeFromHead() {

  if(head == NULL) {
    printf("Error: Trying to remove from empty list.\n");
    return;
  }

  Node_t * next_node = head->next;

  free(head);
  head = next_node;

  listLength--;
}
void LinkedList::removeFromListAtPosition(int position) {
  if(head == NULL) {
    printf("Error: Trying to remove from empty list.\n");
    return;
  }

  if(position >= listLength || position < 0) {
    printf("Error: Position out of bounds.\n");
    return;
  }

  if(position == 0) {
    this->removeFromHead();
    return;
  }

  Node_t * cur = head;
  Node_t * prev = NULL;

  int i = 0;
  while(cur != NULL && i < position) {
    prev = cur;
    cur = cur->next;
    i++;
  }

  prev->next = cur->next;
  free(cur);

  listLength--;
}
void LinkedList::removeFromEnd() {
  if(head == NULL) {
    printf("Error: Trying to remove from empty list.\n");
    return;
  }

  Node_t * prev, * cur;
  for(prev = NULL, cur = head; cur->next != NULL; prev = cur, cur = cur->next);

  if(prev == NULL) {
    head = NULL;
  } else {
    prev->next = cur->next;
  }

  free(cur);
  listLength--;
}

// List methods.
//returns true or false depending on if we found the specified value in the list.
int LinkedList::find(int value) {
  for(Node_t * iterator = head; iterator != NULL; iterator = iterator->next) {
    if(iterator->value == value) {
      return 1;
    }
  }
  return 0;
}
void LinkedList::reverseList() {

  // if list has less than two nodes then the list is the same forwards as it is
  // backwards. Nothing more needs to be done.
  if(head == NULL || head->next == NULL) {
    return;
  }

  // if list has only two nodes, you only need to bring the last node to the front
  // and you have reversed the list. (swap the first and the last nodes).
  if(listLength == 2) {
    Node_t * first = head;
    Node_t * last = head->next;

    head = last;
    last->next = first;
    first->next = NULL;
    return;
  }

  // Final case: listLength > 2. In this case you need to use the algorithm as follows:
  // 1. Initialize a pointer to point to head. (call it first) and a pointer to point to the
  // last node. (call it last).
  // 2. swap the node first is pointing to with the node last is pointing to.
  // 3. increment first to point to the next node in the list. Decrement last to point to the
  // node right behind it.
  // 4. Repeat steps 2 and 3 until you've reached the half way point of the list.
  // 5. At this point you are done. The list has been reversed.

  // Special Cases:
  //   On the outtermost swap, when first == head, instead of just swapping the first and the last
  //   nodes you must also change head to point to the last node so the list knows where the new
  //   reversed list will start. This is why the algroithm looks complicated with the if-else
  //   statements thrown in there.
  //
  //   If the list has an even number of nodes, the innermost swap will be a litte different
  //   because sec will equal last and secToLast will equal first. This is why the special
  //   "if(length == 2)" case is thrown in there. To deal with lists that have an even number
  //   of nodes.

  Node_t * first = head;
  Node_t * sec = head->next;
  Node_t * last = head;
  Node_t * secToLast = NULL;
  Node_t * tmp;

  for(int length = listLength; length >= 2; length -= 2) {

    for(int i = 0; i < length - 1; i++) {
      secToLast = last;
      last = last->next;
    }

    if(length == 2) {
      first->next = last->next;
      last->next = first;
      tmp->next = last;
      continue;
    }

    first->next = last->next;
    last->next = sec;
    if(length == listLength)
      head = last;
    else
      tmp->next = last;
    secToLast->next = first;

    if(length == listLength)
      tmp = head;
    else
      tmp = tmp->next;
    first = sec;
    sec = sec->next;
    last = first;
    secToLast = NULL;
  }

}

//List accessors
Node_t * LinkedList::getHead() {
  return head;
}
int LinkedList::getListLength() {
  return listLength;
}

// Print out the Linked List in a readable format
// 20 nodes per line
void LinkedList::print() {
  printf("HEAD -> ");

  int i = 0;
  for(Node_t * k = head; k != NULL; k = k->next) {
    printf("[%d] -> ", k->value);
    if(i % 10 == 9) printf("\n");
    i++;
  }
  printf("NULL\n");
}
