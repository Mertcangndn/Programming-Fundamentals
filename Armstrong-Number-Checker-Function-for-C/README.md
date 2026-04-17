# Armstrong Number Checker Function

This C program checks if a given number is an Armstrong number.
An Armstrong number (also known as a narcissistic number) is a number that is equal to the sum
of its own digits each raised to the power of the number of digits. For example, 153 is an Armstrong number
because 1^3 + 5^3 + 3^3 = 153.

## How the Program Works:
1. Input: The program prompts the user to enter a number.
2. Digit Counting: The program calculates the number of digits in the entered number.
3. Power Calculation: It then iterates through each digit, raising each to the power of the total number of digits and summing these values.
4. Comparison: If the sum of the powered digits equals the original number, it is an Armstrong number; otherwise, it is not.

## Example:
For the input 153:
- The number of digits is 3.
- The program calculates 1^3 + 5^3 + 3^3 = 153.
- Since the sum equals the original number, 153 is an Armstrong number.

# Features:
- The program only uses functions and doesn't require returning or taking input/output values in the function itself.
- The function armstrong() checks if the number is Armstrong and prints the result.

**Feel free to modify or improve the code as needed!**
