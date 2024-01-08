# bignum
Arbitrary precision number library written in C.

## Makefile options:

| Target              | Explanation                                                       |
|---------------------|-------------------------------------------------------------------|
| ```compile```       | Compiles all library sources to object files.                     |
| ```test```          | Compiles and executes ```test/test.c```.                          |
| ```test-valgrind``` | Compiles and executes ```test/test.c``` using valgrind.           |
| ```lib```           | Compiles all library sources into ```libbignum.a```.              |
| ```clean```         | Deletes all object files, valgrind files and the test executable. |

Use ```DEBUG=1``` to compile any targets with debug flags. Execute ```clean``` beforehand.

## Feature status:

| Feature                      | Implemented |
|------------------------------|-------------|
| ```bignum``` from string     | ✔️           |
| ```bignum``` to string       | ✔️           |
| ```bignum``` from double     | ✔️           |
| ```bignum``` from integer    | ✔️           |
| copying ```bignum```         | ✔️           |
| comparisons                  | ✔️           |
| unsigned comparisons         | ✔️           |
| treating numbers as unsigned | ❌          |
| addition                     | ✔️           |
| subtraction                  | ✔️           |
| multiplication               | ⚠           |
| division                     | ❌          |
| modulo                       | ❌          |
| freeing ```bignum```         | ✔️           |

