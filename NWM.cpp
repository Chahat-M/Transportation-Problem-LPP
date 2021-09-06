/*
North West Corner Method:
Considerations: The problem is balanced i.e supply = demand
                There is no value of supply which is same as demand - coded but not tested
Input: Source - no. of sources - int
       Destination - no. of destinations - int
       Matrix input of all the constraints coeffcients - 2D matrix mat
       Supply - supply amount of each source - int array
       Demand - demand of each destination - int array
Output : Optimum cost - int
         Initial basic feasible solution - 2D matrix IBFS
Challenge : Make other entries 0 of same matrix mat instead of IBFS
*/

#include <iostream>
using namespace std;

/*void input(){
    int source,dest;

    cout<<"Enter no. of sources and destination respectively:";
    cin >> source >> dest;
    int mat[source][dest];
    cout<<"Entries of the matrix:";

    //matrix input 
    for(int i=0;i<source;i++){
        for(int j=0;j<dest;j++){
            cin>>mat[i][j];
        }
    }
}*/

int main(){

int source,dest;

cout<<"Enter no. of sources and destination respectively:";
cin >> source >> dest;
int mat[source][dest];
cout<<"Entries of the matrix:";

//matrix input 
for(int i=0;i<source;i++){
    for(int j=0;j<dest;j++){
        cin>>mat[i][j];
    }
}

int supply[source];
int demand[dest];
int IBFS[source][dest] = {}; 

//supply and demand value in array
cout<<"Enter supply quantity for each source";
for (int i=0;i<source;i++){
  cin>>supply[i];
}

cout<<"Enter demand quantity for each destination";
for (int k=0;k<dest;k++){
  cin>>demand[k];
}

//testing if supply==demand
int supply_sum=0;
int demand_sum=0;
for(int i=0;i<dest;i++){
   if(i<source){
      supply_sum+=supply[i];}
   demand_sum+=demand[i];
}

//needed variables
int cost = 0;
int sup=0;
int dem=0;

//main algo
while(dem<dest && sup<source && supply_sum==demand_sum){
    
    if(demand[dem] < supply[sup]){
        supply[sup]-=demand[dem];
        cost += mat[sup][dem] * demand[dem];
        //mat[sup][dem]=demand[dem];
        IBFS[sup][dem] = demand[dem];
        demand[dem]=0;
        dem++;          
    }

    else if(demand[dem]>supply[sup]){
        demand[dem]-=supply[sup];
        cost += mat[sup][dem] * supply[sup];
        //mat[sup][dem]=supply[sup];
        IBFS[sup][dem] = supply[sup];
        supply[sup]=0;
        sup++;
    }

    else if(demand[dem]==supply[sup]){
        cost += mat[sup][dem] * demand[dem];
        //mat[sup][dem]=demand[dem];
        IBFS[sup][dem] = demand[dem];
        demand[dem]=0;
        supply[sup]=0;
        if(dem == dest-1 && sup == source-1)
            break;
        sup++;
        dem++;
    }
    
}

cout<<"Optimum cost "<<cost<<endl;

cout<<"Displaying new matrix"<<endl;
for(int i=0;i<source;i++){
    for(int j=0;j<dest;j++){
        cout<<IBFS[i][j]<<" ";
    }
    cout<<endl;
}

return 0;
}
