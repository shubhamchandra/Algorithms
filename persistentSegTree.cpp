#include <bits/stdc++.h>
using namespace std;

/* Author : Shubham Chandra */
/* Persistent segment tree */
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/greedy-chairmanaugclash/

const long long mod = 1e9 + 7;
const int maxn = 2e5 + 5;

struct node {
    int cnt;
    node *l, *r;
    node() : l(NULL), r(NULL), cnt(0) {}
};

node *merge(node *l, node *r) {
    node *n = new node();
    n->l = l;
    n->r = r;
    n->cnt = l->cnt + r->cnt;
    return n;
}

node *build(int tp, int tl, int tr) {
    if(tl == tr) return new node();
    int tm = (tl + tr) / 2;
    return merge(build(2*tp, tl, tm), build(2*tp + 1, tm + 1, tr));
}

node *update(node *prev, int tp, int tl, int tr, int idx) {
    if(idx < tl || idx > tr) return prev;
    node *n;
    if(tl == tr) {
        n = new node();
        n->cnt = prev->cnt + 1;
        return n;
    }
    int tm = (tl + tr) / 2;
    return merge(update(prev->l, 2*tp, tl, tm, idx), update(prev->r, 2*tp + 1, tm + 1, tr, idx));
}

long long modPow(long long int x, long long n) {
    if(n == 0) return 1;
    long long ret = modPow(x, n / 2);
    ret *= ret;
    ret %= mod;
    if(n & 1) ret *= x, ret %= mod;
    return ret;
}

long long fact[maxn], inv[maxn];
void pre() {
    fact[0] = 1;
    for(int i = 1; i < maxn; i++) fact[i] = (fact[i - 1] * i) % mod;
    inv[maxn - 1] = modPow(fact[maxn - 1], mod - 2);
    for(int i = maxn - 2; i > 0; i--) inv[i] = (inv[i + 1] * (i + 1)) % mod;
    inv[0] = 1;
}

long long ncr(int n, int r) {
    if(r < 0 || r > n) return 0;
    long long ret = (fact[n] * inv[r]) % mod;
    ret *= inv[n - r];
    ret %= mod;
    return ret;
}

long long query(node *x, node *y, int tp, int tl, int tr, int k) {
    if(tl == tr) {
        return ncr(y->cnt - x->cnt, k);
    }
    int tm = (tl + tr) / 2;
    if(y->l->cnt - x->l->cnt >= k)
        return query(x->l, y->l, 2*tp, tl, tm, k);
    return query(x->r, y->r, 2*tp + 1, tm + 1, tr, k - (y->l->cnt - x->l->cnt));
}

int main() {
    int n, q;
    cin >> n >> q;
    int a[maxn];
    set <int> s;
    map <int, int> mp;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s.insert(a[i]);
    }
    int p = 1;
    for(int x : s) {
        mp[x] = p++;
    }
    node *root[maxn];
    root[0] = build(1, 0, n);
    for(int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 1, 0, n, mp[a[i]]);
    }
    pre(); // compute factorials and inverse
    while(q--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%lld\n", query(root[l - 1], root[r], 1, 0, n, k));
    }
    return 0;
}



