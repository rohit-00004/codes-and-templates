#include <iostream>
#include <vector>
#include <string>
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

int arr[100005], seg[4*100005];

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = arr[l];
        return;
    }
    int mid = (l+r) / 2;
    build(2*idx + 1, l, mid);
    build(2*idx + 2, mid+1, r);

    seg[idx] = seg[2*idx+1] + seg[2*idx+2];
}

void updateQuery(int idx, int l, int r, int x, int vl) {
    if(l == r) {
        seg[idx] = vl;
        return;
    }
    int mid = (l+r) / 2;
    if(x <= mid) {
        updateQuery(2*idx+1, l, mid, x, vl);
    }
    else updateQuery(2*idx+2, mid+1, r, x, vl);
    seg[idx] = seg[2*idx+1] + seg[2*idx+2];
}

int sumQuery(int idx, int l, int r, int gl, int gr) {
    if(gr < l or gl > r) return 0;
    if(l >= gl and r <= gr) return seg[idx];

    int mid = (l+r) / 2;
    return sumQuery(2*idx+1, l, mid, gl, gr) + sumQuery(2*idx+2, mid+1, r, gl, gr);
}

void solve(){
    int n, m;
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> arr[i];

    build(0, 0, n-1);

    for(int i=0; i<m; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1) updateQuery(0, 0, n-1, l, r);
        else cout << sumQuery(0, 0, n-1, l, r-1) << nl;
    }
}

int32_t main(){
  fastio()
  #ifndef ONLINE_JUDGE
  freopen("Input.txt", "r", stdin);
  freopen("Output.txt", "w", stdout);
  #endif

  int t=1;
//   cin >> t;
  for(int tc=1; tc<=t; tc++){
    solve();
  }
  
  return 0;
}