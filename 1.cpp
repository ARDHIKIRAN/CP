bool Isprime(int n){
    if(n < 2) return false;
    for(int x=2;x*x<=n;x++){
        if(n % x == 0){
            return false;
        }
    }
   return true;
}
vector<int> Factors(int n){
    vector<int> f;

    for(int x=2;x*x<=n;x++){
        while(n % x == 0){
            f.push_back(x);
            n /= x;
        }
    }
    if(n>1) f.push_back(n);
    return f;
}
int NoOfPrimeNumbers(int n){
    return n / log10(n);
    //n=1e6......total prime number exists = 78498
}
//time complexity : O(n*log(log(n)))
void sieveOfEratosthenes(int n) {
    vector<int> sieve(n+1,0);
    for(int x=2;x<=n;x++){
        if(sieve[x]) continue;
        for(int u=2*x;u<=n;u+=x){
            sieve[u] = 1;
        }
    }
}
//Euclid Alogorithm to find gcd(a,b) 
// lcm(a,b) = a*b/gcd(a,b)
//time complexity : O(log(n))
int gcd(int a,int b){
    if(b == 0) return a;
     return gcd(b,a%b);
}
int lcm(int a,int b){
    return a*b / gcd(a,b);
}


//Extended euclidean algorithm 
// ax + by = gcd(a,b)
// to find the value of {x,y,gcd(a,b)}
vector<int> ExtendedEuclidean(int a,int b){
    if(b == 0) return {1,0,a};
    vector<int> SubAns = ExtendedEuclidean(b,a%b);
    return {SubAns[1],SubAns[0]-(a/b)*SubAns[1],SubAns[2]};
   
}


// Modular Exponentiation
// to Find the value of (x ^ n) % m in log(n) time complexity
long long modpow(int x,int n,int m){
    if(n == 0) return 1%m;
    long long u = ModPow(x,n/2,m);
    u = (u*u) % m;
    if(n % 2 == 1) u = (u*x) % m;
    return u;
}


//Modular Multiplicative Inverses
//x * inv(x) % m == 1

// if m = prime
//inv(x) = x ^(m-2)
int inv(int x,int m){
    return modpow(x,m-2,m);
}
















