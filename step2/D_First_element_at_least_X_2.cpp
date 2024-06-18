// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/D

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
            tree[node] = v[st]; // maximum
            return;
        }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]); // maximum element
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
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]); // maximum element
    }

    int query(int node, int k, int st, int en, int left)
    {
        if (k > tree[node])
            return -1; // answer does not exist

        if (en < left)
            return -1;

        if (st == en)
            return st; // ans found

        int mid = (st + en) / 2;
        int q1 = query(node * 2, k, st, mid, left);

        if (q1 != -1)
        {
            return q1; // answer found in the left half
        }

        int q2 = query(node * 2 + 1, k, mid + 1, en, left); // search on right half

        return q2;
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
        cin >> t;
        if (t == 1)
        {
            int i, v;
            cin >> i >> v;
            ST->update(1, i, 0, n - 1, v);
        }
        else
        {
            int x, l;
            cin >> x >> l;
            cout << ST->query(1, x, 0, n - 1, l) << endl; // x+1 because in the qn 1s is starting from 0
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