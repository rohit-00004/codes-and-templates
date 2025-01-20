#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cstdint>
#include <set>
using namespace std;

#pragma GCC optimize "trapv"
#define ll long long
#define int ll
#define nline cout << "\n"
#define nl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pii pair<int, int>
#define db(str, x) cout << str << " = " << x << nline;
#define dbv(a)        for(auto it: a)cout<<it<<" "; cout << nline;
#define db1(a)        cout<<a<<"\n";
#define db2(a,b)      cout<<a<<" "<<b<<"\n";
#define db3(a,b,c)    cout<<a<<" "<<b<<" "<<c<<"\n";
#define fastio() ios_base::sync_with_stdio(false);cin.tie(0);

const int M = 1e9+7;
const int N = 300005;

/*
https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/A
*/
struct dsu {
  vector<int> parent;
  dsu(int n) {
    parent.resize(n+1);
    for(int i=0; i<=n; i++)
      parent[i] = i;
  }

  int find_par(int n) {
    if(n == -1) return -1;
    if(n == parent[n]) return n;
    return parent[n] = find_par(parent[n]);
  }

  void unite(int a, int b) {
    a = find_par(a);
    b = find_par(b);
    if(a != b) {
      parent[a] = b;
    }
  }
};

void solve(){
  int n, m;
  cin >> n >> m;

  dsu ds(n);

  for(int i=1; i<=m; i++) {
    char c;
    int x;
    cin >> c >> x;

    if(c == '-') {
      if(x < n) ds.unite(x, x+1);
      else ds.unite(x, -1);
    } else {
      int par = ds.find_par(x);
      cout << par << nl;
    }

  }
}

int32_t main(){
  fastio()
  #ifndef ONLINE_JUDGE
  freopen("Input.txt", "r", stdin);
  freopen("Output.txt", "w", stdout);
  #endif

  int t=1;
  // cin >> t;
  for(int tc=1; tc<=t; tc++){
    solve();
  }

  return 0;
}