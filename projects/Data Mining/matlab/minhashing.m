load('DM2011_V4');
%初始化参数
Matrix_Instance=Matrix;
Permutation_Instance=Permutation;
[Me_row_number,Me_column_number]=size(Matrix_Instance);
[Pe_row_number,Pe_column_number]=size(Permutation_Instance);
fprintf('开始minhashing...\n')
%Hashed_Matrix用于存储乱序后取得的hash函数值
Hashed_Matrix=[];
for i=1:Pe_row_number
    Permutation_Result=zeros(1,Me_column_number);
    %每次做hash的时候产生的记录，记录此次循环中第一次出现1的位置
    for j=1:Pe_column_number
        tmp=Permutation_Instance(i,j);
        for k=1:Me_column_number
            if Permutation_Result(k)==0 
                
                if Matrix_Instance(tmp,k)==1
                    Permutation_Result(k)=j;
                end
            %else
             %   if Matrix_Instance(tmp,k)==1%&&j<Permutation_Result(k)
              %      Permutation_Result(k)=j;
               % end
            end
        end
    end
    Hashed_Matrix=[Hashed_Matrix;Permutation_Result];
    %在hash结果矩阵中添加此次记录
end
fprintf('minhashing 结束...结果存于Hashed_Matrix矩阵中\n')