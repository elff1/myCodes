#include <stdio.h>

int Cost(int p, int h, int d) {
	int ans;

	ans = 0;
	if(h > 0) {
		if(h < 8) {
			if(h + d <= 8)
				return p * d * 26;
			else
				return p * (8 - h) * 26 + Cost(p, 8, d - (8 - h));
		}
		else if(h < 22) {
			if(h + d <= 22)
				return p * d * 56;
			else
				return p * (22 - h) * 56 + Cost(p, 22, d - (22 - h));
		}
		else {
			if(h + d <= 24)
				return p * d * 26;
			else
				return p * (24 - h) * 26 + Cost(p, 0, d - (24 - h));
		}
	}
	else {
		if(d <= 8)
			return p * d * 26;
		else if(d <= 22)
			return p * (d - 8) * 56 + Cost(p, 0, 8);
		else if(d <= 24)
			return p * (d - 22) * 26 + Cost(p, 0, 22);
		else
			return Cost(p, 0, 24) + Cost(p, 0, d - 24);
	}
}

int main(void) {
	int T, n, m, i, j, c;
	int ans, td;
	int p, h, d;

	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		ans = 0;
		td = 0;
		for(i = 0; i < n; i++) {
			scanf("%d%d%d", &p, &h, &d);
			ans += Cost(p, h, d);
			td += p * d;
		}
		if(td > 200)
			ans += (td - 200) * 10;
		printf("%d\n", (int)(ans));
	}

	return 0;
}
