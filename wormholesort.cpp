Problme : Wormhole Sort 

Link : https://usaco.org/index.php?page=viewproblem2&cpid=992 

Tag : DSU + Binary Search

Code : 
#include<bits/stdc++.h>
using namespace std;
#define int long long int 

class DSU{
      vector<int> par,sz;
    public:
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
          
          if(x ==y) return;
          
          if(sz[x] < sz[y]) swap(x,y);
          par[y] = x;
          sz[x] += sz[y];
       }
};

bool check(int mid , int n , vector<int> &pos , vector<vector<int>> &edges){
    DSU d(n+1);
    for(auto edge : edges){
      if(edge[2] >= mid){
         d.Union(edge[0] , edge[1]);
      }
    }
    
    for(int i = 0 ; i < n ; ++i){
       if(d.find(i+1) != d.find(pos[i])){
          return false;
       }
    }
    return true;
}




int32_t main(){
   int n,m,x,y,wt,maxW = 0;
   cin >> n >> m;
   vector<int> pos(n);
   bool flag = true;
   for(int i = 0 ; i < n ; ++i){
     cin >> pos[i];
     if(i+1 != pos[i]) flag = false;
   }
   if(flag){
      cout << "-1\n";
      return 0;
   }
   
   vector<vector<int>> edges;
   for(int i = 0 ; i < m ; i++){
        cin >> x >> y >> wt;
        edges.push_back({x,y,wt});
        maxW = max(maxW , wt);
   }
   
   int low = 0 , high = maxW;
   int ans = maxW;
   
   while(low <= high){
       int mid = low + (high - low)/2;
       
       if(check(mid , n , pos , edges)){
           ans = mid;
           low = mid + 1; 
       }else{
         high = mid - 1;
       }
   }
   
   cout << ans << endl;
   
}
