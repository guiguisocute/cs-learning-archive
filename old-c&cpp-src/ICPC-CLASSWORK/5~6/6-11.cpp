#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n - i; j++){
            printf("           ");
            for(int j = i; j >= 1; j--){
                printf("%3d*%3d=%3d",i,j,i * j);
            }
            cout << endl;
        }
    }
    return 0;
}