program n982;
var a:array[1..20]of string;
    n,i,j,k:integer;t:string;
begin
readln(n);readln(t);
for i:=1 to n-1 do
begin
 k:=pos(' ',t);
 a[i]:=copy(t,1,k-1);
 delete(t,1,k);
end;
a[n]:=t;
for i:=1 to n-1 do
 for j:=i+1 to n do
  if a[i]<a[j] then
  begin
   t:=a[i];a[i]:=a[j];a[j]:=t;
  end;
t:='';
for i:=1 to n do t:=t+a[i];
writeln(t);
readln;
end.
