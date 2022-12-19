Evan Lee & Hunter Egeland
CST-405
Complete Compiler
README


Language Specifications:


1. We allow booleans (expressed as integers 0 and 1), integers, floats, and chars. We also allow arrays for these types as well. 
2. We allow order of operations, exponents, +, -, x, and / in variable declarations but any math in while and if/else statements need to be + and - only.
3. Variable initializations need to be done before they are declared as a variable. For example: 
                        
int x = 5;


   will not work. This needs to be written as two separate expressions as such:


                int x;
                x = 5;


4. To write a newline: “write ~nl;”
5. On the same note, printing a variable or string uses the “write” command.


                write x;
                write “hello world”;


6. There is no “int main() {}”, any expression written not in a function will be run.
7. There is no “&&” or “||” operators inside conditions.
8. Functions can have either no parameters or up to 3 parameters.



Installation:


To install and run our parser first clone/download the repository into a Ubuntu directory using the command:


 git clone https://github.com/hunteregeland/compilers2.git 


Then, do the following command in the terminal to allow text coloring in some of the Python code we use:


pip install colorama




Function source code:


To run the first test file for functions, change line 14 of the “Makefile” file to the following:


        ./parser testing1.gcupl


Then, run the following code in the terminal to run the file:


        make all


Now, copy the code from MIPScode.asm to a separate file on your Desktop or just copy MIPScode.asm to your Desktop. Then, open QTSpim and reinitialize and load the file you just saved to your Desktop. Then, you can click the green run button and see the expected output in the console.




If-else statement source code:


To run the second test file for if-else statements, change line 14 of the “Makefile” file to the following:


        ./parser testing2.gcupl


Then, run the following code in the terminal to run the file:


        make all


Now, copy the code from MIPScode.asm to a separate file on your Desktop or just copy MIPScode.asm to your Desktop. Then, open QTSpim and reinitialize and load the file you just saved to your Desktop. Then, you can click the green run button and see the expected output in the console.


While loop source code:


To run the third test file for while loops, change line 14 of the “Makefile” file to the following:


        ./parser testing3.gcupl


Then, run the following code in the terminal to run the file:


        make all


Now, copy the code from MIPScode.asm to a separate file on your Desktop or just copy MIPScode.asm to your Desktop. Then, open QTSpim and reinitialize and load the file you just saved to your Desktop. Then, you can click the green run button and see the expected output in the console.