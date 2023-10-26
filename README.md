# Big Integer Library using Linked List in C Language

Welcome to the Big Integer Library, a C language library that allows you to work with arbitrarily large integers using a linked list data structure. This library provides a set of functions to perform arithmetic operations on big integers, making it easier to handle large numbers in your C programs.

## Features

- **Arithmetic Operations:** Perform addition, subtraction, multiplication, and division on large integers.
- **Dynamic Memory Management:** Utilizes dynamic memory allocation for handling integers of any size.
- **Input and Output:** Supports input and output of large integers from and to standard input/output streams.
- **Error Handling:** Provides error handling for invalid input or memory allocation failures.
- **Modular Design:** Designed as a reusable library, making it easy to integrate into your C projects.

## How to Use

1. **Include the Library:**
   Include the `BigInteger.h` header file in your C source files to access the functions provided by the Big Integer Library.

   ```c
   #include "BigInteger.h"
   ```

2. **Compile your Code:**
   Compile your C files along with `BigInteger.c` to create the executable.

   ```sh
   gcc -o my_program my_program.c BigInteger.c -lm
   ```

   Note: The `-lm` flag is used to link the math library, which is required for some mathematical operations.

3. **Use Big Integer Functions:**
   Use the functions provided by the Big Integer Library to perform operations on large integers. Make sure to create and free big integers using appropriate functions.

   ```c
   #include <stdio.h>
   #include "BigInteger.h"

   int main() {
       // Create and perform operations on big integers here
       // Don't forget to free the allocated memory using `free_big_int()` function
       return 0;
   }
   ```


## Contributing

Contributions to the Big Integer Library are welcome! If you find any issues or have suggestions for improvement, please create an issue or a pull request in this repository.

## License

This Big Integer Library is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```