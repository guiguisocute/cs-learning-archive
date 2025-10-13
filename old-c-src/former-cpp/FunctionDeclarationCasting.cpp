//函数声明的强制转换
#include<iostream>
using namespace std;
int main()
{
	float  add1(float, float);	 	 // 函数原型
	float  add2(int, int); 	  	 // 函数原型
	float  a, b, c;
	cin >> a >> b;
	c = add1(a, b);             cout << "c1=" << c << endl;
	c = add2(1 / a, 1 / b);        cout << "c2=" << c << endl;
}
float  add1(float  x, float  y)
{
	return (x + y);
}

float  add2(int  i, int  j)
{
	return (i + j);
}
