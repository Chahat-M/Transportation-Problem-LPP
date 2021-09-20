/*
North West Corner Method:
Considerations: 1. The problem is balanced i.e supply = demand
                2. There is no value of supply which is same as demand - coded but not tested
Input: Source - no. of sources - int source
       Destination - no. of destinations - int dest
       Matrix input of all the constraints coeffcients - 2D vector vect
       Supply - supply amount of each source - 1D vector supply
       Demand - demand of each destination - 1D vector demand
Output : Optimum cost - int cost
         Initial basic feasible solution - 2D vector ibfs
*/

#include <iostream>
#include <vector>
#include "input.hpp"

int main(){
    // Function defined in "input.cpp" to take all the necessary inputs
    take_input();

    // Needed variables
    int sup = 0;
    int dem = 0;

    // Main algo
    while (dem < dest && sup < source && test_equality()) {
        
        if (demand[dem] < supply[sup]) {

            supply[sup] -= demand[dem];
            cost += vect[sup][dem] * demand[dem];
            ibfs[sup][dem] = demand[dem];
            demand[dem] = 0;
            dem++;          

        }

        else if (demand[dem] > supply[sup]) {

            demand[dem] -= supply[sup];
            cost += vect[sup][dem] * supply[sup];
            ibfs[sup][dem] = supply[sup];
            supply[sup] = 0;
            sup++;

        }

        else if (demand[dem] == supply[sup]) {

            cost += vect[sup][dem] * demand[dem];
            ibfs[sup][dem] = demand[dem];
            demand[dem] = 0;
            supply[sup] = 0;
            if(dem == dest-1 && sup == source-1)
                break;
            sup++;
            dem++;
        }
        
    }
    
    if (!test_equality()){
        std::cout << "The given problem is unbalanced" << std::endl;
        std::cout << "Kindly enter valid inputs" << std::endl;
    }
    
    // Function defined in "input.cpp" to print the output
    else
        print_output();

    return 0;
}
