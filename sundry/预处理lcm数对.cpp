void init(int n) { // 预处理lcm<=n的所有数队 n((logn)^2)

    for(ll gcd = 1; gcd <= n; gcd ++) {    
        for(int i = gcd; i <= n; i += gcd) {
            for(int j = gcd; j <= n && i/gcd*j <= n && j <= i; j += gcd) {
                if(__gcd(i, j) == gcd) {
                    ll lcm = i/gcd*j;
                    v[lcm].push_back({j, i}); // (j <= i)
                }
            }
        }
    }
}
