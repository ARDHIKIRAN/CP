// [ (a*b) % c ] where a,b,c <= 1e15
int BinaryMultiplication(int a,int b,int c){
    int res = 0;
    while(b){
        if(b&1) res += a,res %= c;
        a += a;a %= c;
        b /= 2;
    }
   return res;
}
