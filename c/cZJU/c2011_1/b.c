#include <stdio.h>
/*#include <math.h>*/

int ceil(double x) {
	int ans;

	ans = (int)x;
	if(ans < x || ans > x)
		return ans + 1;
	return ans;
}

int main(void) {
	int i, m, n, k, t;

	scanf("%d", &t);

	for(i = 0; i < t; i++) {
		scanf("%d%d%d", &n, &m, &k);
		printf("%d\n", ceil(1.0*n/k) * ceil(1.0*m/k));
	}
	return 0;
}
