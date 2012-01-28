program n014;
const maxn=10;
var
   n,i,j,k,m,p,q,w:longint;
   f1,f2,d:array[0..maxn,0..maxn]of longint;
   s:array[0..maxn,0..maxn]of longint;
   function max(a,b:longint):longint;begin if a>b then exit(a);exit(b);end;
begin
readln(n);
fillchar(d,sizeof(d),0);
readln(p,q,w);
repeat
      d[p,q]:=w;
      readln(p,q,w);
until p=0;
fillchar(s,sizeof(s),0);
for i:=1 to n do
begin
     s[i,1]:=d[i,1];
     for j:=2 to n do s[i,j]:=s[i,j-1]+d[i,j];
end;
fillchar(f1,sizeof(f1),0);
fillchar(f2,sizeof(f2),0);
for j:=1 to n do for i:=1 to j do f1[i,j]:=s[1,j];
for k:=2 to n do
begin
     for i:=1 to n do for j:=i to n do for p:=i to n do for q:=max(p,j) to n do
     if p>=j then f2[p,q]:=max(f2[p,q],f1[i,j]+s[k,q]-s[k,i-1])else
         f2[p,q]:=max(f2[p,q],f1[i,j]+s[k,p]-s[k,i-1]+s[k,q]-s[k,j-1]);
     f1:=f2;
end;
writeln(f1[n,n]);
readln;
end.

