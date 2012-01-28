program mm;
var i,j,k,n,m,l,r,t,b:longint;
    a:array[1..50000]of longint;
begin
assign(input,'mm.in');reset(input);
assign(output,'mm.out');rewrite(output);
readln(n,m);
for i:=1 to n do a[i]:=i;
for i:=1 to m do
begin
 readln(l,r,t);
 for k:=1 to t do
 begin
  b:=a[l];
  for j:=l to r-1 do a[j]:=a[j+1];
  a[r]:=b;
 end;
end;
for i:=1 to n do writeln(a[i]);
close(input);close(output);
end.
