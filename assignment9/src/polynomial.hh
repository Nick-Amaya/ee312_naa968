
#ifndef _polynomial
#define _polynomial

#include <stdio.h>
#include <iostream>

/**
 *  Class Node
 */
class Node
{
	public:
		// Constructor / Destructor
		Node(double v, Node *n);
		Node(const Node& n);
		~Node();

		double value;
		Node *next;
};

/**
 *  Class Poly
 */
class Poly
{
    public:
		Poly();
		Poly(const Poly& p);
		~Poly();
		void operator= (const Poly& p);

		// Accessors and Modifiers
		// Note: weird syntax. The const lets the compiler know that
		// you are not going to modify the function when you call on
		// it in the copy constructor.
		Node *getHead() const;
		int getOrder() const;
		void modifyHead(Node *newHead);

		void print() const;
		void append(double v);

	private:
		Node *head;
		int order;

		void copy(const Poly& p);
};

#endif
