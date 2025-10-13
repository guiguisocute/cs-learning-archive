//老师我高中时期正好写过一模一样的小程序，现在还躺在文件夹里，稍微改改直接CV过来了
#include<iostream>

using namespace std;
int main()
{
	int n;
	cin >> n;
    if ((n % 4 == 0 && n % 100 != 0) || n % 400 == 0) 
  {

		cout << "1";

	}
	else
	{
		cout << "0";
	}
	
	system("pause");
	return 0;

}