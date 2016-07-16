//输入字符串"abc def gh"，输出字符串"gh def abc"

#include<string>
#include<iostream>

using namespace std;

int main() {
	string s = "i am here";
	string res;
	//char *head, *end;
	//head = end = &s[s.length() - 1];
	//
	//while(*head)
	//while (*head != ' ') head--;

	int head, end, temp;
	head = end = s.length() - 1;

	while (head >= 0) {
		while (head != 0 && s[head - 1] != ' ') head--;		//此处交换前后两个逻辑表达式顺序居然修复了个bug，我一定要记录下
		temp = head;
		while (temp <= end) {
			res += s[temp];
			temp++;
		}
		
		if (head != 0) {
			res += ' ';
			head -= 2;
			end = head;
		}
		else break;
	}

	cout << res;
	return 0;
}
