# Homework 5 Programming Part
Name: Jinghao (Daniel) Wang
USC ID: 4237145509
USC Net ID: jinghao

## Contents
- bayes.cpp
- Makefile
- README.md

## Compile Method
Simply by typing make or make bayes as indicated in Makefile

## Programming Behavior
For each classifying unit (each line in classify.txt except for the first line), I used a map to store all the possible classfications(key) and their correpsonding Pr(C|X)(value)

When outputting the classification with maximum probability, if two classifications has the same conditional probability, I update the classifciation if the conditional probability is bigger than or equal to current maximum probability, so I output the classifciation comes later in the map when two classifications have the same conditional probability

The output file doesn't have newline for the last line as instructed through piazza post
