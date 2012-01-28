load('DM2011_V4');
%初始化参数

Matrix_Instance=Matrix;
Permutation_Instance=Permutation;
[Me_row_number,Me_column_number]=size(Matrix_Instance);
[Pe_row_number,Pe_column_number]=size(Permutation_Instance);
t=input('请输入相似度threshold:');

fprintf('根据给定的threshold生成判定矩阵...\n')

SIM=0;
for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Similarity(i,j)>=t
            Similarity(i,j)=1;
            SIM=SIM+1;
        else 
            Similarity(i,j)=0;
        end
    end
end
fprintf('判定矩阵生成完毕,存放于Similarity...\n')

fprintf('开始对Hashed_Matrix使用LSH方法..\n')
r=input('请输入每一个band中的行数r:');
t=0:0.001:1;
last_row=Pe_row_number-mod(Pe_row_number,r);
b=last_row/r;
y=1-(1-t.^r).^b;
plot(t,y);
bucket_size=bitshift(2,30)-1;
Hashed_Similarity=zeros(b,Me_column_number);
for i=1:r:last_row
    for j=1:Me_column_number
        hash_value=0;
        for k=i:i+r-1
            tt=fastmod(r,r-k+i-1,bucket_size)*Hashed_Matrix(k,j);
            tt=mod(tt,bucket_size);
            hash_value=hash_value+tt;
        end
        Hashed_Similarity((i-1)/r+1,j)=hash_value;
    end
end
Hashed_Similarity=squareform(1-pdist(Hashed_Similarity','jaccard'));
for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Hashed_Similarity(i,j)>0
            Hashed_Similarity(i,j)=1;
        end
    end
end

fprintf('开始计算FP与FN..\n')

FP=0;
FN=0;
TP=0;
TN=0;
for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Hashed_Similarity(i,j)==1 && Similarity(i,j)==0
            FP=FP+1;
        else if Hashed_Similarity(i,j)==0 && Similarity(i,j)==1
            FN=FN+1;
            else if Hashed_Similarity(i,j)==1 && Similarity(i,j)==1
                TP=TP+1;
                else if Hashed_Similarity(i,j)==0 && Similarity(i,j)==0
                        TN=TN+1;
                    end
                end
            end
        end
    end
end
fprintf('SIM=%d\n',SIM);

fprintf('FP=%d\n',FP)

fprintf('FN=%d\n',FN)

fprintf('TP=%d\n',TP)

fprintf('TN=%d\n',TN)