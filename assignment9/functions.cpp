
#include "functions.hh"
#define MAX_ORDER 20

/**
 *	Adds two polynomials and returns the result.
 */
Poly addPolynomials(Poly p1, Poly p2)
{
    Poly p;

    if (p1.getHead() == NULL || p2.getHead() == NULL)
    {
        fprintf(stderr, "Error: Adding a NULL polynomial.\n");
        return p;
    }

    // Traverse the longest polynomial.
    // If they are equal in length, traverse p1.
    Node *iterLong, *iterShort;
    int cOrder, orderShort;
    if (p2.getOrder() > p1.getOrder())
    {
        iterShort = p1.getHead();
        iterLong = p2.getHead();
        cOrder = p2.getOrder();
        orderShort = p1.getOrder();
    }
    else
    {
        iterShort = p2.getHead();
        iterLong = p1.getHead();
        cOrder = p1.getOrder();
        orderShort = p2.getOrder();
    }

    // While traversing the list, add like-terms.
    while (iterLong != NULL)
    {
        if (cOrder <= orderShort)
        {
            p.append(iterLong->value + iterShort->value);
            iterShort = iterShort->next;
        }
        else
        {
            p.append(iterLong->value);
        }

        iterLong = iterLong->next;
        cOrder--;
    }

    return p;
}

/**
 * [subtractPolynomials description]
 * @param  p1 [description]
 * @param  p2 [description]
 * @return    [description]
 */
Poly subtractPolynomials(Poly p1, Poly p2)
{
	Poly p;

    if (p1.getHead() == NULL || p2.getHead() == NULL)
    {
        fprintf(stderr, "Error: Subtracting a NULL polynomial.\n");
        return p;
    }

    // Traverse the longest polynomial.
    // If they are equal in length, traverse p1.
    Node *iterLong, *iterShort;
    int cOrder, orderShort;
    bool p1Short = false;

    if (p2.getOrder() > p1.getOrder())
    {
        iterShort = p1.getHead();
        iterLong = p2.getHead();
        cOrder = p2.getOrder();
        orderShort = p1.getOrder();
        p1Short = true;
    }
    else
    {
        iterShort = p2.getHead();
        iterLong = p1.getHead();
        cOrder = p1.getOrder();
        orderShort = p2.getOrder();
    }

    // While traversing the list, subtract like-terms.
    // Always subtracting p2 from p1.
    while (iterLong != NULL)
    {
        if (cOrder <= orderShort)
        {
            if (p1Short)
            {
                p.append(iterShort->value - iterLong->value);
            }
            else
            {
                p.append(iterLong->value - iterShort->value);
            }
            iterShort = iterShort->next;
        }
        else
        {
            p.append(iterLong->value);
        }

        iterLong = iterLong->next;
        cOrder--;
    }

    // Clean up any leading zeros.
    Node *prev;
    for(iterLong = p.getHead(), prev = NULL; iterLong->value == 0; prev = iterLong, iterLong = iterLong->next)
    {
        delete prev;
    }
    delete prev;
    p.modifyHead(iterLong);

	return p;
}

/**
 *  Multiply p1 and p2 and return the result.
 */
Poly multiplyPolynomials(Poly p1, Poly p2)
{
	Poly p;

    if (p1.getHead() == NULL || p2.getHead() == NULL)
    {
        fprintf(stderr, "Error: Multipying a NULL polynomial.\n");
        return p;
    }

    int ord1, ord2, highestOrd;
    double liketerms[MAX_ORDER] = {0};
    Node *iter1, *iter2;

    ord1 = p1.getOrder();
    ord2 = p2.getOrder();
    highestOrd = ord1 + ord2;

    for (iter1 = p1.getHead(); iter1 != NULL; iter1 = iter1->next)
    {
        for(iter2 = p2.getHead(); iter2 != NULL; iter2 = iter2->next)
        {
            liketerms[ord1 + ord2] += iter1->value * iter2->value;
            ord2--;
        }
        ord2 = p2.getOrder();
        ord1--;
    }

    for (int i = highestOrd; i >= 0; i--)
    {
        p.append(liketerms[i]);
    }

	return p;
}
