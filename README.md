# cs503-lisp-interpreter

## Compiling:

1. Clone the source directory
    ``` 
   git clone https://github.com/andyhansen7/cs503-lisp-interpreter.git
    ```
2. Run the setup script to create the build folder
    ```
    ./setup.sh
    ```
3. Move to the ```build``` directory and run cmake
    ```
   cd build/
   ```
   ``` 
   make
   ```
4. Move back to the source directory and run the executable
   ```
   cd ..
   ```
   ``` 
   ./arhansen-lisp-interpreter
   ```

## Usage:

### Command line options:
>-d: Enable debugging script\
>-i: Set input filepath (relative to source directory)\
>--help: Pretty much the same as this

### Testing
Unit tests exist in the /tests directory, in UnitTests.cpp. This file utilizes the GTest framework to unit test the codebase. 

To run these tests for yourself, navigate to the build directory as above, and run the command ```ctest```. The test cases and outputs will be shown.

## Test Results
```
1. (number? 5.43)
   > T
   
2. (number? ())
   > T
   
3. (number? (1 2 3 4))
   > ()
   
4. (list? (1 2 3 4))
   > T
   
5. (list? 1.23)
   > ()
   
6. (list? ())
   > T
   
7. (null? ())
   > T
   
8. (+ 1 2 3)
   > 6.000000
   
9. (- 10 1 3)
   > 6.000000
   
10. (* 1 2 3)
    > 6.000000
   
11. (/ 36 2 3)
    > 6.000000

12. (print 6)
    > 6.000000

13. (if T (1) (2))
    > 1.000000

14. (if () (1) (2))
   > 2.000000

15. (set x 1.23)
    > OK
    (+ x x)
    > 2.460000

16. (define x (a) (print a))
    > OK
    (x 1.23)
    > 1.230000

17. (begin (print 1) (print 2))
    > 1.000000
    > 2.000000

18. (set var 0)
    > OK
    (while (< var 3) (begin (print var) (set var (+ var 1)))) 
    > 0.000000
    > OK
    > 1.000000
    > OK
    > 2.000000
    > OK

19. (cons 1 2)
    > (1.000000 2.000000)

20. (car (1 2))
    > 1.000000

21. (cdr (1 2))
    > (2.000000)