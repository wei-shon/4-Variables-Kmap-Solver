# 4 Variables Kmap minimizer
This is c++ code to find the simplest boolean equation, giving the group we circle and draw the Kmap.
This is uing the code from [https://github.com/AlaaAnani/3-Variable-K-Map-Minimizer](https://). Chnage 3 Variable to 4 Variable and adding the function that change the input boolean function to minimal decimal-digits and adding the function that writing and reading file. 
## Input
#### Given a input.txt.
The content is boolean function that is not the simplest function 
## Output
#### The output is output.txt.
The content is 4 Variables Kmap and the group we circle and minimize the variable. Fianlly giving the simple boolean function.
## Sample input
ad+a'bc+c'd+(a'b'cd)+(ab'cd')
## Sample output
    ========= K Map =========
      \AB|
    CD \ | 00 | 01 | 11 | 10
    -----+----+----+----+-----
      00 |  0 |  0 |  0 |  0 |
    -----+----+----+----+----|
      01 |  1 |  1 |  1 |  1 |
    -----+----+----+----+----|
      11 |  1 |  1 |  1 |  1 |
    -----+----+----+----+----|
      10 |  0 |  1 |  0 |  1 |
    --------------------------

group 1: [6, 7]

simplification of group 1 ->a'bc

group 2: [10, 11]

simplification of group 2 ->ab'c

group 3: [9, 1, 11, 3, 5, 7, 13, 15]

simplification of group 3 ->d

F(A, B, C, D) = a'bc + ab'c + d 
