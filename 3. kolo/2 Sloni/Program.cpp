#include <bits/stdc++.h>

using namespace std;

long long solve1(long long w, long long h, long long x, long long y, long long t) {
    long long res=0;
    for (int i=0; i<w; i++) {
        long long rel_time = t - abs(i-x);
        res += max(min(y, rel_time) + min(h-y, rel_time) + (rel_time >= 0) + 1, (long long) 0) / 2;
        // cout << min(y, rel_time) + min(h-y, rel_time) + (rel_time >= 0) + 1 << endl;
    }
    return res;
}

long long b(long long x, long long s, long long e) {
    return max(s, min(x, e));
}

long long rect(long long a, long long b, bool flag) {
    if (a*b % 2 == 0)
        return a*b/2;
    else if (flag)
        return (a*b+1)/2;
    else
        return (a*b-1)/2;
}

long long sumhalf(long long s, long long d) {
    if (d == 0) {
        return 0;
    }
    if (d == 1) {
        return (s+1)/2;
    }
    long long res=0;
    if (s % 2 == 0) {
        res += s++/2; d--;
    }
    if (d % 2 == 1) {
        res += (s+d+1)/2; d--;
    }
    res += (2*d*(s+1) + d*(d-2))/4;

    return res;
}

long long solve2(long long w, long long h, long long x, long long y, long long t) {
    long long res=0;
    res += rect(min(t, x) + 1 + min(t, w-x-1), 1, min(x,t)%2==t%2);
    // cout << "b: " << res << endl;

    long long a0, a1, a2, a3, a0s, a3e;
    a0 = b(x-t+1, 0, w-1);
    a3 = b(x+t-1, 0, w-1);
    if (t > y) {
        a1 = b(y-t+x, 0, w-1);
        a2 = b(t-y+x, 0, w-1);
    } else {
        a1 = x; a2 = x;
    }
    res += rect(min(t, y), (a2-a1+1), (x-a1+min(t, y))%2==t%2);
    // cout << "r1: " << res << endl;
    // cout << min(t, y) << " " << (a2-a1+1) << endl;
    
    if (a0 < a1) {
        a0s = min(y, t - abs(a0-x));
        res += sumhalf(a0s, a1-a0);
    }
    // cout << "s1a: " << res << endl;
    if (a3 > a2) {
        a3e = min(y, t - abs(a3-x));
        res += sumhalf(a3e, a3-a2);
    }
    // cout << "s1b: " << res << endl;
    // cout << a3e << " " << a3-a2 << endl;


    y = h-y-1;    
    long long b0, b1, b2, b3, b0s, b3e;
    b0 = b(x-t+1, 0, w-1);
    b3 = b(x+t-1, 0, w-1);
    if (t > y) {
        b1 = b(y-t+x, 0, w-1);
        b2 = b(t-y+x, 0, w-1);
    } else {
        b1 = x; b2 = x;
    }
    res += rect(min(t, y), (b2-b1+1), (x-b1+min(t, y))%2==t%2);
    // cout << "r2: " << res << endl;
    // cout << min(t, y) << " " << (b2-b1+1) << endl;
    
    if (b0 < b1) {
        b0s = min(y, t - abs(b0-x));
        res += sumhalf(b0s, b1-b0);
    }
    // cout << "s2a: " << res << endl;
    // cout << b0s << " " << b1-b0 << endl;
    if (b3 > b2) {
        b3e = min(y, t - abs(b3-x));
        res += sumhalf(b3e, b3-b2);
    }
    // cout << "s2b: " << res << endl;
    // cout << b3e << " " << b3-b2 << endl;
    return res;
}

int main() {
    int n;
    cin >> n;
    for (int _=0; _<n; _++) {
        long long w, h, x, y, t;
        cin >> w >> h >> x >> y >> t;
        cout << solve2(w, h, x, y, t) << endl;
    }
}