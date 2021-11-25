#include<vector>


namespace hh509 {
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        cached.resize(n + 1, 0);
        return helper(n);
    }
private:
    int helper(int i) {
        if (i <= 1) return i;
        if (cached[i]) return cached[i];
        return cached[i] = helper(i - 1) + helper(i - 2);
    }
private:
    std::vector<int> cached;
}

class Solution2 {
public:
    int fib(int n) {
        if (n < 2) return n;
        int f = 0;
        int g = 1;
        for (int i = 2; i <= n; ++i) {
            g = f + g;
            f = g - f;
        }
        return g;
    }
}
}

namespace hh1137 {
class Solution {
public:
    int tribonacci(int n) {
        if (n <= 1) return n;
        if (n == 2) return 1;
        int f = 0, g = 1, h = 1;
        for (int i = 3; i <= n; ++i) {
            h = f + g + h;
            g = h - f - g;
            f = h - f - g;
        }
        return h;
    }
}
}

