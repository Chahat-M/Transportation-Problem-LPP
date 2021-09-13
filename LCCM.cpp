/*
Least Cost Cell Method:
Considerations: The problem is balanced i.e supply = demand
                There is no value of supply which is same as demand (if so, then demand value is taken) - coded but not tested
Input: Source - no. of sources - int source
       Destination - no. of destinations - int dest
       Matrix input of all the constraints coeffcients - 2D vector vect
       Supply - supply amount of each source - int 1D array supply
       Demand - demand of each destination - int 1D array demand
Output : Optimum cost - int cost
         Initial basic feasible solution - 2D matrix ibfs
*/

#include <iostream>
#include <vector>
#include <climits>

//  Setting all entries of the desired row to 0 
void setRow (std::vector<std::vector<int>>& vect, int lowi) {
    for (int i=0; i < vect[lowi].size(); i++)
        vect[lowi][i] = 0;
}

//  Setting all entries of desired column to 0
void setCol (std::vector<std::vector<int>>& vect, int lowj) {
    for (int i=0; i < vect.size(); i++)  
        vect[i][lowj] = 0;
}

//  To check if all supplies = 0 (req for break condition)
int supply_check (int supply[], int source) {
    int sup = 0;
    for (int i=0; i < source; i++) {
        if (supply[i] != 0)
            sup++;
    }
    return sup;
}

//  To check if all demands = 0 (req for break condition)
int demand_check (int demand[], int dest) {
    int dem = 0;
    for (int i=0; i < dest; i++) {
        if (demand[i] != 0)
            dem++;
    }
    return dem;
}


int main(){
    
    int source, dest;
    std::cout << "Enter no. of sources and destination respectively:";
    std::cin >> source >> dest;

    std::vector<std::vector<int>> vect(source,std::vector<int> (dest));
    std::vector<std::vector<int>> ibfs(source, std::vector<int> (dest,0));
  
    //  Matrix input in std::vector form
    std::cout << "Entries of the matrix:";
    for (int i=0; i < source; i++) {
        for (int j=0; j < dest; j++) {
            std::cin >> vect[i][j];
        }
    }

    int supply[source];
    int demand[dest];

    std::cout << "Enter supply quantity for each source";
    for (int i=0; i < source; i++){
        std::cin >> supply[i];
    }

    std::cout<<"Enter demand quantity for each destination";
    for (int i=0; i < dest; i++) {
        std::cin >> demand[i];
    }

    // Testing if supply==demand
    int supply_sum = 0;
    int demand_sum = 0;

    for (int i=0; i < dest; i++) {
        if (i < source) {
            supply_sum += supply[i];
        }
        demand_sum += demand[i];
    }
  
    // Needed variables
    int low = INT_MAX;
    int lowi = 0;
    int lowj = 0;
    int cost = 0;

    while (supply_sum == demand_sum ) {
    
        low=INT_MAX;

        if (supply_check(supply,source) == demand_check(demand,dest) && supply_check(supply,source)==0)
            break;

        //  Finding the least element in the matrix
        for (int row=0; row < vect.size(); row++) {
            for (int col=0; col < vect[row].size(); col++) {
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


    std::cout << "Optimum Cost " << cost << std::endl;
    std::cout << "IBFS matrix:" << std::endl;

    for (int row=0; row < ibfs.size(); row++) {
        for (int col=0; col < ibfs[row].size(); col++) {
            std::cout << ibfs[row][col] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
      
}