/*
North West Corner Method:
Considerations: 1. The problem is balanced i.e supply = demand
                2. There is no value of supply which is same as demand - coded but not tested
Input: Source - no. of sources - int source
       Destination - no. of destinations - int dest
       Matrix input of all the constraints coeffcients - 2D matrix mat
       Supply - supply amount of each source - int 1D array supply
       Demand - demand of each destination - int 1D array demand
Output : Optimum cost - int cost
         Initial basic feasible solution - 2D matrix ibfs
*/

#include <iostream>

int main(){

    int source, dest;

    std::cout << "Enter no. of sources and destination respectively:";
    std::cin >> source >> dest;
    int mat[source][dest];
    std::cout << "Entries of the matrix:";

    //matrix input 
    for (int i=0; i < source; i++) {
        for (int j=0; j < dest; j++) {
            std::cin >> mat[i][j];
        }
    }

    int supply[source];
    int demand[dest];
    int ibfs[source][dest] = {}; 

    //supply and demand value in array
    std::cout << "Enter supply quantity for each source";
    for (int i=0; i < source; i++){
        std::cin >> supply[i];
    }

    std::cout << "Enter demand quantity for each destination";
    for (int k=0; k < dest; k++){
        std::cin >> demand[k];
    }

    //testing if supply==demand
    int supply_sum = 0;
    int demand_sum = 0;
    for (int i=0; i < dest; i++) {
        if (i < source)
            supply_sum+=supply[i];
        demand_sum+=demand[i];
    }

    //needed variables
    int cost = 0;
    int sup = 0;
    int dem = 0;

    //main algo
    while (dem < dest && sup < source && supply_sum == demand_sum) {
        
        if (demand[dem] < supply[sup]) {

            supply[sup] -= demand[dem];
            cost += mat[sup][dem] * demand[dem];
            ibfs[sup][dem] = demand[dem];
            demand[dem] = 0;
            dem++;          

        }

        else if (demand[dem] > supply[sup]) {

            demand[dem] -= supply[sup];
            cost += mat[sup][dem] * supply[sup];
            ibfs[sup][dem] = supply[sup];
            supply[sup] = 0;
            sup++;

        }

        else if (demand[dem] == supply[sup]) {

            cost += mat[sup][dem] * demand[dem];
            ibfs[sup][dem] = demand[dem];
            demand[dem] = 0;
            supply[sup] = 0;
            if(dem == dest-1 && sup == source-1)
                break;
            sup++;
            dem++;
        }
        
    }

    std::cout << "Optimum cost " << cost << std::endl;

    std::cout << "Displaying new matrix" << std::endl;
    for (int i=0; i < source; i++) {
        for (int j=0; j < dest; j++) {
            std::cout << ibfs[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
