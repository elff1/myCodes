load('DM2011_V4');
%��ʼ������
Matrix_Instance=Matrix;
Permutation_Instance=Permutation;
[Me_row_number,Me_column_number]=size(Matrix_Instance);
[Pe_row_number,Pe_column_number]=size(Permutation_Instance);
fprintf('��ʼminhashing...\n')
%Hashed_Matrix���ڴ洢�����ȡ�õ�hash����ֵ
Hashed_Matrix=[];
for i=1:Pe_row_number
    Permutation_Result=zeros(1,Me_column_number);
    %ÿ����hash��ʱ������ļ�¼����¼�˴�ѭ���е�һ�γ���1��λ��
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
    %��hash�����������Ӵ˴μ�¼
end
fprintf('minhashing ����...�������Hashed_Matrix������\n')