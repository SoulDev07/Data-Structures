#include <stdio.h>
#include <stdlib.h>

// Node structure for a term in a polynomial
typedef struct Node
{
    int coef;
    int exp;
    struct Node *next;
} Node;

// Function to create a new node with given coefficient and exponent
Node *createNode(int coef, int exp)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    return node;
}

// Function to insert a new term into the polynomial
Node *insertTerm(Node *head, int coef, int exp)
{
    Node *newNode = createNode(coef, exp);

    if (head == NULL || exp > head->exp)
    {
        // Insert at the beginning (highest exp)
        newNode->next = head;
        return newNode;
    }

    Node *curr = head;
    while (curr->next != NULL && exp < curr->next->exp)
        curr = curr->next;

    if (curr->next != NULL && exp == curr->next->exp)
    {
        // Term with the same exp exists, update the coef
        curr->next->coef += coef;
        free(newNode); // Free the unused node
    }
    else
    {
        // Insert in the middle or at the end
        newNode->next = curr->next;
        curr->next = newNode;
    }

    return head;
}

// Function to display the polynomial
void display(Node *head)
{
    if (head == NULL)
    {
        printf("Polynomial is empty!\n");
        return;
    }

    Node *curr = head;
    while (curr != NULL)
    {
        printf("%dx^%d", curr->coef, curr->exp);
        if (curr->next != NULL)
            printf(" + ");
        curr = curr->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node *addPolynomials(Node *poly1, Node *poly2)
{
    Node *result = NULL;
    Node *current1 = poly1;
    Node *current2 = poly2;

    while (current1 != NULL || current2 != NULL)
    {
        int coeff1 = (current1 != NULL) ? current1->coef : 0;
        int exp1 = (current1 != NULL) ? current1->exp : 0;

        int coeff2 = (current2 != NULL) ? current2->coef : 0;
        int exp2 = (current2 != NULL) ? current2->exp : 0;

        if (exp1 == exp2)
        {
            int sum_coeff = coeff1 + coeff2;
            result = insertTerm(result, sum_coeff, exp1);

            if (current1 != NULL)
                current1 = current1->next;

            if (current2 != NULL)
                current2 = current2->next;
        }
        else if (exp1 > exp2)
        {
            result = insertTerm(result, coeff1, exp1);

            if (current1 != NULL)
                current1 = current1->next;
        }
        else
        {
            result = insertTerm(result, coeff2, exp2);

            if (current2 != NULL)
                current2 = current2->next;
        }
    }

    return result;
}

// Function to multiply two polynomials
Node *multiplyPolynomials(Node *poly1, Node *poly2)
{
    Node *result = NULL;
    Node *current1 = poly1;

    while (current1 != NULL)
    {
        Node *current2 = poly2;

        while (current2 != NULL)
        {
            int coef = current1->coef * current2->coef;
            int exp = current1->exp + current2->exp;

            result = insertTerm(result, coef, exp);

            current2 = current2->next;
        }

        current1 = current1->next;
    }

    return result;
}

// Function to free memory allocated for the linked list
void freePolynomial(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    Node *poly1 = NULL, *poly2 = NULL, *result = NULL;

    // Example polynomials:
    // 3x^2 + 4x + 2
    poly1 = insertTerm(poly1, 3, 2);
    poly1 = insertTerm(poly1, 4, 1);
    poly1 = insertTerm(poly1, 2, 0);

    // 5x^3 + 2x + 1
    poly2 = insertTerm(poly2, 5, 3);
    poly2 = insertTerm(poly2, 2, 1);
    poly2 = insertTerm(poly2, 1, 0);

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    result = multiplyPolynomials(poly1, poly2);

    printf("Resultant Polynomial (Multiplication): ");
    display(result);

    result = addPolynomials(poly1, poly2);

    printf("Resultant Polynomial (Addition): ");
    display(result);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
