int BinaryExponentation(int a,int b){
    int res = 1;
    while(b){
        if(b&1) res *= a,res %= mod;
        a *= a;a %= mod;
        b /= 2;
    }

    return res;
}
