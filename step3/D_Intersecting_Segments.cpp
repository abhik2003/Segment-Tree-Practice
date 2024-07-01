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

        tree[node] = tree[node * 2] + tree[node * 2 + 1]; // sum segment tree
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
        tree[node] = tree[node * 2] + tree[node * 2 + 1]; // sum segment tree
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
            return 0;
        }

        int mid = (st + en) / 2;
        int q1 = query(node * 2, l, r, st, mid);
        int q2 = query(node * 2 + 1, l, r, mid + 1, en);

        return q1 + q2; // sum
    }
};

static bool comp(vector<int> &a, vector<int> &b)
{
    return a[1] < b[1];
}
void test_case()
{
    int n;
    cin >> n;
    vector<int> aux(2 * n);
    vector<int> v(2 * n);
    SegmentTree *S = new SegmentTree(aux);
    vector<vector<int>> interval(n, vector<int>(2, -1));

    for (int i = 0; i < 2 * n; i++)
    {
        cin >> v[i];
        if (interval[v[i] - 1][0] == -1)
            interval[v[i] - 1][0] = i; // 1st occurance
        else
            interval[v[i] - 1][1] = i; // second occurance
    }

    sort(interval.begin(), interval.end(), comp); // sort intervals wrt second occurance

    vector<int> ans(n);

    for (auto it : interval)
    {
        int l = it[0];
        int r = it[1];

        //intersecting segment previous problem
        int cnt = S->query(1, l, r, 0, 2 * n - 1); // find how many interval's 1st occurence occur in this interval as it is guaranteed right occurence is less than r
        
        ans[v[r] - 1] = (r - 1 - l) - 2 * cnt; //total segment size - 2*intersecting interval

        S->update(1, l, 0, 2 * n - 1, 1); // mark the left occurance as visted so that it is considerred for the next intervals
    }
    for (int x : ans)
        cout << x << " ";
}

int32_t main()
{
    fastio;
    int t = 1;
    // cin >> t;
    while (t--)
        test_case();
}