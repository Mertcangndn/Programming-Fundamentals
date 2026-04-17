
# Smith Number Finder

This C program is designed to check if a given number is a **Smith Number**. A Smith Number is a composite number for which the sum of its digits is equal to the sum of the digits of its prime factors (excluding 1 as a factor).

## What is a Smith Number?

A **Smith Number** is a composite number where:
1. The number itself is not prime.
2. The sum of the digits of the number is equal to the sum of the digits of its prime factors.

For example:
- 378 is a Smith Number:
    - Sum of digits of 378: 3 + 7 + 8 = 18
    - Prime factorization: 2, 3, 3, and 3
    - Sum of digits of the prime factors: (2) + (3 + 3 + 3) = 18

## How the Program Works

The program checks if a given number is a Smith Number through the `smith` function:
1. **Prime Factorization**: It finds all prime factors of the number by iterating through potential divisors and checks for primality.
2. **Digit Summation of Prime Factors**: For each prime factor, it sums its digits.
3. **Digit Summation of Original Number**: It separately calculates the sum of the digits of the original number.
4. **Comparison**: If the sums match, the number is identified as a Smith Number; otherwise, it is not.

## Code Structure

### Functions

- **smith(int sayi)**: Checks if the provided number `sayi` is a Smith Number. This function:
  - Loops through potential divisors of `sayi` to find prime factors.
  - Sums the digits of each prime factor and compares it to the sum of the digits of `sayi`.
  - Prints if the number is a Smith Number or not.

### Variables

- **int asallik**: Used to check if the divisor is prime.
- **int carpan**: Represents the divisor to check prime factors.
- **int sumc**: Stores the sum of digits of the prime factors.
- **int sumsayi**: Stores the sum of digits of the original number.

### Compilation

Compile the program with:

```bash
gcc smith_number_finder.c -o smith_finder
```

### Usage

Run the program by executing:

```bash
./smith_finder
```

The output will display whether the specified number is a Smith Number.

### Example Output

For an input of `121`:

```plaintext
Smith Sayisi Degildir.
```

## License

This code is open-source.
