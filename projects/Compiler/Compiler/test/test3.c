int fact(int n) {
	if (n == 1)
		return n;
	else
		return (n*fact(n-1));
}

int main(void) {
	int m;
	int result;
	m = input();
	if (m > 1)
		result = fact(m);
	else
		result = 1;
	output(result);
	return 0;
}

