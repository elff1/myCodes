#include <stdio.h>

int Reverse(char ch) {
	int ans = 0;
	int i;
	int c = 128;

	for(i = 0; i < 8; i++) {
		if(ch % 2)
			ans += c;
		c >>= 1;
		ch >>= 1;
	}
	return ans;
}

int main(void) {
	char ch;
	int rev0, rev1;

	rev0 = 0;
	while((ch = getchar()) != '\n') {
		rev1 = Reverse(ch);
		//printf("%d\t", rev1);
		printf("%d\n", (256 + rev0 - rev1) % 256);
		rev0 = rev1;
	}

	return 0;
}
