#ifndef _INPUT_H
#define _INPUT_H
#include <iostream>
#include <vector>

extern int source, dest;
extern int cost;
extern std::vector<int> supply;
extern std::vector<int> demand;
extern std::vector<std::vector<int>> vect;
extern std::vector<std::vector<int>> ibfs;

void take_input();
bool test_equality();
void print_output();
#endif
