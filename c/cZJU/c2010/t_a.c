#include <stdio.h> 
 
/* ���� */ 
int T; 
/* ÿ���˵Ŀγ��� */ 
int n; 
/* �γ̵�ѧ��, �ɼ��ͼ��� */ 
float C, S, G; 
/* �洢��ѧ�ּ������ѧ�� */ 
float sN, sD; 
/* �洢 GPA */ 
float GPA; 
/* ѭ������ */ 
int t, i, j; 
 
int main() { 
    /* �������� */ 
    scanf("%d", &T); 
    for (t = 0; t < T; t++) { 
        /* ����γ��� */ 
		scanf("%d",&n);
        /* ��ʼ�����Ӻͷ�ĸ */ 
        sN = 0; 
        sD = 0; 
        for (i = 0; i < n; i++) { 
            /* ����γ̵�ѧ�ֺͳɼ� */ 
			scanf("%f%f",&C,&S);
            /* ���ɼ�ת��Ϊ���� */ 
            if (S >= 85) { 
                G = 4; 
            } else if (S < 60) { 
                G = 0; 
            } else { 
                G = (S - 60) / 10 + 1.5; 
            } 
            /* �ۼƷ��Ӻͷ�ĸ */ 
            sN += C * G; 
            sD += C; 
        } 
        GPA = sN / sD; 
        /* ����� */ 
		printf("%.2f\n",GPA);
    } 
    return 0; 
}