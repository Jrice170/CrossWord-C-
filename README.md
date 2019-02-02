Programming assignment 1 (PA01)
==============================

#  Dynamically Allocated Two-Dimensional Arrays

---

## What is this repository?
The files listed here are the starting point for your assignment. 
Only add source files (not compiled files) to the Git repository.

## Note (actually do this)!!
Thoroughly read the syllabus sections on "Programming assignments" and "Grading". These sections give good tips, tricks, hints, and instructions for programming assignments, including how to submit via Git.

## Assignment description
Finding patterns in data, like text files, or arrays of pixel values, is the basis of many more advanced methods, for example, image recognition in AI, or text processing. This week, you will write a program to input and store a 2D matrix of data of user-defined size, and then find a segment of data in that matrix that matches a search key, regardless of its orientation or direction.

![matrix](matrix.png)

## Input/Output
These are both specified in the sample_*.txt files provided in your repository. 

* Input is all via C++ std::cin. Even though sample_input.txt is a file, input is not via fstream or file input; we re-direct via **standard input**: https://en.wikipedia.org/wiki/Standard_streams. See the syllabus for details.
* The general form of input is here:
```
    <number of cases>

    <number of rows> <number of columns>
    <data set>
    <intended word to search>

    <number of rows> <number of columns>
    <data set>
    <intended word to search>
```

* sample_output.txt specifies exactly what your program should produce. We will use the Unix program **diff** to compare your output to this file, and if yours does not match, you will lose points.
* See the syllabus for details as to how to use $diff at the command line.

## Grading
95% of this assignment will be graded based on the successful implementation of the functions in the header file using unit testing, and the correct output of main. Each function's performance on its own unit test will be worth a certain subset of those points, and the output of main will as well. A correct submission will result in a grade of 95%. The remaining 5% will be awarded based on run-time for you main, with the student with the fastest run-time in the class receiving a 100%, and the slowest correct submission receiving 95%, and a linear interpolation (not sequential) using your actual time in between.

## Due date
Please see the schedule for all due dates.

