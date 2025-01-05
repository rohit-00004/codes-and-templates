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

int arr[N], seg[4*N], cntMin[4*N];

void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx] = arr[l];
        cntMin[idx] = 1;
        return;
    }

    int mid = (l+r) / 2;

    build(2*idx+1, l, mid);
    build(2*idx+2, mid+1, r);

    seg[idx] = min(seg[2*idx+1], seg[2*idx+2]);
    if(seg[2*idx+1] == seg[2*idx+2]) {
        cntMin[idx] = cntMin[2*idx+1] + cntMin[2*idx+2];
    } else if(seg[2*idx+1] < seg[2*idx+2]) {
        cntMin[idx] = cntMin[2*idx+1];
    } else {
        cntMin[idx] = cntMin[2*idx+2];
    }
    
}

void updateQuery(int idx, int l, int r, int v, int vl) {
    if(v > r or v < l) return;
    if(l == r) {
        seg[idx] = vl;
        cntMin[idx] = 1;
        return;
    }

    int mid = (l+r) / 2;
    
    if(v <= mid) updateQuery(2*idx+1, l, mid, v, vl);
    else updateQuery(2*idx+2, mid+1, r, v, vl);

    seg[idx] = min(seg[2*idx+1], seg[2*idx+2]);
    if(seg[2*idx+1] == seg[2*idx+2]) {
        cntMin[idx] = cntMin[2*idx+1] + cntMin[2*idx+2];
    } else if(seg[2*idx+1] < seg[2*idx+2]) {
        cntMin[idx] = cntMin[2*idx+1];
    } else {
        cntMin[idx] = cntMin[2*idx+2];
    }
    
}

int minQuery(int idx, int l, int r, int gl, int gr) {
    if(l >= gl and r <= gr) return seg[idx];
    if(l > gr or r < gl) return INT_MAX;

    int mid = (l+r) / 2;
    int left = minQuery(2*idx+1, l, mid, gl, gr);
    int right = minQuery(2*idx+2, mid+1, r, gl, gr);

    return min(left, right);
}

int cntMinQuery(int idx, int l, int r, int gl, int gr, int vl) {
    if(l > gr or r < gl) return 0;
    if( (r <= gr or l >= gl) && seg[idx] > vl) return 0;
    if(l >= gl and r <= gr) {
        if(seg[idx] == vl)
            return cntMin[idx];
        return 0;
    }

    int mid = (l+r) / 2;
    int left = cntMinQuery(2*idx+1, l, mid, gl, gr, vl);
    int right = cntMinQuery(2*idx+2, mid+1, r, gl, gr, vl);

    return left + right;
}

void solve(){
    int n, m;
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> arr[i];

    build(0, 0, n-1);

    for(int i=0; i<m; i++) {
        int x, l, r;
        cin >> x >> l >> r;

        if(x == 1) {
            updateQuery(0, 0, n-1, l, r);
        }
        else {
            int mini = minQuery(0, 0, n-1, l, r-1);
            int minCnt = cntMinQuery(0, 0, n-1, l, r-1, mini);
            cout << mini << " " << minCnt << nl;
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
  for(int tc=1; tc<=t; tc++){
    solve();
  }
  
  return 0;
}