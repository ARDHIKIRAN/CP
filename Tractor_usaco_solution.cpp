Problem : https://usaco.org/index.php?page=viewproblem2&cpid=245 

Concept : DSU + Binary Search 

Code : 

 #include<bits/stdc++.h>
using namespace std;


class DSU{
    private:
      vector<int> par , sz;
   public : 
      DSU(int n){
          par.resize(n);
          iota(par.begin() , par.end() , 0);
          sz.resize(n , 1);
      }
      int find(int node){
          if(par[node] == node) return node;    
          return par[node] = find(par[node]);
      }      
      void Union(int x,int y){
          x = find(x);
          y = find(y);
          
          if(x == y) return;
          if(sz[x] < sz[y]) swap(x,y);
          par[y] = x;
          sz[x] += sz[y];
          return;
      }
      int componentBySize(int node){
          return sz[find(node)];
      }
};
 int n;
vector<vector<int>> edges;
bool check(int mid){
     int cost = 0;
     DSU d(n * n);
     int required = ((n * n )+ 1)/2;
     for(auto edge : edges){
        if(edge[2] <= mid){
           d.Union(edge[0] ,edge[1]);
           if(d.componentBySize(edge[0]) >= required){
             return true;
           }
        } else{
            break;
        }
    }
   return false;
}

int main(){
    cin >> n;
    
    int arr[n][n];
    int max_sum = 0;
    
    for(int i = 0 ; i < n ; ++i){
       for(int j = 0 ; j < n ; ++j){
          cin >> arr[i][j];  
          max_sum += arr[i][j];
       }
    }
    
    int dx[4] = {0 , 0 , 1 , -1};
    int dy[4] = {1 , -1 , 0 , 0};
    
    for(int i = 0 ; i < n ; i++){
      for(int j = 0 ; j < n ; j++){

          for(int dir = 0 ; dir < 4; dir++){
             int x = i + dx[dir];
             int y = j + dy[dir];
             if(x >0 && x < n && y >=0 && y < n){
                 int node1 = (n * i) + j;
                 int node2 = (n * x) + y;
                 int wt = abs(arr[i][j] - arr[x][y]);
                 edges.push_back({node1 , node2 , wt});
             }
          }
       }
    }
    
    
    sort(edges.begin() , edges.end() , [&](vector<int> &a,vector<int> &b){
        return a[2] < b[2];
    });
    
    
    int low = 0 , high = max_sum;
    int minCost = high;
    while(low <= high){
      int mid = low + (high - low)/2;
      if(check(mid)){
        minCost = mid;
        high = mid - 1;
      }else{
        low = mid + 1;
      }
    }
    
    cout << minCost << endl;
}
