#include <stdio.h> 
 
/* 人数 */ 
int T; 
/* 每个人的课程数 */ 
int n; 
/* 课程的学分, 成绩和绩点 */ 
float C, S, G; 
/* 存储总学分绩点和总学分 */ 
float sN, sD; 
/* 存储 GPA */ 
float GPA; 
/* 循环变量 */ 
int t, i, j; 
 
int main() { 
    /* 读入人数 */ 
    scanf("%d", &T); 
    for (t = 0; t < T; t++) { 
        /* 读入课程数 */ 
		scanf("%d",&n);
        /* 初始化分子和分母 */ 
        sN = 0; 
        sD = 0; 
        for (i = 0; i < n; i++) { 
            /* 读入课程的学分和成绩 */ 
			scanf("%f%f",&C,&S);
            /* 将成绩转化为绩点 */ 
            if (S >= 85) { 
                G = 4; 
            } else if (S < 60) { 
                G = 0; 
            } else { 
                G = (S - 60) / 10 + 1.5; 
            } 
            /* 累计分子和分母 */ 
            sN += C * G; 
            sD += C; 
        } 
        GPA = sN / sD; 
        /* 输出答案 */ 
		printf("%.2f\n",GPA);
    } 
    return 0; 
}