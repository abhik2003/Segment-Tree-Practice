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
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);
#define endl '\n';
#define __builtin_popcount(x) __builtin_popcountll(x)
#define int long long
using namespace std;
 
const int INF=1e8;
const int M=1e9+7;

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
            tree[node] = v[st]; // if v[st]=1 , number of one is 1 else 0
            return;
        }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);

        tree[node] = tree[node * 2] + tree[node * 2 + 1]; // total ones is sum of two children node
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
        tree[node] = tree[node * 2] + tree[node * 2 + 1]; // total ones is sum of two children node
    }

    int query(int node, int k, int st, int en)
    {
        if (k > tree[node])
            return -1; // answer does not exist

        if (st == en)
            return st; // ans found
        int mid = (st + en) / 2;
        int q1 = query(node * 2 + 1, k, mid + 1, en);

        if (q1 != -1)
        {
            return q1; // answer found in the right half
        }

        int q2 = query(node * 2 , k - tree[node * 2 + 1], st, mid); // search on left half

        return q2;
    }
};

void test_case()
{
    int n;
    cin >> n;
    vector<int> v(n, 1),a(n);
    SegmentTree *S = new SegmentTree(v);

    for (int i = 0; i < n;i++){
        cin >> a[i];
    }
    
    for (int i = n-1; i >= 0;i--){
        // find a[i]+1 th 1 from right
        int q = S->query(1, a[i]+1, 0, n - 1);
        a[i] = q + 1;
        // cout << q + 1 <<" ";

        // update qth index as 0 ....means visted
        S->update(1, q, 0, n - 1, 0);
    }
    for(int x : a)
        cout << x << " ";
}

int32_t main(){
    fastio;
    int t=1;
    while(t--)
        test_case();
}