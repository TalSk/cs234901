#include <iostream>

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int m, n, c, r;
        std::cin >> m;
        std::cin >> n;
        std::cin >> c;
        std::cin >> r;

        int a1 = c;
        int a2 = m - c - 1;
        int a3 = r;
        int a4 = n - r - 1;

        int res = a1 ^ a2 ^ a3 ^ a4;
        if (res == 0) {
            std::cout << "Hansel" << std::endl;
        }
        else {
            std::cout << "Gretel" << std::endl;
        }
    }
    return 0;
}