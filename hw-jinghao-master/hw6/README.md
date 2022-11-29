# Homework 6 Programming Part
Name: Jinghao (Daniel) Wang
USC ID: 4237145509
USC Net ID: jinghao

## Contents
- counting.cpp
- Hashtable.h
- Hashtable.cpp
- Makefile
- README.md

## Compile Method
Simply by typing make counting or make

## Programming Behavior
 - In counting.cpp, when subtracting words from input file, after get rid of whitespaces and delete the non-letter part in the word, I convert those trimmed word to lowercase, ready for being inserted to the vector words
 -  But before inserting into vector words, I checked if the trimmed word has length bigger than 0 (for some word only containing non-letters, then it would become an empty string after trimming, so get rid of them) and check if they are shorter than or equal to 28 characters since the program only deals with strings shorter than or equal to 28 characters and in hamlet there are some words larger than 28 characters in hamlet.txt
 - It means I only take non empty strings with length shorter than or eqaul to 28 characters and add into vector words


## Report Questions
1. Which size of input cases did you use?
    30, 300, 3000, 30000, 31945
    
2. Did you use AVL Trees or the STL map?
    STL map
    
3. For each of the 4 approaches (linear probing, quadratic probing, double hashing, AVL Trees), report how long each of your input cases took. How long did it take per operation?

    Linear Probing with debug mode
        - Size 30 with r = 10000
            Each input case took:   1.81066e-05
            Each operation took:    6.03553e-07
        - Size 300 with r = 1000
            Each input case took:   0.000179966
            Each operation took:    5.99887e-07
        - Size 3000 with r = 100
            Each input case took:   0.001582
            Each operation took:    5.27333e-07
        - Size 30000 with r = 10
            Each input case took:   0.0117009
            Each operation took:    3.9003e-07
        - Size 31945 with r = 10
            Each input case took:   0.0122741
            Each operation took:    3.84226e-07
            
    Quadratic Probing with debug mode
        - Size 30 with r = 10000
            Each input case took:   1.77905e-05
            Each operation took:    5.93017e-07
        - Size 300 with r = 1000
            Each input case took:   0.000179921
            Each operation took:    5.99737e-07
        - Size 3000 with r = 100
            Each input case took:   0.00158474
            Each operation took:    5.28247e-07
        - Size 30000 with r = 10
            Each input case took:   0.0120324
            Each operation took:    4.0108e-07
        - Size 31945 with r = 10
            Each input case took:   0.0122112
            Each operation took:    3.82257e-07
            
    Double-Hashing with debug mode
        - Size 30 with r = 10000
            Each input case took:   2.97905e-05
            Each operation took:    9.93017e-07
        - Size 300 with r = 1000
            Each input case took:   0.000302411
            Each operation took:    1.00804e-06
        - Size 3000 with r = 100
            Each input case took:   0.00260703
            Each operation took:    8.6901e-07
        - Size 30000 with r = 10
            Each input case took:   0.0192545
            Each operation took:    6.41817e-07
        - Size 31945 with r = 10
            Each input case took:   0.020451
            Each operation took:    6.40194e-07
            
    STL Map
        - Size 30 with r = 10000
            Each input case took:   1.49498e-05
            Each operation took:    4.98327e-07
        - Size 300 with r = 1000
            Each input case took:   0.000205113
            Each operation took:    6.8371e-07
        - Size 3000 with r = 100
            Each input case took:   0.00219603
            Each operation took:    7.3201e-07
        - Size 30000 with r = 10
            Each input case took:   0.0239342
            Each operation took:    7.97807e-07
        - Size 31945 with r = 10
            Each input case took:   0.0260645
            Each operation took:    8.15918e-07
            
4. 
(1) All three different ways (linear probing, quadratic probing, double-hashing) for Hashtables perfoms shorter average runtime for each operation as the size of input increases, this is kind of surprising to me but I think it is because keep loading factor be less than 0.5 for almost all the time (only not at the boundary case that after inserting one element, the loading factor changes from less than 0.5 to larger than 0.5, but Hashtable get resized immediately when next input is inserted), and the size of Hashtable is always prime number. It makes Hashtable more efficient and the benefits become more and more obvious when the input size increases, which cuts large portion of time and makes the average runtime for each operation decrease.

(2) Double-Hashing has longer average runtime for each operation than linear probing and quadratic probing, it is not very surprising, since we have two hash functions to be used in double-hashing and use one extra hash function to calculate another hash value would make the program take longer and also longer for each opeartion on average.

(3) Linear Probing and Quadratic Probing both behaves similarly well in terms of average runtime for each operation, this is surpring because I though quadratic probing would perform better than linear probing since linear probing tends to make primay cluster, but I think it is because the loading factor is less than 0.5 for majority of the time, so Hashtable is really efficient and the size of Hashtable is always prime number, so it makes those two probing method behaves similarly well because of lots of empty spaces in Hashtable.

(4) At first at smaller input size (30), STL Map behaves better than Hashtbale but for Hashtables, no matter which probing method used, it has shorter average runtime for each operation compared to STL map as the size increases and at some point behaves better than STL Map(linear and quadratic probing reached the point earlier (at size 300)than double hashing but double hashing behaves better than STL Map at size 30000 ), it is not surprising at all since the average operation runtime for Hashtable is constant (does not depends on the input size) and the operation runtime is logN (does depend on the input size), and when size becomes larger than certain number, Hashtable will behave better than STL map on average.
