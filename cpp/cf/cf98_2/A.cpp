#include <stdio.h>
#include <cstring>

int main(void) {
	char pre, now;
	int count, ans;

	pre = 0;
	count = 0;
	ans = 0;
	while(1) {
		now = getchar();
		if(pre == 0) {
			pre = now;
			count++;
		}
		else if(pre == now) {
			count++;
		}
		else {
			ans += (count - 1) / 5 + 1;
			if(now == '\n')
				break;
			pre = now;
			count = 1;
		}
	}

	printf("%d\n", ans);
	return 0;
}
