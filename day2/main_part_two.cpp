#include <bits/stdc++.h>
using namespace std;
using u128 = unsigned __int128;

u128 parse_u128(const string &s) {
    u128 x = 0;
    for (char c : s) if (c >= '0' && c <= '9') x = x * 10 + (c - '0');
    return x;
}

string to_string_u128(u128 v) {
    if (v == (u128)0) return "0";
    string out;
    while (v > 0) {
        unsigned d = (unsigned)(v % 10);
        out.push_back(char('0' + d));
        v /= 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

u128 ceil_div(u128 a, u128 b) {
    return a / b + (a % b != 0);
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input.txt\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) { cerr << "Cannot open input file.\n"; return 1; }
    string all, line;
    while (getline(in, line)) all += line;
    in.close();
    string s;
    for (char c : all) if (!isspace((unsigned char)c)) s.push_back(c);
    if (s.empty()) { cout << "0\n"; return 0; }

    const int MAXP = 80;
    vector<u128> pow10(MAXP+1);
    pow10[0] = 1;
    for (int i = 1; i <= MAXP; ++i) pow10[i] = pow10[i-1] * (u128)10;

    const int MAXD = 40;
    vector<int> mu(MAXD+1, 1), primes;
    vector<int> mind(MAXD+1, 0);
    for (int i = 2; i <= MAXD; ++i) {
        if (!mind[i]) { mind[i] = i; primes.push_back(i); mu[i] = -1; }
        for (int p : primes) {
            long long v = 1LL * p * i;
            if (v > MAXD) break;
            mind[v] = p;
            if (i % p == 0) { mu[v] = 0; break; }
            else mu[v] = -mu[i];
        }
    }
    vector<vector<int>> divisors(MAXD+1);
    for (int d = 1; d <= MAXD; ++d)
        for (int t = 1; t * t <= d; ++t)
            if (d % t == 0) {
                divisors[d].push_back(t);
                if (t * t != d) divisors[d].push_back(d / t);
            }

    u128 total = 0;

    size_t pos = 0;
    while (pos < s.size()) {
        size_t comma = s.find(',', pos);
        string token = (comma == string::npos) ? s.substr(pos) : s.substr(pos, comma - pos);
        pos = (comma == string::npos) ? s.size() : comma + 1;
        if (token.empty()) continue;
        size_t dash = token.find('-');
        if (dash == string::npos) continue;
        u128 L = parse_u128(token.substr(0, dash));
        u128 R = parse_u128(token.substr(dash + 1));
        if (L > R) swap(L, R);

        int digitsR = 1;
        for (u128 t = R; t >= 10; t /= 10) ++digitsR;

        int max_d = min(MAXD, digitsR); 
        for (int d = 1; d <= max_d; ++d) {
            int max_r = digitsR / d;
            for (int r = 2; r <= max_r; ++r) {
                int total_len = d * r;
                if (d*r > MAXP) continue; 
                u128 ten_dr = pow10[total_len];
                u128 ten_d = pow10[d];
                
                u128 M_full = (ten_dr - (u128)1) / (ten_d - (u128)1);

                u128 smin = pow10[d-1];
                u128 smax = pow10[d] - (u128)1;

                u128 sL = ceil_div(L, M_full);
                u128 sR = R / M_full;
                if (sL < smin) sL = smin;
                if (sR > smax) sR = smax;
                if (sL > sR) continue;

                u128 Gsum = 0;

                for (int t : divisors[d]) {
                    u128 ten_t = pow10[t];
                    u128 Ms_s = (pow10[d] - (u128)1) / (ten_t - (u128)1);
                    u128 umin = ceil_div(sL, Ms_s);
                    u128 umax = sR / Ms_s;
                    u128 umin_digit = pow10[t-1];
                    u128 umax_digit = pow10[t] - (u128)1;
                    if (umin < umin_digit) umin = umin_digit;
                    if (umax > umax_digit) umax = umax_digit;
                    if (umin > umax) continue;
                    u128 cnt = umax - umin + (u128)1;
                    u128 a = umin + umax;
                    u128 b = cnt;
                    if (a % 2 == 0) a /= 2;
                    else b /= 2;
                    u128 sum_u = a * b;
                    u128 Fsum = Ms_s * sum_u;

                    int mucoef = mu[d / t];
                    if (mucoef == 1) Gsum += Fsum;
                    else if (mucoef == -1) Gsum -= Fsum;
                }

                total += Gsum * M_full;
            }
        }
    }

    cout << to_string_u128(total) << "\n";
    return 0;
}
