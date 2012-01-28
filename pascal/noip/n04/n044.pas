program n04_4;
var a:array[1..10000]of integer;
    b:array[1..10000]of boolean;
    p,m,n,i,j,k:integer;
begin
readln(n);readln(m);
for i:=1 to n do read(a[i]);readln;
for i:=1 to m do
begin
 j:=n-1;while a[j+1]<a[j]do j:=j-1;
 fillchar(b,sizeof(b),1);
 for k:=1 to j-1 do b[a[k]]:=false;
 p:=0;repeat p:=p+1 until b[p]and(p>a[j]);
 a[j]:=p;b[p]:=false;
 for k:=1 to n do if b[k] then
  begin j:=j+1;a[j]:=k end
end;
for i:=1 to n do write(a[i],' ');
writeln;readln
end.
