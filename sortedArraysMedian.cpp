#include <bits/stdc++.h>
using namespace std;

const int inf = 1e6;

float _getMedian(vector <int> &a, vector <int> &b) {
    int sz1 = a.size(), sz2 = b.size(), lsz = (sz1 + sz2 + 1) / 2;
    int lo = 0, hi = sz1 - 1;
    while(lo < hi) {
        int mid = (lo + hi) / 2;
        int m = lsz - (mid + 1) - 1;
        int leftMax = max(a[mid], b[m]);
        int rightMin = 0;
        if(mid < sz1 - 1) // edge case
            rightMin = a[mid + 1];
        if(m < sz2 - 1) // edge case
            rightMin = min(rightMin, b[m + 1]);
        if(leftMax <= rightMin) {
            if((sz1 + sz2) % 2)
                return leftMax;
            return (leftMax + rightMin) / 2.0;
        }
        if(a[mid] > b[m])
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    return inf;
}

float getMedian(vector <int> &a, vector <int> &b) {
    if(a.size() == 1 && b.size() == 1) return 0.5 * (a[0] + b[0]);
    return min(_getMedian(a, b), _getMedian(b, a));
}

int main() {
    cout << " test case: " << '\n';
    int t;
    cin >> t;
    while(t--) {
        vector <int> a, b;
        cout << " no. of elements in arr1:\t";
        int n;
        cin >> n;
        cout << " enter elements:\n";
        for(int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            a.push_back(x);
        }
        cout << " no. of elements in second arr:\t";
        cin >> n;
        cout << " enter elements:\n";
        for(int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            b.push_back(x);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        cout << " median: " << getMedian(a, b) << '\n';
    }
    return 0;
}
