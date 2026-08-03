#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // 1. Declare temporary pointers to traverse from LSB (tail)
    node *temp1 = tail1;
    node *temp2 = tail2;

    // Variables to store digits and result
    int data1 = 0;
    int data2 = 0;
    int diff = 0, borrow = 0;

    // 2. Traverse until first list becomes NULL (assumes operand1 >= operand2)
    while(temp1 != NULL)
    {
        // 3. Get digit from first list
        data1 = temp1->data;

        // 4. Get digit from second list (if NULL, take 0)
        if(temp2 == NULL)
            data2 = 0;
        else
            data2 = temp2->data;

        // 5. Subtract previous borrow from current digit
        data1 = data1 - borrow;

        // 6. Check if borrow is required
        if(data1 < data2)
        {
            // Borrow from next higher digit
            diff = (data1 + 10) - data2;
            borrow = 1;
        }
        else
        {
            // No borrow needed
            diff = data1 - data2;
            borrow = 0;
        }

        // 7. Insert result digit at beginning (to maintain correct order)
        if(insert_first(headR, tailR, diff) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }

        // 8. Move to previous nodes (towards MSB)
        temp1 = temp1->prev;

        if(temp2 != NULL)
            temp2 = temp2->prev;
    }
}