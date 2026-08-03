#include "apc.h"

// Validate command line arguments
int cla_validation(int argc, char *argv[])
{
    // Check if exactly 4 arguments are passed (program name + 3 inputs)
    if(argc != 4)
    {
        printf("ERROR: Invalid number of arguments\n");
        return FAILURE;
    }

    // ---------------- CHECK OPERATOR ----------------

    // Operator must be a single character
    if(strlen(argv[2]) != 1)
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }

    char op = argv[2][0];

    // Allowed operators: +, -, x, X, /
    if(op != '+' && op != '-' && op != 'x' && op != 'X' && op != '/')
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }

    // ---------------- CHECK OPERAND 1 ----------------
    int i = 0;

    // Case: only '+' or '-' without number → invalid
    if((argv[1][0] == '+' || argv[1][0] == '-') && argv[1][1] == '\0')
    {
        printf("ERROR: Invalid operand\n");
        return FAILURE;
    }

    // Skip sign if present
    if(argv[1][0] == '+' || argv[1][0] == '-')
        i = 1;

    // Check each character is a digit
    for(; argv[1][i] != '\0'; i++)
    {
        if(argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("ERROR: Operand must be an integer\n");
            return FAILURE;
        }
    }

    // ---------------- CHECK OPERAND 2 ----------------
    i = 0;

    // Same validation as operand1
    if((argv[3][0] == '+' || argv[3][0] == '-') && argv[3][1] == '\0')
    {
        printf("ERROR: Invalid operand\n");
        return FAILURE;
    }

    // Skip sign
    if(argv[3][0] == '+' || argv[3][0] == '-')
        i = 1;

    // Check digits
    for(; argv[3][i] != '\0'; i++)
    {
        if(argv[3][i] < '0' || argv[3][i] > '9')
        {
            printf("ERROR: Operand must be an integer\n");
            return FAILURE;
        }
    }

    // ---------------- DIVISION BY ZERO CHECK ----------------

    // If operator is division and operand2 is "0"
    if((op == '/') && strcmp(argv[3], "0") == 0)
    {
        printf("ERROR: Divsion by zero not allowed!\n");
        return FAILURE;
    }

    return SUCCESS;  // All validations passed
}


// Create linked list from string operand
void create_list(char *opr, node **head, node **tail)
{
    int i = 0;

    // Skip sign (+ or -)
    if(opr[0] == '+' || opr[0] == '-')
    {
        i = 1;
    }

    // Traverse the string
    while(opr[i])
    {
        // Convert character to integer digit
        if(opr[i] >= '0' && opr[i] <= '9')
        {
            int data = opr[i] - '0';

            // Insert digit at end of list
            if(insert_last(head, tail, data) == FAILURE)
            {
                printf("No possible operation\n");
                exit(1);  // Exit if memory allocation fails
            }
        }
        i++;
    }
}


// Remove leading zeros from result list
void remove_pre_zeros(node **head)
{
    if(*head == NULL)
        return;

    node *temp = *head;

    // Remove nodes until non-zero digit or last node
    while(temp->data == 0 && temp->next != NULL)
    {
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);  // Free removed node
        temp = *head;
    }
}


// Find length of linked list
int list_len(node *head)
{
    int len = 0;

    // Traverse list and count nodes
    while(head != NULL)
    {
        len++;
        head = head->next;
    }

    return len;
}


// Compare two linked list numbers
int compare_list(node *head1, node *head2)
{
    // First compare lengths
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    if(len1 > len2)
        return OPERAND1;   // First number is greater
    else if(len1 < len2)
        return OPERAND2;   // Second number is greater
    else
    {
        // If lengths equal, compare digit by digit
        while(head1 != NULL && head2 != NULL)
        {
            if(head1->data > head2->data)
                return OPERAND1;
            else if(head1->data < head2->data)
                return OPERAND2;

            head1 = head1->next;
            head2 = head2->next;
        }
    }

    return SAME;  // Both numbers are equal
}


// Insert node at beginning
int insert_first(node **head, node **tail, int data)
{
    // Allocate memory for new node
    node *new = malloc(sizeof(node));

    if(new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    // If list is empty
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        // Link new node at beginning
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}


// Insert node at end
int insert_last(node **head, node **tail, int data)
{
    // Allocate memory
    node *new = malloc(sizeof(node));

    if(new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    // If list is empty
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        // Link new node at end
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}


// Delete entire list
int delete_list(node **head, node **tail)
{
    if(*head == NULL)
        return FAILURE;

    node *temp = *head;

    // Traverse and free all nodes
    while(temp != NULL)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }

    *tail = NULL;  // Reset tail pointer

    return SUCCESS;
}


// Print linked list
void print_list(node *head)
{
    if(head == NULL)
    {
        printf("Info : List is Empty\n");
        return;
    }

    // Traverse and print each digit
    while(head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");  // New line after printing number
}