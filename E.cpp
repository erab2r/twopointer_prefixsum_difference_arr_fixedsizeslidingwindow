#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    if (!(cin >> tc)) 
    return 0;
    while (tc--) {
        int n;
        long long s;
        cin >> n >> s;
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) 
            cin >> arr[i];

        int ans = n + 1;
        int l = 0, r = 0;
        long long res = s;

        while (l < n) {
            if (res == 0) ans = min(ans, l + (n - r));
            if (res < 0 || r == n) {
                res += arr[l];
                l++;
            } else {
                res -= arr[r];
                r++;
            }
        }

        if (ans > n) 
            cout << -1 << '\n';
        else 
            cout << ans << '\n';
    }

    return 0;
}
