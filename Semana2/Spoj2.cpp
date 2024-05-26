#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Data {
    int num;
    int count;
    int appear;
};

bool operator<(const Data& a, const Data& b) {
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.appear < b.appear;
}
//toma una secuencia de números, cuenta cuántas veces aparece cada número 
//y luego imprime los números ordenados por frecuencia (mayor frecuencia primero),
//en caso de empate, por orden de aparición. 
int main() {
    int n;
    long c;
    std::cin >> n >> c;
    std::vector<int> nums(n);
    std::map<int, Data> data;
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
        if (data.count(nums[i]) == 0) {
            data[nums[i]] = {nums[i], 0, i};
        }
        data[nums[i]].count++;
    }
    std::multiset<Data> sortedData;
    for (const auto& pair : data) {
        sortedData.insert(pair.second);
    }
    for (const auto& d : sortedData) {
        for (int i = 0; i < d.count; ++i) {
            std::cout << d.num << ' ';
        }
    }
    return 0;
}
