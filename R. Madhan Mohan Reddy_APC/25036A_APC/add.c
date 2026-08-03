#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    // 1. Declare temporary pointers to traverse both lists from LSB (tail)
    node *temp1 = tail1;
    node *temp2 = tail2;

    // Variables to store digits and result
    int data1 = 0;
    int data2 = 0;
    int sum = 0, carry = 0;

    // 2. Traverse until both lists are completely processed
    while(temp1 != NULL || temp2 != NULL)
    {
        // 3. Get digit from first list (if NULL, take 0)
        if(temp1 == NULL)
            data1 = 0;
        else
            data1 = temp1->data;

        // 4. Get digit from second list (if NULL, take 0)
        if(temp2 == NULL)
            data2 = 0;
        else
            data2 = temp2->data;

        // 5. Add both digits along with carry
        sum = data1 + data2 + carry;

        // 6. Extract remainder (digit to store) and new carry
        int rem = sum % 10;   // single digit
        carry = sum / 10;     // carry for next iteration

        // 7. Insert result digit at beginning (since we are adding from LSB)
        if(insert_first(headR, tailR, rem) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }

        // 8. Move to previous nodes (towards MSB)
        if(temp1 != NULL)
            temp1 = temp1->prev;

        if(temp2 != NULL)
            temp2 = temp2->prev;
    }

    // 9. If carry remains after loop, insert it at beginning
    if(carry > 0)
    {
        if(insert_first(headR, tailR, carry) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }
    }
}