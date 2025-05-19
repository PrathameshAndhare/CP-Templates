#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define mod 1000000007
#define int long long int
#define ld long double
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order(index), order_of_key(x)-> cnt < x
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
int N = 100001;
vector<int>fact(N + 1, 1), invFact(N + 1), spf(N + 1), isPrime(N + 1, 1);
int mulMod(int a, int b) { return ((a % mod) * (b % mod)) % mod;}
int powMod(int a, int b) { return b == 0 ? 1 : (b % 2 == 0 ? powMod(mulMod(a, a), b / 2) : mulMod(a, powMod(a, b - 1)));}
int addMod(int a, int b) { return ((a % mod) + (b % mod) + mod) % mod; }
int divMod(int a) { return powMod(a, mod - 2);}
int subMod(int a, int b) { return ((a % mod) - (b % mod) + mod) % mod;}
int binPow(int a, int b) { int res = 1; while(b) { res = (b & 1 ? res * a % mod : res); a = a * a % mod; b >>= 1; } return res; }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
void sieve() { isPrime.resize(N + 1, 1); vector<int>primes; isPrime[0] = isPrime[1] = 0; for (int i = 2; i <= N; i++) if (isPrime[i]) { primes.push_back(i); for (int j = i * i; j <= N; j += i) isPrime[j] = 0; }}
void SPF() { iota(spf.begin(), spf.end(), 0); for (int i = 2; i * i <= N; i++) if (spf[i] == i) for (int j = i * i; j <= N; j += i) spf[j] = min(spf[j], i); }
void precompute() { fact[0] = 1; for (int i = 1; i <= N; i ++) fact[i] = (fact[i - 1] * i) % mod; invFact[N] = powMod(fact[N], mod - 2); for (int i = N - 1; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % mod; }
int NCR(int n, int r) { return (r > n || r < 0) ? 0 : (fact[n] * invFact[r] % mod * invFact[n - r] % mod) % mod; }
void init() {
    #ifndef PRATHAMESH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void bol_bacchan() {
    sieve();
    cout << isPrime[5] << endl;
    
}

signed main() {
    fast
    init();
    int test = 1;
    cin >> test;
    precompute();

    while(test --) {
        bol_bacchan();
    }
}
