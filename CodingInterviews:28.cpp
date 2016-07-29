//剑指Offer：面试题28
//字符串全排列一直不会，所以照着写一遍试试

#include<stdio.h>

void Permutation(char* pStr);
void Permutation(char* pStr, char* pBegin);

int main() {
	char s[] = "abc";
	Permutation(s);

	return 0;
}

void Permutation(char* pStr) {
	if (pStr == NULL)
		return;

	Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin) {
	if (*pBegin == '\0')
		printf("%s\n", pStr);
	else {
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh) {
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);
			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}
