//老师我高中时期正好写过一模一样的小程序，现在还躺在文件夹里，稍微改改直接CV过来了
#include<iostream>
#include<limits> 

using namespace std;
int main()
{
	int year;
	cout << "please enter the year:" << '\t'; 
	cin >> year;
	if(cin.fail()){
		cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
		cout << "Invalid input, Please enter a vaild year." << endl;
	} else {
	if (year%4==0&&year%100!=0)
	{
		cout << "1";

	}
	else
	{
		cout << "0";
	}
	}
	system("pause");

	return 0;

}
