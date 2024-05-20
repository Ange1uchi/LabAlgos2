#include <bits/stdc++.h>
using namespace std;

bool ok(vector<int>& v, int x, int c)
{
    int n = v.size();
    int count = 1;
    int d = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] - d >= x) {
            d = v[i];
            count++;
        }
        if (count == c) {
            return true;
        }
    }
    return false;
}

int agresivacas(vector<int>& v, int n, int k)
{
    sort(v.begin(), v.end());
    int low = 0, high = v[n-1] - v[0];
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        if (ok(v, mid, k)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

int main()
{
    int t;
    cin >> t;
    while(t--) {
        int N, K;
        cin >> N >> K;
        vector<int> arr(N);
        for(int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        int ans = agresivacas(arr, N, K);
        cout << ans << endl;
    }
    return 0;
}