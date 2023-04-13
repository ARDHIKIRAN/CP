#include<bits/stdc++.h>
using namespace std;
int main(){

    // Prefix sum for 1d array
    int nn;
    cin >> nn;
    int arr[nn+1] = {0};
    for(int i=1;i<=nn;i++){
        cin >> arr[i];
        arr[i] += arr[i-1];
    }


    int qq;
    cin >> qq;

    while(qq--){
        int l,r;
        cin >> l >> r;
        // sum of arr[l....r] = arr[r] - arr[l-1]
        cout << arr[r] - arr[l-1] << '\n';
    }




    // for 2d array prefix sum


    int n,m;
    cin >> n >> m;


    vector<vector<int>> arr(n+1,vector<int>(m+1,0));
    vector<vector<int>> pref(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> arr[i][j];

            pref[i][j] = arr[i][j] +  pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1]; 
        }    
    }

    int q;
    cin >> q;

    while(q--){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
 
        // finding the sum from (x1,y1)[Top Most] to (x2,y2) [Bottom most]
        cout << pref[x2][y2] - pref[x1-1][y2] - pref[x2][y1-1] + pref[x1-1][y1-1] << '\n';          

    }
}
