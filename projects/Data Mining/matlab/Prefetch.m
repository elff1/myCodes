load('DM2011_V4');
fprintf('开始计算原始矩阵列的相似度...\n')
Similarity=squareform(1-pdist(Matrix','jaccard'));
fprintf('原始矩阵列相似度计算完毕...\n')