program n951a;
var a,b:array[byte]of byte;
    n,t,i,j:byte;
begin
readln(n);
for i:=1 to n do read(a[i]);
readln;
for i:=1 to n do
begin
 t:=0;
 for j:=1 to i-1 do
  if a[i]>a[j]then t:=t+1;
 b[i]:=t;
end;
for i:=1 to n do write(b[i]);
writeln;
end.