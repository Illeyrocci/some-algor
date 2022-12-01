long long gcdex(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcdex(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = gcdex(a, m, x, y);
    assert(g == 1);
    return (x % m + m) % m;
}
long long garner(vector<long long> A, vector<long long> P) {
    //long long a, b, n, m; cin >> a >> b >> n >> m;
    long long M = 1;
    for (long long p : P) {
        M *= p;
    }
    vector<long long> PP;
    for (long long p : P) {
        PP.push_back(M / p);
    }
    vector<long long> RPP;
    for (int i = 0; i < P.size(); i++) {
        RPP.push_back(modInverse(PP[i] % P[i], P[i]));
    }
    long long x = 0;
    for (int i = 0; i < P.size(); i++) {
        x += A[i] * PP[i] * RPP[i];
        x %= M;
    }
    return x;
}
