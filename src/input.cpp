#include <iostream>
#include <vector>
#include "input.hpp"

int source, dest;
int cost = 0;
std::vector<int> supply(source);
std::vector<int> demand(dest);
std::vector<std::vector<int>> vect(source,std::vector<int> (dest));
std::vector<std::vector<int>> ibfs(source, std::vector<int> (dest,0));
int supply_sum = 0;
int demand_sum = 0;

// Function to take all inputs
void take_input(){
  std::cout << "Enter no. of sources and destination respectively:";
  std::cin >> source >> dest;

  // Matrix input in std::vector form
  std::cout << "Entries of the matrix:";
  for (int i = 0; i < source; i++) {
    std::vector<int> vect_temp;
    for (int j = 0; j < dest; j++) {
      int temp; 
      std::cin >> temp;
      vect_temp.push_back(temp);
    }
    vect.push_back(vect_temp);
  }
  
  std::cout << "Enter supply quantity for each source";
  for (int i = 0; i < source; i++){
    int temp;
    std::cin >> temp;
    supply.push_back(temp);
  }
  
  std::cout<<"Enter demand quantity for each destination";
  for (int i = 0; i < dest; i++) {
    int temp;
    std::cin >> temp;
    demand.push_back(temp);
  }

  // Setting all entries of ibfs vector to 0 for further ease
  for (int i = 0; i < source; i++) {
    std::vector<int> ibfs_temp;
    for (int j = 0; j < dest; j++) {
      int temp = 0; 
      ibfs_temp.push_back(temp);
    }
    ibfs.push_back(ibfs_temp);
  }
}

// Function to test if supply == demand or not
bool test_equality(){
  int supply_sum = 0;
  int demand_sum = 0;

  for (int i = 0; i < dest; i++) {
    if (i < source) {
      supply_sum += supply[i];
    }
      demand_sum += demand[i];
  }

  return supply_sum == demand_sum ? true : false;
}

// Function to print the output
void print_output(){
    std::cout << "Optimum Cost " << cost << std::endl;
    std::cout << "IBFS matrix:" << std::endl;

    for (int row = 0; row < ibfs.size(); row++) {
        for (int col = 0; col < ibfs[row].size(); col++) {
            std::cout << ibfs[row][col] << " ";
        }
        std::cout << std::endl;
    }
}
