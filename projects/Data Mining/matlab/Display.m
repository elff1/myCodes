%display.m
%������ʾr,b,t�Ĺ�ϵ�����������ж����threshold
t=input('������thresholdֵ��');
N=input('������permutation������N(N=r*b):');
r=1 - lambertw(0, -t*log(t)*(N - 1))/log(t);
fprintf('һ������Ľ�����r=%d����r=%d\n',ceil(r),floor(r));
x=0.00:0.001:1.0;
y=1 - lambertw(0, -x.*log(x).*(N - 1))./log(x);
plot(x,y);
title('���t-r��ϵͼ');
xlabel('�ж����Ƶ���ֵthreshold');
ylabel('ÿband�������rֵ');