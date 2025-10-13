//指针内容转换
#include <iostream>
#include <limits>
using namespace std;

// 函数声明
void swap(int*, int*);

int main() {
    int a = 3, b = 8;
    cout << "a = " << a << ", b = " << b << endl;

    swap(&a, &b); // 函数的调用

    cout << "after swapping... \n";
    cout << "a = " << a << ", b = " << b << endl;

    // 等待用户输入，以防止窗口立即关闭
    cout << "Press Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    return 0;
}

// 函数定义
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
