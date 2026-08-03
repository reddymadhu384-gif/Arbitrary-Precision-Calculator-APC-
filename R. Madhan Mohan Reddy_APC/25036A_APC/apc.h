#ifndef APC_H
#define APC_H   // Header guard to prevent multiple inclusion

#include <stdio.h>    // For input/output functions (printf, etc.)
#include <string.h>   // For string operations (strlen, etc.)
#include <stdlib.h>   // For dynamic memory allocation (malloc, free)

// Macros for function return status
#define SUCCESS		1   // Indicates successful operation
#define FAILURE		0   // Indicates failure

// Macros used for comparing two operands
#define SAME		0   // Both operands are equal
#define OPERAND1	1   // Operand1 is greater
#define OPERAND2	2   // Operand2 is greater

// Definition of doubly linked list node
typedef struct node
{
    struct node *prev;   // Pointer to previous node
    int data;            // Stores single digit of number
    struct node *next;   // Pointer to next node
} node;

/* ================= Arithmetic operations ================= */

// Performs addition of two numbers represented as linked lists
void addition(node *tail1, node *tail2, node **headR, node **tailR);

// Performs subtraction of two numbers represented as linked lists
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);

// Performs multiplication of two numbers represented as linked lists
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);

// Performs division of two numbers represented as linked lists
void division(node *headL1, node *head_opr2, node *tail_opr2, node **headR, node **tailR);

/* ================= Validation & list creation ================= */

// Validates command line arguments (format, operator, etc.)
int cla_validation(int argc, char *argv[]);

// Converts input string into linked list (each digit as node)
void create_list(char *opr, node **head, node **tail);

/* ================= List operations ================= */

// Inserts a node at the beginning of the list
int insert_first(node **head, node **tail, int data);

// Inserts a node at the end of the list
int insert_last(node **head, node **tail, int data);

// Deletes entire linked list and frees memory
int delete_list(node **head, node **tail);

// Prints the linked list (used to display number)
void print_list(node *head);

/* ================= Utility functions ================= */

// Compares two linked list numbers
// Returns OPERAND1, OPERAND2, or SAME
int compare_list(node *head1, node *head2);

// Returns length (number of nodes) in list
int list_len(node *head);

// Removes leading zeros from result list (e.g., 00045 → 45)
void remove_pre_zeros(node **head);

#endif   // End of header guard