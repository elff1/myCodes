#include <stdio.h>

#define MaxN 2000
#define MaxIDNum 1000000
#define MaxIDLen 6

int average(int *a, int num);
void qsort(int a[][5], int col, int p, int q);
void swap(int a[][5], int p, int q);

int main(void) {
	int n, m;
	int i, j;
	int sid;
	char symbol[4] = {'A', 'C', 'M', 'E'};
	/** score[]: 0 for A, 1 for C, 2 for M, 3 for E, 4 for array id*/
	int score[MaxN][5];
	/** rank[]: 0 for A, 1 for C, 2 for M, 3 for E*/
	int rank[MaxN][4];
	/** bestRank[]: 0 for the best rank, 1 for the best course*/
	int bestRank[MaxN][2];
	/** the array id of a student ID */
	int id[MaxIDNum];

	int currentScore, currentRank;
	int currentBestRank, currentBestCourse;

	/** initialization*/
	for(i = 0; i < MaxIDNum; i++)
		id[i] = -1;

	/** input score*/
	scanf("%d%d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &sid);
		id[sid] = i;
		score[i][4] = i;
		for(j = 1; j < 4; j++)
			scanf("%d", &score[i][j]);
		score[i][0] = average(&(score[i][1]), 3);
	}

	/** compute the score rank*/
	for(i = 0; i < 4; i++) {
		qsort(score, i, 0, n - 1);
		currentScore = score[0][i];
		currentRank = 0;
		for(j = 0; j < n; j++) {
			if(currentScore != score[j][i]) {
				currentScore = score[j][i];
				currentRank = j;
			}
			rank[score[j][4]][i] = currentRank + 1;
		}
	}

	/** compute the best rank*/
	for(i = 0; i < n; i++) {
		currentBestRank = rank[i][0];
		currentBestCourse = 0;
		for(j = 1; j < 4; j++) {
			if(rank[i][j] < currentBestRank) {
				currentBestRank = rank[i][j];
				currentBestCourse = j;
			}
		}
		bestRank[i][0] = currentBestRank;
		bestRank[i][1] = currentBestCourse;
	}

	/** handle m queries*/
	for(i = 0; i < m; i++) {
		scanf("%d", &sid);
		if(id[sid] < 0)
			printf("N/A\n");
		else
			printf("%d %c\n",
					bestRank[id[sid]][0],
					symbol[bestRank[id[sid]][1]]
					);
	}

	return 0;
}

int average(int *a, int num) {
	int i;
	long s;

	s = 0;
	for(i = 0; i < num; i++)
		s += a[i];

	return s / num;
}

void qsort(int a[][5], int col, int p, int q) {
	int i, j, m;

	i = p;
	j = q;
	m = a[(p + q) / 2][col];
	do {
		while(a[i][col] > m)
			i++;
		while(a[j][col] < m)
			j--;
		if(i <= j) {
			swap(a, i, j);
			i++;
			j--;
		}
	} while(i <= j);
	if(i < q)
		qsort(a, col, i, q);
	if(j > p)
		qsort(a, col, p, j);
}

void swap(int a[][5], int p, int q) {
	int tmp, i;

	for(i = 0; i < 5; i++) {
		tmp = a[p][i];
		a[p][i] = a[q][i];
		a[q][i] = tmp;
	}
}
