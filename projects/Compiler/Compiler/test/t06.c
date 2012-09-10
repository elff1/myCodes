int main(void) {
	int a;  int b;
	a = 10;  b = 10;
	{
		int b;
		b = 1;
		{
			int a;
			a = 2;
			output(a); output(b);
		}
		{
			int b;
			b = 3;
			output(a); output(b);
		}
		output(a); output(b);
	}
	output(a); output(b);
	return 0;
}

