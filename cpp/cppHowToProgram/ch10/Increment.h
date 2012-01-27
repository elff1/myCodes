#ifndef INCREMENT_H
#define INCREMENR_H

class Increment {
	public:
		Increment(int c = 0, int i = 1);

		void addIncrement() {
			count += increment;
		}

		void print() const;
	private:
		int count;
		const int increment;
};

#endif
