#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7, maxn = 1e6 + 10, b = 313; 
long long rhash[maxn], lhash[maxn];
string s;  
int n; 
vector<long long> len; 
long long bpow(long long a, long long p) 
{
    if(p == 1) return a; 
    if(p == 0) return 1; 

    long long t = bpow(a, p/2); 
    return (((t * t) % mod) * bpow(a, p%2)) % mod; 
}
void input ()
{
    cin >> s; 
    n = s.size(); 
}
bool check (int l) 
{
    long long com = lhash[l - 1]; 
    for (int i = 1; i <= n - l - 1; i ++) {
        long long q = rhash[i] - ((rhash[i + l] * bpow(b, l))); 
        q %= mod; q += mod; q %= mod; 
        if(q == com) return true; 
    }

    return false; 
}
void solve ()
{
    lhash[0] = int(s[0]); 
    rhash[n - 1] = int(s[n - 1]); 

    for (int i = 1; i <= n - 1; i ++) {
        lhash[i] = lhash[i - 1] + (bpow(b, i) * int(s[i])); 
        lhash[i] %= mod; 
    }
    for (int i = n - 2; i >= 0; i -- ){
        rhash[i] = rhash[i + 1] * b; rhash[i] %= mod; 
        rhash[i] += int(s[i]); rhash[i] %= mod; 
    }
    for (int i = 0; i <= n - 2; i ++) {
        if(lhash[i] == rhash[n - i - 1]) len.push_back(i + 1); 
    }
    
}
int main ()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    input ();
    solve (); 
}