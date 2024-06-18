// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

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
    SegmentTree(vector<int> &v_)
    {
        int n = v_.size();
        v = v_;
        tree.resize(n * 4);
        build(1, 0, n - 1);
    }
    void build(int node, int st, int en)
    {
        if (st == en)
        {
            tree[node] = v[st];
            return;
        }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]); // min segment tree
    }

    void update(int node, int index, int st, int en, int val)
    {
        if (st == en)
        {
            v[index] = val;
            tree[node] = val;
            return;
        }
        int mid = (st + en) / 2;
        if (index <= mid)
        {
            update(node * 2, index, st, mid, val);
        }
        else
        {
            update(node * 2 + 1, index, mid + 1, en, val);
        }
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]); // min segment tree
    }

    int query(int node, int l, int r, int st, int en)
    {
        // l...st..en...r   whole subarray
        if (l <= st && r >= en)
        {
            return tree[node];
        }

        // st..en l..r ||  l..r st..en  out of subarray
        if (en < l || st > r)
        {
            return INT_MAX; //****
        }

        int mid = (st + en) / 2;
        int q1 = query(node * 2, l, r, st, mid);
        int q2 = query(node * 2 + 1, l, r, mid + 1, en);

        return min(q1, q2); // min
    }
};

void test_case()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    SegmentTree *ST = new SegmentTree(v);
    while (m--)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            ST->update(1, x, 0, n - 1, y);
        }
        else
        {
            cout << ST->query(1, x, y - 1, 0, n - 1) << endl;
        }
    }
}

int32_t main()
{
    fastio;
    int t = 1;
    // cin >> t;
    while (t--)
        test_case();
}