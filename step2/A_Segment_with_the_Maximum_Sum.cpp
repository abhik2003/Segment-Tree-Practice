// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

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
    vector<int> v;
    vector<vector<int>> tree;

public:
    SegmentTree(vector<int> &v_)
    {
        int n = v_.size();
        v = v_;
        tree.resize(n * 4);
        build(1, 0, n - 1);
    }
    void combine(int node)
    {
        int l = node * 2;
        int r = node * 2 + 1;

        int sum = tree[l][0] + tree[r][0];
        int max_pre = max(tree[l][1], tree[l][0] + tree[r][1]);
        int max_suf = max(tree[r][2], tree[r][0] + tree[l][2]);
        int maximal_sum = max({tree[l][3], tree[r][3], tree[l][2] + tree[r][1]});

        tree[node] = {sum, max_pre, max_suf, maximal_sum};
    }
    void build(int node, int st, int en)
    {
        if (st == en)
        {
            tree[node] = {v[st], v[st], v[st], v[st]}; // sum, max pref, max suf , maximal sum
            if (v[st] < 0)
            {
                tree[node] = {v[st], 0, 0, 0};
            }
            return;
        }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);

        combine(node);
    }

    void update(int node, int index, int st, int en, int val)
    {
        if (st == en)
        {
            v[index] = val;
            tree[node] = {v[st], v[st], v[st], v[st]};
            if (v[st] < 0)
            {
                tree[node] = {v[st], 0, 0, 0};
            }
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
        combine(node);
    }

    int query()
    {
        // l...st..en...r   whole subarray
        return tree[1][3];
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
    cout << ST->query() << endl;
    while (m--)
    {
        int t, x, y;
        cin >> x >> y;
        ST->update(1, x, 0, n - 1, y);
        cout << ST->query() << endl;
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