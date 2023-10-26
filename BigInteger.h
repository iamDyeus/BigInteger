#include "stdio.h"
#include "stdlib.h"

struct node {
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *l;
    int sign;
    int length;
};


void reverse_linked_list_sign(struct node *head);
struct BigInteger initialize(char *s);


// Helping Functions
struct BigInteger add_positives(struct BigInteger a,struct BigInteger b,int sign);
struct BigInteger add_negative_positive(struct BigInteger a,struct BigInteger b,int sign);
struct BigInteger multiply(struct BigInteger a , struct BigInteger b ,int sign);
struct BigInteger division(struct BigInteger a , struct BigInteger b , int sign , int choice);
void truncate(struct BigInteger n); // Truncate Function

// Compare Functions
int compare_sub(struct node *h1 , struct node *h2);
int compare(struct BigInteger h1 , struct BigInteger h2);
// Display Functions
void display(struct BigInteger n);
void display_linked_list(struct node *head);



// Main Operation Functions
struct BigInteger add( struct BigInteger a,struct BigInteger b);
struct BigInteger sub( struct BigInteger a,struct BigInteger b);
struct BigInteger mul( struct BigInteger a,struct BigInteger b);
struct BigInteger div1(struct BigInteger a,struct BigInteger b);
struct BigInteger mod( struct BigInteger a,struct BigInteger b);