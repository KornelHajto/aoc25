#include <bits/stdc++.h>
using namespace std;

using u128 = unsigned __int128;

// parse decimal string → u128
u128 parse_u128(const string &s) {
    u128 x = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9')
            x = x * 10 + (c - '0');
    }
    return x;
}

// u128 → string
string to_string_u128(u128 v) {
    if (v == 0) return "0";
    string out;
    while (v > 0) {
        out.push_back('0' + (unsigned)(v % 10));
        v /= 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

u128 ceil_div(u128 a, u128 b) {
    return a / b + (a % b != 0);
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input.txt\n";
        return 1;
    }

    // read file
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Cannot open input file.\n";
        return 1;
    }

    string all, line;
    while (getline(in, line)) all += line;
    in.close();

    // strip whitespace
    string s;
    for (char c : all)
        if (!isspace((unsigned char)c))
            s.push_back(c);

    if (s.empty()) return 0;

    // precompute powers of 10
    vector<u128> pow10(41);
    pow10[0] = 1;
    for (int i = 1; i <= 40; ++i) pow10[i] = pow10[i - 1] * (u128)10;

    u128 total = 0;

    // process each range
    size_t pos = 0;
    while (pos < s.size()) {
        size_t comma = s.find(',', pos);
        string token = (comma == string::npos
                        ? s.substr(pos)
                        : s.substr(pos, comma - pos));
        pos = (comma == string::npos ? s.size() : comma + 1);
        if (token.empty()) continue;

        size_t dash = token.find('-');
        if (dash == string::npos) continue;

        u128 L = parse_u128(token.substr(0, dash));
        u128 R = parse_u128(token.substr(dash + 1));
        if (L > R) swap(L, R);

        // digit count of R
        int digitsR = 1;
        for (u128 t = R; t >= 10; t /= 10) digitsR++;
        int max_k = digitsR / 2;

        for (int k = 1; k <= max_k; ++k) {
            u128 tenk = pow10[k];
            u128 m = tenk + 1;

            u128 s_min = pow10[k - 1];
            u128 s_max = pow10[k] - 1;

            u128 sL = ceil_div(L, m);
            u128 sR = R / m;

            if (sL < s_min) sL = s_min;
            if (sR > s_max) sR = s_max;

            if (sL > sR) continue;

            u128 count = sR - sL + 1;
            u128 a = sL + sR;
            u128 b = count;

            // one must be even
            if (a % 2 == 0) a /= 2;
            else b /= 2;

            u128 sum_s = a * b;
            total += sum_s * m;
        }
    }

    cout << to_string_u128(total) << "\n";
    return 0;
}
