#include<bits/stdc++.h>
using i64 = long long;
#define int long long
void solve() {
    int n, m, L, V;
    std::cin >> n >> m >> L >> V;
    std::vector<std::array<int, 3>> car(n);
    std::vector<int> p(m);
    for (int i = 0; i < n; i++) std::cin >> car[i][0] >> car[i][1] >> car[i][2];
    for (int i = 0; i < m; i++) std::cin >> p[i];
    std::vector<std::array<int, 2>> range;
    for (auto [d, v, a] : car) {
        if (a == 0) {
            auto it = lower_bound(p.begin(), p.end(), d) - p.begin();
            if (v <= V || it > m - 1) continue;
            else range.push_back({it, m - 1});
        } else if (a < 0) {
            auto check = [&](int i) {
                return 2 * (p[i] - d) * a < (V + v) * (V - v);
            };
            auto it = lower_bound(p.begin(), p.end(), d) - p.begin();
            if (it == m) continue;
            if (v <= V || check(it)) continue;
            int l = it, r = m - 1;
            while (l < r) {
                int mid = l + r >> 1;
                if (check(mid)) r = mid;
                else l = mid + 1;
            }            
            while (l < m && !check(l)) l++;
            while (l - 1 >= it && check(l - 1)) l--;
            if (it <= l - 1) {
                range.push_back({it, l - 1});
            }
        } else {
            auto check = [&](int i) {
                return 2 * (p[i] - d) * a > (V + v) * (V - v);
            };
            auto it = lower_bound(p.begin(), p.end(), d) - p.begin();
            if (it == m || !check(m - 1)) continue;
            if (v > V && it <= m - 1) {
                range.push_back({it, m - 1});
                continue;
            }
            int l = it, r = m - 1;
            while (l < r) {
                int mid = l + r >> 1;
                if (check(mid)) r = mid;
                else l = mid + 1;
            }
            while (l - 1 >= it && check(l - 1)) l--;
            while (l < m && !check(l)) l++;
            if (l <= m - 1 && check(l)) {
                range.push_back({l, m - 1});
            }
        }
    }

    std::vector<std::vector<int>> g(m); 
    for (auto [l, r] : range) {
        g[r].push_back(l);
    }
    int last = -1, ans = 0;
    for (int i = 0; i < m; i++) {
        sort(g[i].begin(), g[i].end());
        for (auto j : g[i]) {
            if (last >= j) continue;
            ans++;
            last = i;
        }
    }

    std::cout << (int)range.size() << " ";
    if(range.size() == 0) ans = 0;
    std::cout << m - ans << "\n";
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    
    // freopen("detect4.in", "r", stdin);
    int t; std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
