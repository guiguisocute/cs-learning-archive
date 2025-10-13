//十进制转换十以下进制float也行
#include<iostream>
using namespace std;
int main()
{
	int ji, item, k, c, d, i = 0, z = 0;	double temp, xiaoshu;
	int a[1000], b[1000];
	cout << "please enter the decimal number:(float is OK)" << endl;
	cin >> temp;
	cout << "please enter the cardinal you want to convert:" << endl;
	cin >> ji;
	xiaoshu = temp - int(temp);
	item = int(temp);

	while (item >= ji)	//整数部分的输出
	{
		k = item % ji;
		item /= ji;
		a[i] = k;
		i++;

	}
	a[i] = item;
	cout << "the result is:";
	for (int j = i; j >= 0; j--)

	{

		c = a[j];
		cout << c;

	}
	cout << ".";
	double dji = ji;
	while (xiaoshu - int(xiaoshu) != 0)	//小数部分逻辑。
	{
		k = int(xiaoshu * ji);
		xiaoshu *= dji;
		xiaoshu = xiaoshu - int(xiaoshu);
		b[z] = k;
		z++;
		if (z >= 10)
			break;
	}
	for (int m = 0; m != z; m++)
	{
		d = b[m];
		cout << d;

	}
	system("pause");
	return 0;
}
