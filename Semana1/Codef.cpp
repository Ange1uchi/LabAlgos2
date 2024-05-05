#include <iostream>
#include <vector>
using namespace std;

int main() {
    int count=0;
    int casos=0;
    int n=0;
    int k=0;
    bool rep=false;
    vector<int> cartas;
    cin >> casos;
    for (int i=0; i<casos; i++){
        cin >> n;
        cin >> k;
        cartas.resize(n);
        for(int i=0; i<n; i++){
            cin >> cartas[i];
        }
        for(int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if(cartas[i]==cartas[j]){
                    count++;
                }
            }
            if(count==k || count > k){
                cout << k-1 << endl;
                count=0;
                rep=true;
                break;          
            }
            count=0;
        }
        if(rep==false){
            cout << n << endl;
        }
        rep=false;
    }
    return 0;
}