/*
Least Cost Cell Method:
Considerations: The problem is balanced i.e supply = demand
                There is no value of supply which is same as demand (if so, then demand value is taken) - coded but not tested
Input: Source - no. of sources - int source
       Destination - no. of destinations - int dest
       Matrix input of all the constraints coeffcients - 2D vector vect
       Supply - supply amount of each source - 1D vector supply
       Demand - demand of each destination - 1D vector demand
Output : Optimum cost - int cost
         Initial basic feasible solution - 2D matrix ibfs
*/

#include <iostream>
#include <vector>
#include <climits>
#include "input.hpp"

//  Setting all entries of the desired row to 0 
void setRow (std::vector<std::vector<int>>& vect, int lowi) {
    for (int i = 0; i < vect[lowi].size(); i++)
        vect[lowi][i] = 0;
}

//  Setting all entries of desired column to 0
void setCol (std::vector<std::vector<int>>& vect, int lowj) {
    for (int i = 0; i < vect.size(); i++)  
        vect[i][lowj] = 0;
}

//  To check if all supplies = 0 (req for break condition)
int supply_check (std::vector<int> supply, int source) {
    int sup = 0;
    for (int i = 0; i < source; i++) {
        if (supply[i] != 0)
            sup++;
    }
    return sup;
}

//  To check if all demands = 0 (req for break condition)
int demand_check (std::vector<int> demand, int dest) {
    int dem = 0;
    for (int i = 0; i < dest; i++) {
        if (demand[i] != 0)
            dem++;
    }
    return dem;
}


int main(){
    // Function defined in "input.cpp" to take all the necessary inputs
    take_input();

    // Needed variables
    int low;
    int lowi = 0;
    int lowj = 0;

    // If supply == demand then only the loop will execute
    while (test_equality()) {
    
        low = INT_MAX;

        if (supply_check(supply, source) == demand_check(demand, dest) && supply_check(supply, source) == 0)
            break;

        //  Finding the least element in the matrix
        for (int row = 0; row < vect.size(); row++) {
            for (int col = 0; col < vect[row].size(); col++) {
                if (low > vect[row][col] && vect[row][col] != 0) {
                    low = vect[row][col];
                    lowi = row;
                    lowj = col;
                }
            }
        }

        if (supply[lowi] < demand[lowj]) {
            cost += vect[lowi][lowj] * supply[lowi];
            ibfs[lowi][lowj] = supply[lowi];
            setRow(vect,lowi);
            demand[lowj] -= supply[lowi];
            supply[lowi] = 0;
        }
   
        else if (supply[lowi] > demand[lowj]) {
            cost += vect[lowi][lowj] * demand[lowj];
            ibfs[lowi][lowj] = demand[lowj];
            setCol(vect,lowj);
            supply[lowi] -= demand[lowj];
            demand[lowj] = 0;
        }
   
        // When supply[lowi] is equal to demand[lowj]
        else {
            cost += vect[lowi][lowj] * demand[lowj];
            ibfs[lowi][lowj] = demand[lowj];
            setRow(vect, lowi);
            setCol(vect, lowj);
            demand[lowj] = 0;
            supply[lowi] = 0;
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