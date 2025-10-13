//常引用函数实例
#include <iostream>
#include <cmath> // 使用cmath代替math.h

using namespace std;

// 显示整数的不同进制表示，因为在此常引用了形参，所以实参调用时就能使用非变量表达式
void display(const int& rk) {
    cout << dec << rk << " :\n"
        << "dec : " << rk << endl
        << "oct : " << oct << rk << endl
        << "hex : " << hex << rk << endl;
}

int main() {
    int x;
    cout << "number : ";
    cin >> x;
    display(x);
    display(4589);  // 示例调用

    system("pause");
    return 0;
}