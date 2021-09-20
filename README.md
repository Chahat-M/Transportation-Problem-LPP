# Transportation-Problem-LPP
Transportation Problem is a kind of Linear Programming Problem (LPP) in which goods are transported from a set of sources to a set of destination subject to the supply and demand of the sources and destination respectively such that the total cost of transportation is minimized.

**There are two types of transportation problems:**
1. Balanced - When both supplies and demands are equal.
2. Unbalanced - When both supplies and demands are unequal.

In this project only **balanced** problems are dealt as for now though the condition is still tested using `test_equality()` function.

### Methods to solve:

To find the Initial Basic Feasible Solution (IBFS) there are three methods:
1. NorthWest Corner Method ([NWM](https://github.com/Chahat-M/Transportation-Problem-LPP/blob/main/src/NWM.cpp))
2. Least Cost Cell Method ([LCCM](https://github.com/Chahat-M/Transportation-Problem-LPP/blob/main/src/LCCM.cpp))
3. Vogel's Approximation Method ([Vogels](https://github.com/Chahat-M/Transportation-Problem-LPP/blob/main/src/Vogels.cpp))

## Usage
**Clone the repository using the command:**
```bash
git clone https://github.com/Chahat-M/Transportation-Problem-LPP.git
```
**To compile the program and run, follow these steps:**
1. Compile the `input.cpp` file using the command below, which creates the object code file `input.o`
```bash
g++ -c -I./include src/input.cpp
```
2. Then compile the file of the program you want to use which will generate the object code file `filename.o`.
```bash
g++ -c -I./include src/filename.cpp
```
For example, if you want to compile `LCCM.cpp` file, use `LCCM` instead of `filename`. This will create a `LCCM.o` object code file.

3. To create an executable by linking both the object code file, follow the command:
```bash
g++ -o output input.o filename.o
```
4. To run the program sucessfully, use the follwing command:
```bash
./output
```
**An alternative approach:**

Compile both the files together `input.cpp` and the program file you want to run using the command:
```bash
g++ -c -I./include src/input.cpp src/filename.cpp
```
This will auto-generate an object code file `a.out` which can then be executed.
```bash
./a.out
```

## Project Structure:
```
|-- .vscode
  |-- launch.json
  |-- settings.json
  |-- tasks.json
|-- include
  |-- input.hpp
|-- src
  |-- NWM.cpp
  |-- LCCM.cpp
  |-- Vogels.cpp
  |-- input.cpp
|-- README.md
|-- a.out
```
## Sample Example
The input for all the program files looks like:
```
Enter no. of sources and destination respectively: 3 4
Entries of the matrix:
3 1 7 4
2 6 5 9
8 3 3 2
Enter supply quantity for each source
300 400 500
Enter demand quantity for each destination
250 350 400 200
```
If `LCCM.cpp` file is executed, the output (as per the above input) will look like:
```
Optimum Cost 2850
IBFS matrix:
0 300 0 0 
250 0 150 0 
0 50 250 200
```
