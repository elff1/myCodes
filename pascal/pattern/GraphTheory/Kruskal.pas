{��С��������Kruskal�㷨��Kruskal�㷨����˼�룺
ÿ��ѡ������ͬһ��ͨ����(��֤������Ȧ)�ұ�Ȩֵ��С�Ķ��㣬���߼���MST��
�������ڵ�2����ͨ�����ϲ���ֱ��ֻʣһ����ͨ����
����ʹ��Quicksort(O(eloge))
����Ƿ���ͬһ��ͨ������Union-Find��ÿ��Find��union������Ƴ���
Union-Findʹ��rank����ʽ�ϲ���·��ѹ��
�ܸ��Ӷ�O(eloge)=O(elogv) (��Ϊe<n(n-1)/2)}
const
  maxn=100;
  maxe=maxn*maxn;
type
  edge=record
         a,b    :integer;      //�ߵ�2������
         len    :integer;      //�ߵĳ���
       end;
var
  edges :array[0..maxe]of edge;    //�������бߵ���Ϣ
  p,r   :array[0..maxn]of integer;   //p[i]����i�ĸ��׽ڵ㣬r����ʵ��Union-Find��rank����ʽ
  n,e   :integer;     //nΪ��������eΪ����
procedure swap(a,b:integer);    //����
begin
  edges[0]:=edges[a];
  edges[a]:=edges[b];
  edges[b]:=edges[0];
end;

procedure quicksort(l,r:integer);   //��������
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
  for i:=1 to e do readln(edges[i].a,edges[i].b,edges[i].len);  //���ļ�����ͼ����Ϣ
  for i:=1 to n do p[i]:=i;   //��ʼ�����鼯
  randomize;
  quicksort(1,e);      //ʹ�ÿ������򽫱߰�Ȩֵ��С��������
end;

function find(x:integer):integer;     //���鼯��Find�������ж�2�������Ƿ�����һ����ͨ����
begin
  if x<>p[x] then p[x]:=find(p[x]);
  find:=p[x]
end;

procedure union(a,b:integer);     //�����������Ȩֵ��С��2������ϲ���һ����ͨ����
var
  t     :integer;
begin
  a:=find(a);b:=find(b);
  if r[a]>r[b] then begin t:=a;a:=b;b:=t end;
  if r[a]=r[b] then inc(r[b]);
  p[a]:=b;
end;

procedure kruskal;      //������
var
  en    :integer;   //enΪ��ǰ�ߵı��
  count :integer;   //ͳ�ƽ����˼��κϲ���n-1�κϲ���͵õ���С������
  tot   :integer;   //ͳ����С�������ı�Ȩ�ܺ�
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