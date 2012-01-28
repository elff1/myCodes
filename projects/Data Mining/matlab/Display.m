%display.m
%用于显示r,b,t的关系并帮助初步判定最佳threshold
t=input('请输入threshold值：');
N=input('请输入permutation的行数N(N=r*b):');
r=1 - lambertw(0, -t*log(t)*(N - 1))/log(t);
fprintf('一个合理的建议是r=%d或者r=%d\n',ceil(r),floor(r));
x=0.00:0.001:1.0;
y=1 - lambertw(0, -x.*log(x).*(N - 1))./log(x);
plot(x,y);
title('最佳t-r关系图');
xlabel('判定相似的阈值threshold');
ylabel('每band所含最佳r值');