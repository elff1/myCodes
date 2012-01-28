program n991;
var n,i,m,s,j:integer;
    h:array[byte]of byte;
    a,f:array[byte]of integer;
begin
n:=1;
repeat read(a[n]);n:=n+1;until eoln;
readln;
m:=0;n:=n-1;
fillword(f,sizeof(f),1);
for i:=2 to n do
 for j:=1 to i-1 do
   if(a[j]>=a[i])and(f[j]+1>f[i])then f[i]:=f[j]+1;
for i:=1 to n do if f[i]>m then m:=f[i];
writeln(m);
readln;
end.
