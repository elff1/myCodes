load('DM2011_V4');
%初始化参数
Matrix_Instance=Matrix;
Permutation_Instance=Permutation;
[Me_row_number,Me_column_number]=size(Matrix_Instance);
[Pe_row_number,Pe_column_number]=size(Permutation_Instance);
FP=zeros(1,Pe_row_number);
FN=zeros(1,Pe_row_number);
TP=zeros(1,Pe_row_number);
TN=zeros(1,Pe_row_number);
t=input('请输入相似度threshold:');

for r=1:Pe_row_number
fprintf('%d\n',r)
for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Similarity(i,j)>=t
            Similarity(i,j)=1;
        else 
            Similarity(i,j)=0;
        end
    end
end







last_row=Pe_row_number-mod(Pe_row_number,r);
b=last_row/r;

bucket_size=bitshift(2,30)-1;
Hashed_Similarity=zeros(b,Me_column_number);
for i=1:r:last_row
    for j=1:Me_column_number
        hash_value=0;
        for k=i:i+r-1
            hash_value=hash_value+mod(Hashed_Matrix(k,j)*r^(r-k+i-1),bucket_size);
        end
        Hashed_Similarity((i-1)/r+1,j)=hash_value;
    end
end
Hashed_Similarity=squareform(1-pdist(Hashed_Similarity','jaccard'));
for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Hashed_Similarity(   i,j)>0
            Hashed_Similarity(i,j)=1;
        end
    end
end

fp=0;
tp=0;
fn=0;
tn=0;

for i=1:Me_column_number
    for j=i+1:Me_column_number
        if Hashed_Similarity(i,j)==1 && Similarity(i,j)==0
            fp=fp+1;
        else if Hashed_Similarity(i,j)==0 && Similarity(i,j)==1
            fn=fn+1;
            else if Hashed_Similarity(i,j)==1 && Similarity(i,j)==1
                tp=tp+1;
                else if Hashed_Similarity(i,j)==0 && Similarity(i,j)==0
                        tn=tn+1;
                    end
                end
            end
        end
    end
end
FP(1,r)=fp;
FN(1,r)=fn;
TP(1,r)=tp;
TN(1,r)=tn;
end
plot(1:Pe_row_number,FP/1000,'*',1:Pe_row_number,FN/1000,'.');