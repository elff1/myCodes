#include <stdio.h>
#include <string.h>

int main(void) {
	int t, k, i, j, n;
	int ss;
	char str[1010], word[2010];

	scanf("%d", &t);
	gets(str);
	for(k = 0; k < t; k++) {
		gets(str);
		n = 0;
		i = -1;
		do {
			/*ss = sscanf(str, "%s", word);
			puts(word);
			printf("%d ", ss);*/
			if(i >= 0)
				putchar(' ');
			i++;
			j = 0;
			while(str[i] && str[i] != ' ') {
				word[j] = str[i];
				i++;
				j++;
			}
			word[j] = 0;
			n++;
			for(j = 0; j < n; j++)
				printf("%s", word);
			/*(putchar('\n');*/
		} while(str[i]);
		/*puts(str);*/
		putchar('\n');
	}
	return 0;
}
