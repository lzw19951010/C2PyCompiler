#include <iostream>
using namespace std;

int main()
{
	int ans = 1;
	int i = 0;
	int j = 0;
	int k = 0;
	char str[100];
	cin >> str;
    i = strlen(str);
	j = i+1;
        j = j/2;
	for(k = 0;k < j;k++)
	{
		if(str[k] != str[i-1-k])
		{
			ans = false;
			break;
		}
	}
	cout << ans;
	return 0;
}