int a;
int b;

int sum(int a, int b) {
	return a+b;
}

int sub(int a, int b) {
	return a-b;
}

int mul(int a, int b) {
	return a*b;
}

int div(int a, int b) {
	return a/b;
}

int main(void) {
	a = 7;
	b = 3;
	output(sum(a, b));
	output(sub(a, b));
	output(mul(a, b));
	output(div(a, b));
	return 0;
}
