/*
Vogel's Approximation Method:  
Considerations: 1. The problem is balanced i.e supply = demand
                2. In the case of ambiguity i.e when maximum penalty is same in row as well
                   as column, the procedure is followed considering row penalty.
Input: Source - no. of sources - int source
       Destination - no. of destinations - int dest
       Matrix input of all the constraints coeffcients - 2D vector vect
       Supply - supply amount of each source - 1D vector supply 
       Demand - demand of each destination - 1D vector demand
Output: Optimum cost - int cost
        Initial basic feasible solution - 2D vector ibfs
*/

#include <iostream>
#include <vector>
#include <climits>
#include "input.hpp"

// Finding difference between 2 least values of the row 
void row_least_two_diff (std::vector<std::vector<int>>& vect, std::vector<int>& rowdiff) {
    int first,second;
    for (int i = 0; i < vect.size(); i++) {
        first = INT_MAX;
        second = INT_MAX;
        for (int j = 0; j < vect[i].size(); j++) {
            if ((vect[i][j] < first) && (vect[i][j] != 0)) {
                second = first;
                first = vect[i][j];
            }
            else if ((vect[i][j] <= second) && (vect[i][j] != 0)) {
                second = vect[i][j];
            }
        }

        rowdiff[i] = abs(first - second);
    }
}

// Finding difference between 2 least values of the column
void col_least_two_diff (std::vector<std::vector<int>>& vect, std::vector<int>& coldiff) {
    int first,second;
    bool col_exceed = false;

    for (int j = 0; col_exceed == false; j++) {
        first = INT8_MAX;
        second = INT8_MAX;
        for (int i = 0; i < vect.size(); i++) {
            if (j < vect[i].size()) {

                if ((vect[i][j] < first) && (vect[i][j] != 0)) {
                    second = first;
                    first = vect[i][j];
                }

                else if ((vect[i][j] <= second) && (vect[i][j] != 0)) {
                    second = vect[i][j]; 
                }
            }
            else
            {
                col_exceed = true;
            }
        }
        
        if (col_exceed == false) {
            coldiff[j] = abs(first-second);
        }
    }
}

// Finding penalty index 
int find_penalty_index (std::vector<int> rowdiff, std::vector<int> coldiff) {
    int row_penalty = 0;
    int row_penalty_index = 0;
    int penalty_index = 0;

    for (int i = 0; i < rowdiff.size(); i++) {
        if (row_penalty <= rowdiff[i]) {
            row_penalty = rowdiff[i];
            row_penalty_index = i;
        }
    }

    int col_penalty = 0;
    int col_penalty_index = 0;
    for (int i = 0; i < coldiff.size(); i++) {
        if (col_penalty <= coldiff[i]) {
            col_penalty = coldiff[i];
            col_penalty_index = i;
        }
    }

    return row_penalty >= col_penalty ? row_penalty_index : col_penalty_index;
}

// Setting all entries of the desired row to 0 
void setRow (std::vector<std::vector<int>>& vect, int lowi) {
    for (int i = 0; i < vect[lowi].size(); i++)
        vect[lowi][i] = 0;
}

// Setting all entries of desired column to 0
void setCol (std::vector<std::vector<int>>& vect, int lowj) {
    for (int i = 0; i < vect.size(); i++)  
        vect[i][lowj] = 0;
}

int main() {
    // Function defined in "input.cpp" to take all the necessary inputs
    take_input();

    // Needed variables
    std::vector<int> rowdiff(source, 0);
    std::vector<int> coldiff(dest, 0);
    int penalty;

    // If supply == demand then only the loop will execute 
    while (test_equality()) {

        row_least_two_diff (vect, rowdiff);
        col_least_two_diff (vect, coldiff);
        penalty = find_penalty_index (rowdiff, coldiff);

        // Checks if row difference is >= column difference at the given penalty index
        // Implies max penalty belongs to the rowdiff
        if (rowdiff[penalty] >= coldiff[penalty] || penalty >= dest) {
            int row_min = INT_MAX;
            int row_min_index = -1;

            for (int j = 0; j < vect[penalty].size(); j++) {
                if (row_min >= vect[penalty][j] && vect[penalty][j] != 0) {
                    row_min = vect[penalty][j];
                    row_min_index = j;
                }
            }

            if (row_min_index == -1) break;
            
            // Implies penalty is the index of row with maximum absolute difference
            // row_min_index is the column index of the least element of row
            if (supply[penalty] >= demand[row_min_index]) {
                cost += vect[penalty][row_min_index] * demand[row_min_index];
                ibfs[penalty][row_min_index] = demand[row_min_index];
                setCol(vect, row_min_index);
                supply[penalty] -= demand[row_min_index];
                demand[row_min_index] = 0;
            }

            else {
                cost += vect[penalty][row_min_index] * supply[penalty];
                ibfs[penalty][row_min_index] = supply[penalty];
                setRow(vect, penalty);
                demand[row_min_index] -= supply[penalty];
                supply[penalty] = 0;
            }
        }

        // Checks if column difference > row difference at the given penalty index
        // Implies max penalty belongs to coldiff
        else if (coldiff[penalty] > rowdiff[penalty] || penalty >= source) {
            int col_min = INT_MAX;
            int col_min_index = -1;

            // Finding minimum element in the column
            for (int i = 0; i < vect.size(); i++) {
                if (col_min >= vect[i][penalty] && vect[i][penalty] != 0) {
                    col_min = vect[i][penalty];
                    col_min_index = i;
                }
            }

            if (col_min_index == -1) break;
            
            // penalty is the column index of the least element of the column
            // col_min_index is the row index of minimum element of the column
            if (supply[col_min_index] >= demand[penalty]) {
                cost += vect[col_min_index][penalty] * demand[penalty];
                ibfs[col_min_index][penalty] = demand[penalty];
                setCol(vect, penalty);
                supply[col_min_index] -= demand[penalty];
                demand[penalty] = 0;
            }

            else if (demand[penalty] > supply[col_min_index]) {
                cost += vect[col_min_index][penalty] * supply[col_min_index];
                ibfs[col_min_index][penalty] = supply[col_min_index];
                setRow(vect, col_min_index);
                demand[penalty] -= supply[col_min_index];
                supply[col_min_index] = 0;
            }
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