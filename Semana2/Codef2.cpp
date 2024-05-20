#include <iostream>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        int a[100];
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        int maxElement = a[0];
        int minElement = a[0];
        for (int i = 1; i < n; ++i) {
            if (a[i] > maxElement) {
                maxElement = a[i];
            }
            if (a[i] < minElement) {
                minElement = a[i];
            }
        }
        std::cout << maxElement - minElement << std::endl;
    }
    return 0;
}