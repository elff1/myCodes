int a[4];
int sum(void) {
	int a[5];
	a[3] = 33;
	return a[3];
}
void main(void) {
	a[3] = 3;
	output(a[3]);
	output(sum());
}
