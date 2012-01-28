load('DM2011_V4');
M=Matrix;
[row,col]=size(M);
t=input('t=:');
S=zeros(col,col);
c=0;
for i=1:col
    for j=i+1:col
        a=0;b=0;
        for k=1:row
            if M(k,i)==0 ||M(k,j)
                b=b+1;
            end
            if M(k,i)&&M(k,j)
                a=a+1;
            end
        end
        S(i,j)=a/b;
        if S(i,j)>=t
            c=c+1;
            fprintf('i=%d,j=%d,c=%d\n',i,j,c);
        end
    end
end