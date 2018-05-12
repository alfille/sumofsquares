Sum Of Squares
2018 Paul H Alfille

This is a program to investigate decomposing an arbirtrary integer into the sum of integer squares
Actually into the fewest number of terms

E.g. 29 = 25 + 4 = 5^2 + 2^2
or   23 = 16 + 4 + 1 + 1 + 1 -- 5 terms
     23 = 9 + 9 + 4 + 1      -- 4 terms
     
     
Of course we extend that to cubes, fourth powers, etc...

-------------------

Get the program
Either download and unzip, or 

> git clone https://github.com/alfille/sumofsquares.git
> cd sumofsquares


-------------------

Compile the program:
> gcc -o sos sos.c
> chmod +x sos

The secopnd step needs to me done only once.

-------------------

Run the program:

> ./sos
       1,       1
       2,       1,       1
       3,       1,       1,       1
       4,       2
       5,       2,       1
       6,       2,       1,       1
       7,       2,       1,       1,       1
       8,       2,       2
       9,       3
      10,       3,       1
      11,       3,       1,       1
      12,       2,       2,       2
      13,       3,       2
      14,       3,       2,       1
      15,       3,       2,       1,       1
      16,       4
      17,       4,       1
      18,       3,       3
      19,       3,       3,       1
      20,       4,       2
.....


So the first column is the number being decomposed,
The next colums are squares that add up to the number

We show the square root of each term so for instance

      15,       3,       2,       1,       1

means

15 = 3^2 + 2^2 + 1^2 + 1^2 
   = 9   + 4   + 1 +   1

-------------------

Options:

 ./sos -h
Sum-of-squares decomposition: Find the minimum number of integer squares thqt sum to a given number
	{c} 2018 Paul H Alfille see github.com
Usage ./sos number
	look for sums up to <number> squared (default 100)
	-m --max max_number used for squares
	-d --depth max number of squares summed (default 10)
	-3 --cube look for cubed number sums
	-4 --fourth power sums
	-5 --fifth power sums
	-6 --sixth power sums
	-p --power up to 10th
	-c --count number of terms rather than list them
	-h --help this summary
    


