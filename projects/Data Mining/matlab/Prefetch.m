load('DM2011_V4');
fprintf('��ʼ����ԭʼ�����е����ƶ�...\n')
Similarity=squareform(1-pdist(Matrix','jaccard'));
fprintf('ԭʼ���������ƶȼ������...\n')