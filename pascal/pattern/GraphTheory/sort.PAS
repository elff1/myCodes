有向图的拓扑排序每次找入度为0的顶点入栈成功返回true,有环返回false总复杂度O(n+e)
const
  maxn=100;
type
  link=^node;
  node=record
         v,w    :integer;
         next   :link;
       end;
  arr=array[1..maxn]of 1..maxn;
var
  adj           :array[1..maxn]of link;     //邻接表
  tsort,indgr   :arr;         //拓扑序列;入度
  n,s,i         :integer;
procedure init;
var
  u,v,w :integer;
  p     :link;
begin
  assign(input,'g.in');reset(input);
  readln(n,s);
  while not eof do
    begin
      readln(u,v,w);
      new(p);
      p^.v:=v;p^.w:=w; p^.next:=adj[u];
      adj[u]:=p; inc(indgr[v])
    end;
end;

function toposort(indgr:arr):boolean;
var
  i,top   :integer;
  p             :link;
  stack         :array[1..maxn]of integer;
begin
  top:=0;
  for i:=1 to n do
    if indgr[i]=0 then
      begin inc(top); stack[top]:=i end;
  i:=0;
  while top>0 do
    begin
      inc(i); tsort[i]:=stack[top]; dec(top);
      p:=adj[tsort[i]];
      while p<>nil do
        begin
          dec(indgr[p^.v]);
          if indgr[p^.v]=0 then
            begin inc(top); stack[top]:=p^.v end;
          p:=p^.next;
        end;
    end;
  exit(i=n)
end;

{===========main===========}
begin
  init;
  if toposort(indgr) then
    for i:=1 to n do write(tsort[i],' ')
  else writeln('A circle found')
end.