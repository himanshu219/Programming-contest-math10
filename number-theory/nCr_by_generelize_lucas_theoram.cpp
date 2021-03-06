//{ Template
using namespace std;
//{ C-headers
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <cfloat>
#include <cctype>
#include <cassert>
#include <ctime>
//}
//{ C++-headers
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
//}
//{ Loops
#define forab(i,a,b) for (__typeof(b) i = (a); i <= (b); ++i)
#define rep(i,n) forab (i, 0, (n) - 1)
#define For(i,n) forab (i, 1, n)
#define rofba(i,a,b) for (__typeof(b) i = (b); i >= (a); --i)
#define per(i,n) rofba (i, 0, (n) - 1)
#define rof(i,n) rofba (i, 1, n)
#define forstl(i,s) for (__typeof ((s).end ()) i = (s).begin (); i != (s).end (); ++i)
//}
//{ Floating-points
#define EPS 1e-10
#define abs(x) (((x) < 0) ? - (x) : (x))
#define zero(x) (abs (x) < EPS)
#define equal(a,b) (zero ((a) - (b)))
#define PI 2 * acos (0.0)
//}
typedef long long int64;
typedef unsigned long long int64u;
#define memo(a,v) memset(a,v,sizeof(a))
#define all(a) a.begin(),a.end()
#define INF 1<<29
#define db double
#define pb push_back
#define pii pair<int64 ,int64 >
#define NL puts("")
#define mx 100005
//{
//Intput_Output
#define II ({ int a; scanf("%d",&a); a;})
#define IL ({ int64 a; scanf("%lld",&a);  a;})
#define ID ({ db a; scanf("%lf",&a);  a;})
#define IC ({ char a; scanf("%c",&a);  a;})
#define IS ({ string a; cin >> a;  a;})
#define ICA(n) ({ char a[n]; scanf("%s",&a);  a;})
#define OC printf("Case %d:",cs);
#define FI freopen("in.txt","r",stdin);
#define FO freopen("out.txt","w",stdout);
//}
//}
template <class T, class U> inline T max (T &a, U &b) {
    return a > b ? a : b;
}
template <class T, class U> inline T min (T &a, U &b) {
    return a < b ? a : b;
}

//int dx[]={1,0,-1,0};int dy[]={0,1,0,-1}; //4 Direction
//int dx[]={1,1,0,-1,-1,-1,0,1};int dy[]={0,1,1,1,0,-1,-1,-1};//8 direction
//int dx[]={2,1,-1,-2,-2,-1,1,2};int dy[]={1,2,2,1,-1,-2,-2,-1};//Knight Direction
//int dx[6]={2,1,-1,-2,-1,1};int dy[6]={0,1,1,0,-1,-1}; //Hexagonal Direction

int64 Pow(int64  b,int64  p) {
    int64  ret = 1;
    while(p) {
        if(p&1) ret *= b ;
        p >>= (1LL) , b *= b ;
    }
    return ret ;
}

pair<int64 ,pair<int64 ,int64 > > eea(int64 a, int64 b) {
    int64 gcd,x=0,y=1;
    int64 u=1, v=0, m, n, q, r;
    gcd = b;
    while (a!=0) {
        q=gcd/a;
        r=gcd%a;
        m=x-u*q;
        n=y-v*q;
        gcd=a;
        a=r;
        x=u;
        y=v;
        u=m;
        v=n;
    }
    return make_pair(gcd,make_pair(x,y));
}

int64 BigMod(int64 B,int64 P,int64 M) {
    int64 R=1;    //compute b^p%m
    while(P>0)  {
        if(P%2==1) {
            R=(R*B)%M;
        }
        P/=2;
        B=(B*B)%M;
    }
    return (int64)R;
}
int64 modInverse_prime(int64 B,int64 P) {
    return BigMod(B,P-2,P);
}
int64 modInverse_relativePrime(int64 B,int64 P) {
    return eea(B,P).second.first;
}

int64 mod;
int64 fact[mx+5];
vector<pii >primeDivisors;

