/*
Least Cost Cell Method:
Considerations: The problem is balanced i.e supply = demand
                There is no value of supply which is same as demand (if so, then demand value is taken) - coded but not tested
Input: Source - no. of sources - int
       Destination - no. of destinations - int
       Matrix input of all the constraints coeffcients - 2D matrix mat
       Supply - supply amount of each source - int array
       Demand - demand of each destination - int array
Output : Optimum cost - int
         Initial basic feasible solution - 2D matrix IBFS
Challenge : 1. Make other entries 0 of same matrix mat instead of IBFS
               But while doing so, final outcome turns out to be the last cell value only
            2. reduce time complexity for iterating in the matrix vect
*/

#include <iostream>
#include <vector>
using namespace std;

//method to set all entries of the desired row to 0 
vector<vector<int>> setRow(vector<vector<int>> vect,int lowi){
  for(int i=0;i<vect[lowi].size();i++)
     vect[lowi][i]=0;
  return vect;
}

//method to set all entries of desired column to 0
vector<vector<int>> setCol(vector<vector<int>> vect,int lowj){
  for(int i=0;i<vect.size();i++)
     vect[i][lowj]=0;
  return vect;
}

//to check if all supplies = 0 (req for break condition)
int supply_check(int supply[],int source){
  int sup=0;
   for(int i=0;i<source;i++){
     if(supply[i] != 0)
       sup++;
    }
  return sup;
}

//to check if all demands = 0 (req for break condition)
int demand_check(int demand[],int dest){
  int dem=0;
   for(int i=0;i<dest;i++){
     if(demand[i] != 0)
       dem++;
    }
  return dem;
}


int main(){
    
    int source,dest;
    cout << "Enter no. of sources and destination respectively:";
    cin>>source>>dest;

    vector<vector<int>> vect(source,vector<int> (dest));
    vector<vector<int>> ibfs(source, vector<int> (dest,0));
  
    //matrix input in vector form
    cout<<"Entries of the matrix:";
    for(int i=0;i<source;i++){
        for(int j=0;j<dest;j++){
            cin>>vect[i][j];
        }
    }

    int supply[source];
    int demand[dest];

    cout<<"Enter supply quantity for each source";
    for (int i=0;i<source;i++){
        cin>>supply[i];
    }

    cout<<"Enter demand quantity for each destination";
    for (int i=0;i<dest;i++){
        cin>>demand[i];
    }

    //testing if supply==demand
    int supply_sum=0;
    int demand_sum=0;

    for(int i=0;i<dest;i++){
        if(i<source){
            supply_sum+=supply[i];
        }
        demand_sum+=demand[i];
    }
  
    //needed variables
    int low = INT8_MAX;
    int lowi=0;
    int lowj=0;
    int cost=0;

    while(supply_sum == demand_sum ){
    
        low=INT8_MAX;

        if(supply_check(supply,source) == demand_check(demand,dest) && supply_check(supply,source)==0)
            break;

        // finding the least element in the matrix
        for(int row=0;row<vect.size();row++){
            for(int col=0;col<vect[row].size();col++){
                if(low > vect[row][col] && vect[row][col] != 0){
                    low = vect[row][col];
                    lowi = row;
                    lowj = col;
                }
            }
        }

        if(supply[lowi] < demand[lowj]){
            cost += vect[lowi][lowj] * supply[lowi];
            ibfs[lowi][lowj] = supply[lowi];
            vect = setRow(vect,lowi);
            demand[lowj] -= supply[lowi];
            supply[lowi] = 0;
        }
   
        else if(supply[lowi] > demand[lowj]){
            cost += vect[lowi][lowj] * demand[lowj];
            ibfs[lowi][lowj] = demand[lowj];
            vect = setCol(vect,lowj);
            supply[lowi] -= demand[lowj];
            demand[lowj] = 0;
        }
   
        else if(supply[lowi] == demand[lowj]){
            cost += vect[lowi][lowj] * demand[lowj];
            ibfs[lowi][lowj] = demand[lowj];
            vect = setRow(vect,lowi);
            vect = setCol(vect,lowj);
            demand[lowj]=0;
            supply[lowi]=0;
        }
    }


    cout<<"Optimum Cost "<<cost<<endl;
    cout<<"IBFS matrix:"<<endl;

    for(int row=0;row<ibfs.size();row++){
        for(int col=0;col<ibfs[row].size();col++){
            cout<<ibfs[row][col]<<" ";
        }
        cout<<endl;
    }

    return 0;
      
}