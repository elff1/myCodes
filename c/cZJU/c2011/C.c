#include <stdio.h>
#include <string.h>

int main(void) {
	int T, i, j;
	int c, h, n, o, p;
	int e, num;
	int f;
	char ch, pre;

	scanf("%d", &T);
	getchar();
	while(T--) {
		c = h = n = o = p = 0;
		num = 0;
		f = 0;
		e = 1;
		pre = 0;
		while(1){
			ch = getchar();
			if(ch == 'C' || ch == 'H' || ch == 'O' 
					|| ch == 'N' || ch == 'P' || ch == '\n') {
				if(num == 0)
					num = 1;
				switch(pre) {
					case 'C':
						c += num;
						break;
					case 'H':
						h += num;
						break;
					case 'N':
						n += num;
						break;
					case 'O':
						o += num;
						break;
					case 'P':
						p += num;
						break;
					default:
						break;
				}
				if(ch == '\n')
					break;
				num = 0;
				pre = ch;
				f = 0;
			}
			else {
				if(f == 0)
					num = ch - '0';
				else {
					num = num * 10 + ch - '0';
				}
				f = 1;
			}
		}
		if(c > 0) {
			printf("C");
			if(c > 1)
				printf("%d", c);
		}
		if(h > 0) {
			printf("H");
			if(h > 1)
				printf("%d", h);
		}
		if(n > 0) {
			printf("N");
			if(n > 1)
				printf("%d", n);
		}
		if(o > 0) {
			printf("O");
			if(o > 1)
				printf("%d", o);
		}
		if(p > 0) {
			printf("P");
			if(p > 1)
				printf("%d", p);
		}
		printf("\n");
	}

	return 0;
}