void generatefactorial(int64 p) {
    fact[0] = fact[1 ]= 1;
    int64 i;
    for (i = 2; i < mod; i++) {
        if(i%p==0) fact[i] = fact[i-1];
        else fact[i] =  (fact[i - 1] * i)%mod;
    }
}

vector<int64 > tobase(int64 a,int64 b) {
    vector<int64 >v;
    while(a) {
        v.pb(a%b);
        a /= b;
    }
    return v;
}

vector<int64 > compute_js(vector<int64 >v,int64 p,int64 q) {
    int64 len = v.size();
    vector<int64 >tmp;
    rep(i,len) {
        int64 a = 0,P = 1;
        for(int64 j = i; j<len && j < i+q ; j++) {
            a += (v[j]*P);
            P *= p;
        }
        tmp.pb(a);
    }
    return tmp;
}

vector<int64 > computeE(int64 len,vector<int64 >M,vector<int64 >R,int64 p) {
    int64 m = M.size(),r = R.size(),c = 0;
    vector<int64>tmp;
    forab(i,m,len-1) M.pb(0);
    forab(i,r,len-1) R.pb(0);
    rep(i,len) {
        c += M[i];
        c += R[i];
        c /= p;
        tmp.pb(c);
    }
    per(i,len-1) tmp[i] = tmp[i] + tmp[i+1];
    return tmp;
}



int64 generelize_lucas_theoram(int64 n,int64 r,int64 p,int64 q) {
    int64 m = (n-r);
    vector<int64>N = tobase(n,p);
    vector<int64>R = tobase(m,p);
    vector<int64>M = tobase(r,p);
    vector<int64>N_js = compute_js(N,p,q);
    vector<int64>M_js = compute_js(M,p,q);
    vector<int64>R_js = compute_js(R,p,q);
    int64 n_len = N.size() , m_len = M.size() , r_len = R.size();
    vector<int64 >e =computeE(n_len,R,M,p);
    int64 ans = 1;
    mod = Pow(p,q);
    generatefactorial(p);
    rep(i,e[0]) ans = (ans*p)%mod;
    rep(i,n_len) ans = (ans*fact[N_js[i]%mod])%mod;
    rep(i,m_len) ans = (ans*modInverse_relativePrime(fact[M_js[i]%mod],mod))%mod;
    rep(i,r_len) ans = (ans*modInverse_relativePrime(fact[R_js[i]%mod],mod))%mod;
    if((p != 2 || q<3) && (q<=e.size() && e[q-1]%2)) ans = (-1*ans)%mod;
    return ans<0?ans+mod:ans;
}

void generate_primeDivisors(int64 n) {
    primeDivisors.clear();

    int64 cnt = 0 ;

    while(n % 2 == 0 ) {
        n>>=1 , cnt++;
    }

    if(cnt) primeDivisors.push_back( pii(2,cnt) );

    int sq = sqrt(n) + 1 ;

    for( int i = 3 ; i <= sq ; i += 2 ) {
        cnt = 0 ;
        while(n % i == 0 ) n /= i , cnt++ ;
        if(cnt) primeDivisors.push_back( pii(i,cnt) );
    }

    if(n > 1 ) primeDivisors.push_back( pii(n,1) ) ;
}


int64 Chinese_Remainder_Theorem(vector<int64 >L,int64 m) {
    int i = 0;
    int64 ans = 0;
    forstl(it,primeDivisors) {
        int64 p = Pow((*it).first,(*it).second);
        //cout << p << endl;
        int64 e = ((m/p) * modInverse_relativePrime(m/p,p))%m;
        ans = (ans + (L[i] * e)%m)%m;
        i++;
    }
    //cout << ans << endl;
    return ans<0?ans+m:ans;
}

int main() {
    int64 n ,r ,m = 142857;
    generate_primeDivisors(m);
    //forstl(it,primeDivisors) cout << (*it).first << " " << (*it).second << endl;
    int t = II;
    rep(i,t) {
        n = IL, r = IL;
        vector<int64 >L;
        L.clear();
        forstl(it,primeDivisors) {
            L.pb(generelize_lucas_theoram(n,r,(*it).first,(*it).second));
        }
        cout << Chinese_Remainder_Theorem(L,m) << endl;
    }
}
