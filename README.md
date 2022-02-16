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