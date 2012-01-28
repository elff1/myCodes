program n074;
const maxn=300;maxl=maxlongint;
type node=array[1..maxn]of longint;
var
        n,i,j,k,a,b,c,m,s,u:longint;
        d,g:array[1..maxn]of node;
        f:array[1..maxn]of boolean;

        procedure dfs(k,c:longint);
        var j:longint;
        begin
                d[i,k]:=c;
                for j:=1 to n do
                        if(d[i,j]=maxl)and(g[k,j]>0)then dfs(j,c+g[k,j]);
        end;

        function max(a,b:longint):longint;
        begin
                if a>b then exit(a)else exit(b);
        end;

        function min(a,b:longint):longint;
        begin
                if a<b then exit(a)else exit(b);
        end;

        procedure prepare;
        var m,p,q,i,j:longint;
        begin
                m:=0;
                for i:=1 to n do for j:=1 to n do if d[i,j]>m then
                        begin p:=i;q:=j;m:=d[i,j];end;
                fillchar(f,sizeof(f),0);
                for i:=1 to n do if d[p,q]=d[p,i]+d[i,q] then f[i]:=true;
        end;

begin
readln(n,s);
fillchar(g,sizeof(g),0);
for i:=1 to n do for j:=1 to n do d[i,j]:=maxl;
for i:=2 to n do
begin
        readln(a,b,c);
        g[a,b]:=c;g[b,a]:=c;
end;
for i:=1 to n do dfs(i,0);
prepare;
b:=maxl;
for i:=1 to n do for j:=1 to n do if f[i]and f[j]and(d[i,j]<=s)then
begin
        m:=0;
        for k:=1 to n do
        begin
          c:=maxl;
          for u:=1 to n do if f[u]and(d[i,j]=d[i,u]+d[u,j])then c:=min(c,d[k,u]);
          m:=max(m,c);
        end;
        b:=min(m,b);
end;
writeln(b);
readln;
end.