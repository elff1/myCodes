#include <stdio.h>

int a, b, c, d;

int Check(int y, int r) {
	int s;
	int i;
	int yy = y, rr = r;

	s = y % 10;
	if(!(s == a || s == b || s == c || s == d))
		return 0;
	s = y / 10;
	if(s)
		if(!(s == a || s == b || s == c || s == d))
			return 0;

	s = r % 10;
	if(!(s == a || s == b || s == c || s == d))
		return 0;
	s = r / 10;
	if(s)
		if(!(s == a || s == b || s == c || s == d))
			return 0;

	return 1;
}

int main(void) {
	int T, n, m, i, j;
	int ans;

	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		ans = 0;
		for(i = 1; i <= 12; i++) {
			if(i==1 || i==3 || i==5 || i==7 || i==8 || i==10 || i==12)
					for(j = 1; j <= 31; j++)
						ans += Check(i, j);
			else if(i==4 || i==6 || i==9 || i==11)
					for(j = 1; j <= 30; j++)
						ans += Check(i, j);
			else if(i==2)
					for(j = 1; j <= 28; j++)
						ans += Check(i, j);
		}
		printf("%d\n", ans);
	}

	return 0;
}
