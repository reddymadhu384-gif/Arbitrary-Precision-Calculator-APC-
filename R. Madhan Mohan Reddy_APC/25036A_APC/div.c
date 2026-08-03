#include "apc.h"

void division(node *headl, node *headOPR2, node *tailOPR2, node **headR, node **tailR)
{
    node *headOPR1 = NULL, *tailOPR1 = NULL;   // Partial dividend (like current number in long division)
    node *head_sr = NULL, *tail_sr = NULL;     // Stores subtraction result

    node *temp = headl;   // Pointer to traverse first operand (dividend)

    // 1. Take first digit of dividend
    insert_last(&headOPR1, &tailOPR1, temp->data);

    // 2. Build initial dividend until it becomes >= divisor
    while(compare_list(headOPR1, headOPR2) == OPERAND2 && temp->next != NULL)
    {
        temp = temp->next;

        // Append next digit to form a bigger number
        if(insert_last(&headOPR1, &tailOPR1, temp->data) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }
    }

    // 3. Main division loop (similar to long division)
    while(temp != NULL)
    {
        int subcount = 0;   // Counts how many times divisor fits (quotient digit)

        // 4. Perform repeated subtraction until dividend < divisor
        while(compare_list(headOPR1, headOPR2) == OPERAND1 || 
              compare_list(headOPR1, headOPR2) == SAME)
        {
            head_sr = tail_sr = NULL;   // Reset subtraction result list (IMPORTANT)

            // Subtract divisor from current dividend
            subtraction(tailOPR1, tailOPR2, &head_sr, &tail_sr);

            // Delete old dividend list
            delete_list(&headOPR1, &tailOPR1);

            // Update dividend with new result
            headOPR1 = head_sr;
            tailOPR1 = tail_sr;

            remove_pre_zeros(&headOPR1);
            subcount++;   // Increment quotient count
        }

        // 5. Store quotient digit
        if(insert_last(headR, tailR, subcount) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }

        temp = temp->next;

        // 6. Bring down next digit (like manual long division)
        if(temp != NULL)
        {
            if(insert_last(&headOPR1, &tailOPR1, temp->data) == FAILURE)
            {
                printf("ERROR: Insertion failed\n");
                return;
            }

            // Remove leading zeros after subtraction
            remove_pre_zeros(&headOPR1);
        }
    }
}