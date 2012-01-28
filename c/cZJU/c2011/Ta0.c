#include <stdio.h>

int main(void) {
	int T, n, m, i, j, c;
	int ans;

	scanf("%d", &T);
	while(T--) {
		ans = 0;
		scanf("%d%d", &m, &n);
		for(i = 0; i < m; i++)
			for(j = 0; j < n; j++) {
				scanf("%d", &c);
				ans += c*c;
			}
		printf("%%%%%% F-Norm Squared = %d %%%%%%\n", ans);
	}

	return 0;
}
