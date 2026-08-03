/******************************************************************************
 * Author        : R.Madhan Mohan Reddy
 * Project Name  : APC (Arbitrary Precision Calculator)
 * Description   : 
 * This project implements an Arbitrary Precision Calculator using a 
 * Doubly Linked List to perform arithmetic operations on very large 
 * numbers which cannot be handled by standard data types.
 *
 * Operations Supported :
 * 1. Addition (+)
 * 2. Subtraction (-)
 * 3. Multiplication (*)
 * 4. Division (/)
 *
 * Data Structure Used :
 * - Doubly Linked List (Each node stores a single digit)
 *
 * Features :
 * - Handles very large numbers
 * - Supports positive and negative numbers
 * - Removes leading zeros
 * - Proper validation of command-line arguments
 * - Error handling (invalid operator, division by zero, etc.)
 *
 * Files Description :
 * - main.c  : Handles input, validation, and operation selection
 * - apc.h   : Function declarations and macros
 * - apc.c   : Linked list utility functions
 * - add.c   : Addition logic
 * - sub.c   : Subtraction logic
 * - mul.c   : Multiplication logic
 * - div.c   : Division logic
 *
 * Working Principle :
 * - Input is taken from command line arguments
 * - Operands are converted into linked lists
 * - Arithmetic operations are performed digit by digit
 * - Result is stored and displayed using linked list
 *
 * Sample Execution :
 *   ./a.out 123 + 456  → Output : 579
 *   ./a.out -100 / 20  → Output : -5
 *
 * Limitations :
 * - Division uses repeated subtraction (less efficient)
 *
 ******************************************************************************/
#include "apc.h" 

int main(int argc, char *argv[])
{
    // Pointers for first number linked list
    node *head1 = NULL, *tail1 = NULL;

    // Pointers for second number linked list
    node *head2 = NULL, *tail2 = NULL;

    // Pointers for result linked list
    node *headR = NULL, *tailR = NULL;

    // Validate command line arguments (format: num1 operator num2)
	if(cla_validation(argc, argv) == FAILURE)
	{
		printf("Invalid input\n");
		return 0;   // Exit if validation fails
	}

    // Create linked list for first operand (argv[1])
    create_list(argv[1], &head1, &tail1);

    // Create linked list for second operand (argv[3])
    create_list(argv[3], &head2, &tail2);

    // ---------------- SIGN HANDLING ----------------
    int sign1 = 1, sign2 = 1;   // Assume both numbers are positive initially

    // Check if first number is negative
    if(argv[1][0] == '-')
        sign1 = -1;

    // Check if second number is negative
    if(argv[3][0] == '-')
        sign2 = -1;

    char op = argv[2][0];   // Extract operator (+, -, x, /)

    switch(op)
    {
        // ================= ADDITION =================
        case '+':
            // If both numbers have same sign → direct addition
            if(sign1 == sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                // If both were negative → result is negative
                if(sign1 == -1)
                    printf("-");
            }
            else
            {
                // Signs are different → perform subtraction

                // If operand1 > operand2
                if(compare_list(head1, head2) == OPERAND1)
                {
                    subtraction(tail1, tail2, &headR, &tailR);

                    // Result sign follows operand1
                    if(sign1 == -1)
                        printf("-");
                }
                // If operand2 > operand1
                else if(compare_list(head1, head2) == OPERAND2)
                {
                    subtraction(tail2, tail1, &headR, &tailR);

                    // Result sign follows operand2
                    if(sign2 == -1)
                        printf("-");
                }
				else
				{
                    // Both numbers are equal → result is 0
					insert_last(&headR,&tailR,0);
				}
            }
            break;

        // ================= SUBTRACTION =================
        case '-':
            // If signs are different → convert to addition
            if(sign1 != sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                // Result sign follows operand1
                if(sign1 == -1)
                    printf("-");
            }
            else
            {
                // Same sign → perform subtraction

                // If operand1 > operand2
                if(compare_list(head1, head2) == OPERAND1)
                {
                    subtraction(tail1, tail2, &headR, &tailR);

                    // Result sign follows operand1
                    if(sign1 == -1)
                        printf("-");
                }
                // If operand2 > operand1
                else if(compare_list(head1, head2) == OPERAND2)
                {
                    subtraction(tail2, tail1, &headR, &tailR);

                    // Result sign changes accordingly
                    if(sign1 == 1)
                        printf("-");
                }
				else
				{
                    // Both numbers equal → result is 0
					insert_last(&headR,&tailR,0);
				}
            }
            break;

        //================= MULTIPLICATION =================
        case 'x':
		case 'X':
            // Perform multiplication
            multiplication(tail1, tail2, &headR, &tailR);

            // If signs are different → result is negative
            if(headR->data != 0 && sign1 != sign2)
			{
                printf("-");
			}
            break;

        //================= DIVISION =================
        case '/':
            // Perform division
            division(head1, head2, tail2, &headR, &tailR);

            // Print negative sign only if result is not zero and signs differ
			if(headR->data != 0 && sign1 != sign2)
			{
                printf("-");
			}
            
            break;

        default:
            // Invalid operator case
            printf("Invalid operator\n");
            return 0;
    }

    // Remove leading zeros from result (e.g., 000123 → 123)
	remove_pre_zeros(&headR);

    // Print final result linked list
    print_list(headR);

    return 0;   // Successful execution
}