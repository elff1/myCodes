const maxn=1000;
var i,u,v,l,h,e,n:longint;
     g:array[1..maxn,1..maxn]of longint;
     b:array[1..maxn,1..maxn]of boolean;
     d:array[1..maxn]of longint;
     qb:array[1..maxn]of boolean;
     q:array[1..1000000]of longint;
begin
fillchar(b,sizeof(b),0);
readln(n,e);
for i:=2 to n do d[i]:=maxlongint;
for i:=1 to e do
begin
     readln(u,v,l);
     g[u,v]:=l;
     b[u,v]:=true;
end;
//*****************SPFA******************\\
fillchar(qb,sizeof(qb),0);
q[1]:=1;h:=0;e:=1;
while h<>e do
begin
        inc(h);
        u:=q[h];
        qb[u]:=false;
        for v:=1 to n do if(b[u,v])and(d[v]>d[u]+g[u,v])then
        begin
                d[v]:=d[u]+g[u,v];
                if not qb[v]then begin inc(e);q[e]:=v;qb[v]:=true;end;
        end;
end;
for i:=1 to n do writeln(d[i]);
readln;
end.