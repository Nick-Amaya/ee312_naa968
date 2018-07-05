
#include "polynomial.hh"

/**
 *  Main node constructor
 */
Node::Node(double v, Node *n)
{
	value = v;
	next = n;
}

/**
 *  Node Copy Costructor
 */
Node::Node(const Node& n)
{
	value = n.value;
	next = n.next;
}

/**
 *  Node Destructor
 */
Node::~Node()
{
    // No dynamically allocated memory in Node
	// so do nothing.
}

/**
 *  Poly default constructor
 */
Poly::Poly()
{
    head = NULL;
	order = -1;
}

/**
 *  Poly destructor
 */
Poly::~Poly()
{
	// printf("Deleting...\n");

	//this->print();
	// Systematically loop through Poly deleting all instances of node.
	// Note: This code is OK because deleting a NULL pointer does nothing.
	Node *iterator, *prev;
	for (iterator = head, prev = NULL; iterator != NULL; prev = iterator, iterator = iterator->next)
	{
	    delete prev;
	}
	delete prev;

	// printf("Deleted!\n");
}

Poly::Poly(const Poly& p)
{
	this->copy(p);
}

void Poly::operator= (const Poly& p)
{
	// First, free all elements of destination to ensure no memory leaks.
	this->~Poly();

	// Copy all elements to destination Poly
	this->copy(p);
}

int Poly::getOrder()
const
{
	return order;
}

Node *Poly::getHead()
const
{
    return head;
}

void Poly::modifyHead(Node *newHead)
{
	head = newHead;
}

void Poly::append(double v)
{
	// Update the order of the polynomial
	order++;

	// Create a new instance of Node in the 'free space'.
    Node *newNode = new Node(v, NULL);

	// If list is empty, append node to head.
	if (head == NULL)
	{
		  head = newNode;
		  return;
	}

	// Else append the new node to the end of Poly.
	Node *iterator;
	for (iterator = head; iterator->next != NULL; iterator = iterator->next);
	iterator->next = newNode;
}

void Poly::print()
const
{
	Node *temp = getHead();

	printf("HEAD -> ");
	while (temp != NULL)
	{
	    printf("[%.2f] -> ", temp->value);
		  temp = temp->next;
	}
	printf("NULL\n");
}

void Poly::copy(const Poly& p)
{
	// If source is empty, make destination poly empty as well.
	if (p.getHead() == NULL)
	{
		head = NULL;
		return;
	}

	// Else copy the polynomial, node by node.
	// Note: the the first node copied needs to be pointed
	// to by head, all others need to be pointed to by prev_node->next;
	Node *iter = p.getHead();
	Node *newNode = new Node(iter->value, NULL);
	head = newNode;
	iter = iter->next;

	Node *dest = head;
	while (iter != NULL)
	{
		// Create a new node. Append it to poly.
		newNode = new Node(iter->value, NULL);
		dest->next = newNode;

		// Increment pointers.
		iter = iter->next;
		dest = dest->next;
	}

	// Copy order as well.
	order = p.getOrder();
}
