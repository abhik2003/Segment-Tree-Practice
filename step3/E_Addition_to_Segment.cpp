#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <bitset>
#include <fstream>
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);
#define endl '\n';
#define __builtin_popcount(x) __builtin_popcountll(x)
#define int long long
using namespace std;

const int INF = 1e8;
const int M = 1e9 + 7;

class SegmentTree
{
    vector<int> v, tree;

public:
    SegmentTree(int n)
    {
        tree.resize(n * 4);
    }


    void update(int node, int l, int r, int st, int en, int val)
    {
        // l...st..en...r   whole subarray
        if (l <= st && r >= en)
        {
            tree[node] += val;  //all elements in this subarray will be increamented 
            return;
        }
        // st..en l..r ||  l..r st..en  out of subarray
        if (en < l || st > r)
        {
            return;
        }

        int mid = (st + en) / 2;

        update(node * 2, l, r, st, mid, val);
        update(node * 2 + 1, l, r, mid + 1, en, val);
    }

    int query(int node, int st, int en, int ind)
    {
        if (st == en)
        {
            return tree[node];
        }

        int ans = tree[node]; //contibution from current node
        int mid = (st + en) / 2;
        if (ind <= mid)
            ans += query(node * 2, st, mid, ind);
        else
            ans += query(node * 2 + 1, mid + 1, en, ind);

        return ans;
    }
};

void test_case()
{
    int n, m;
    cin >> n >> m;
    SegmentTree *S = new SegmentTree(n);
    while(m--){
        int t;
        cin >> t;
        if(t==1){
            int l, r, inc;
            cin >> l >> r >> inc;
            S->update(1, l, r - 1, 0, n - 1, inc);
        }
        else{
            int i;
            cin >> i;
            cout << S->query(1, 0, n - 1, i) << endl;
        }
    }
}

int32_t main()
{
    fastio;
    int t = 1;
    while (t--)
        test_case();
}