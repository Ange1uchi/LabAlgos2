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
        else {
            continue;
        }
    }
    if (count >= c) {
        return true;
    }
    return false;
}

int agresivacas(vector<int>& v, int n, int k)
{
    long long ans = -1;
    int maxi = 0;
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, v[i]);
    }

    for (long long i = 1; i <= maxi; i++) {
        if (ok(v, i, k)) {
            ans = i;
        }
        else {
            break;
        }
    }
 
    return ans;
}

int main()
{
    int K = 3;
    vector<int> arr = { 1, 2, 4, 8, 9 };
    int N = arr.size();
 
    int ans = agresivacas(arr, N, K);
    cout << ans << endl;
 
    return 0;
}
