const maxn=1000;
var i,j,u,v,l,e,n,min:longint;
     g:array[1..maxn,1..maxn]of longint;
     b:array[1..maxn,1..maxn]of boolean;
     d:array[1..maxn]of longint;
     qb:array[1..maxn]of boolean;
begin
fillchar(b,sizeof(b),0);
readln(n,e);
for i:=1 to n do for j:=1 to n do g[i,j]:=maxlongint;
for i:=1 to e do
begin
     readln(u,v,l);
     g[u,v]:=l;
     b[u,v]:=true;
end;
//*****************Dijkstra******************\\
d[1]:=0;for i:=2 to n do d[i]:=g[1,i];
fillchar(qb,sizeof(qb),0);
qb[1]:=true;
repeat
     min:=maxint;u:=0;
     for i:=2 to n do if(not qb[i])and(d[i]<min) then 
      begin min:=d[i];u:=i;end;
     if u<>0 then
     begin
          qb[u]:=true;
          for v:=2 to n do 
            if(not qb[i])and(b[u,v])and(d[v]>d[u]+g[u,v])then
                d[v]:=d[u]+g[u,v];
     end;
until u=0;
for i:=1 to n do writeln(d[i]);
readln;
end.