#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2 = tail2;   // Pointer to traverse second number (multiplier)

    node *headR1 = NULL, *tailR1 = NULL;   // Final accumulated result
    node *headR2 = NULL, *tailR2 = NULL;   // Partial result for each digit multiplication
    node *headAR = NULL, *tailAR = NULL;   // Result after addition of partial results

    int count = 0;   // Used for shifting (adding zeros like manual multiplication)

    // Traverse each digit of second number (from LSB to MSB)
    while (temp2 != NULL)
    {
        headR2 = tailR2 = NULL;   // Reset partial result list
        int carry = 0;

        // 1. Add shifting zeros based on position (IMPORTANT)
        // Example: second digit → add one zero, third digit → add two zeros
        for (int i = 0; i < count; i++)
        {
            if(insert_last(&headR2, &tailR2, 0) == FAILURE)
            {
                printf("ERROR: Insertion failed\n");
                return;
            }
        }

        node *temp1 = tail1;   // Pointer to traverse first number

        // 2. Multiply each digit of first number with current digit of second number
        while (temp1 != NULL)
        {
            int product = temp1->data * temp2->data + carry;

            int digit = product % 10;   // Store single digit
            carry = product / 10;       // Carry for next iteration

            // Insert digit at beginning to maintain correct order
            if(insert_first(&headR2, &tailR2, digit) == FAILURE)
            {
                printf("ERROR: Insertion failed\n");
                return;
            }

            temp1 = temp1->prev;   // Move to next higher digit
        }

        // 3. If carry remains after multiplication, insert it
        if (carry)
        {
            if(insert_first(&headR2, &tailR2, carry) == FAILURE)
            {
                printf("ERROR: Insertion failed\n");
                return;
            }
        }

        // 4. First iteration → directly assign partial result to final result
        if (headR1 == NULL)
        {
            headR1 = headR2;
            tailR1 = tailR2;
        }
        else
        {
            // Reset addition result list before using
            headAR = tailAR = NULL;

            // Add previous result and current partial result
            addition(tailR1, tailR2, &headAR, &tailAR);

            // Free old lists to avoid memory leaks
            delete_list(&headR1, &tailR1);
            delete_list(&headR2, &tailR2);

            // Update final result with new addition result
            headR1 = headAR;
            tailR1 = tailAR;
        }

        temp2 = temp2->prev;  // Move to next digit of second number
        count++;              // Increase shift count
    }

    // Store final result in output pointers
    *headR = headR1;
    *tailR = tailR1;
}