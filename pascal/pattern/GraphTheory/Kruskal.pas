{最小生成树的Kruskal算法。Kruskal算法基本思想：
每次选不属于同一连通分量(保证不生成圈)且边权值最小的顶点，将边加入MST，
并将所在的2个连通分量合并，直到只剩一个连通分量
排序使用Quicksort(O(eloge))
检查是否在同一连通分量用Union-Find，每次Find和union运算近似常数
Union-Find使用rank启发式合并和路径压缩
总复杂度O(eloge)=O(elogv) (因为e<n(n-1)/2)}
const
  maxn=100;
  maxe=maxn*maxn;
type
  edge=record
         a,b    :integer;      //边的2个顶点
         len    :integer;      //边的长度
       end;
var
  edges :array[0..maxe]of edge;    //保存所有边的信息
  p,r   :array[0..maxn]of integer;   //p[i]保存i的父亲节点，r用来实现Union-Find的rank启发式
  n,e   :integer;     //n为顶点数，e为边数
procedure swap(a,b:integer);    //交换
begin
  edges[0]:=edges[a];
  edges[a]:=edges[b];
  edges[b]:=edges[0];
end;

procedure quicksort(l,r:integer);   //快速排序
var
  x,i,j :integer;
begin
  x:=edges[random(r-l+1)+l].len;
  i:=l;j:=r;

  repeat
    while edges[i].len<x do inc(i);
    while edges[j].len>x do dec(j);
    if i<=j then
      begin
        swap(i,j);
        inc(i);dec(j);
      end
  until i>j;

  if l<j then quicksort(l,j);
  if i<r then quicksort(i,r);
end;

procedure init;
var
  i     :integer;
begin
  assign(input,'g.in');reset(input);
  readln(n,e);
  for i:=1 to e do readln(edges[i].a,edges[i].b,edges[i].len);  //从文件读入图的信息
  for i:=1 to n do p[i]:=i;   //初始化并查集
  randomize;
  quicksort(1,e);      //使用快速排序将边按权值从小到大排列
end;

function find(x:integer):integer;     //并查集的Find，用来判断2个顶点是否属于一个连通分量
begin
  if x<>p[x] then p[x]:=find(p[x]);
  find:=p[x]
end;

procedure union(a,b:integer);     //如果不属于且权值最小则将2个顶点合并到一个连通分量
var
  t     :integer;
begin
  a:=find(a);b:=find(b);
  if r[a]>r[b] then begin t:=a;a:=b;b:=t end;
  if r[a]=r[b] then inc(r[b]);
  p[a]:=b;
end;

procedure kruskal;      //主过程
var
  en    :integer;   //en为当前边的编号
  count :integer;   //统计进行了几次合并。n-1次合并后就得到最小生成树
  tot   :integer;   //统计最小生成树的边权总和
begin
  count:=0;en:=0; tot:=0;
  while count<n-1 do
    begin
      inc(en);
      with edges[en] do
        begin
          if find(a)<>find(b) then
            begin
              union(a,b);
              writeln(a,'--',b,':',len);
              inc(tot,len);
              inc(count);
            end;
        end;
    end;
  writeln('Total Length=',tot)
end;

{===========main==========}
begin
  init;
  kruskal;
end.