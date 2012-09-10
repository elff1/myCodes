int add(int a) {
	return a + 1;
}

void main(void) {
	output(add(add(add(0))));
}
