program n021;
const maxn=100;
var n,i,j,m,ans:longint;
    a:array[0..100]of longint;
begin
readln(n);
m:=0;
for i:=1 to n do begin read(a[i]);inc(m,a[i]);end;readln;
m:=m div n;
ans:=0;
for i:=1 to n-1 do if a[i]<>m then
begin
     inc(ans);
     inc(a[i+1],a[i]-m);
end;
writeln(ans);
readln;
end.

