#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
using namespace std;

#pragma GCC optimize "trapv"
#define ll long long
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
const int N = 1e5+5;

struct item {
    int val, cnt;
};

struct segtree {
    vector<item> values;

    void init(int n) {
        values.resize(4*n);
    }

    item single(int v) {
        return {v, 1};
    }

    item merge(item a, item b) {
        if(a.val < b.val) return a;
        if(a.val > b.val) return b;
        return {a.val, a.cnt + b.cnt};
    }

    void build(int idx, int l, int r, vector<int>& arr) {
        if(l == r) {
            values[idx] = single(arr[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(2*idx+1, l, mid, arr);
        build(2*idx+2, mid+1, r, arr);

        values[idx] = merge(values[2*idx+1], values[2*idx+2]);
    }

    void update(int idx, int l, int r, int v, int vl) {
        if(l == r) {
            values[idx] = single(vl);
            return;
        }

        int mid = (l+r) / 2;

        if(v <= mid) update(2*idx+1, l, mid, v, vl);
        else update(2*idx+2, mid+1, r, v, vl);

        values[idx] = merge(values[2*idx+1], values[2*idx+2]);
    }

    item calc(int idx, int l, int r, int gl, int gr) {
        if(l > gr or r < gl) return {INT_MAX, 0};
        if(l >= gl and r <= gr) return values[idx];

        int mid = (l + r) / 2;
        item left = calc(2*idx+1, l, mid, gl, gr);
        item right = calc(2*idx+2, mid+1, r, gl, gr);

        return merge(left, right);
    }
};

void solve(){
    int n, m;
    cin >> n >> m;

    segtree st;

    vector<int> arr(n);
    st.init(n);
    for(int i=0; i<n; i++) cin >> arr[i];

    st.build(0, 0, n-1, arr);
    for(int i=0; i<m; i++) {
        int x, l, r;
        cin >> x >> l >> r;

        if(x == 1) st.update(0, 0, n-1, l, r);
        else {
            item res = st.calc(0, 0, n-1, l, r-1);
            cout << res.val << " " << res.cnt << nl;
        }
    }
}

int main(){
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