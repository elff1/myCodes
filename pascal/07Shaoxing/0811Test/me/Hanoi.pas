program z06;
const s:array[1..3]of char=('A','B','C');
var n,m,i,j,d:integer;
    a,b:array[byte]of integer;
 procedure move(k,p,q:integer);
 var i,t:integer;
 begin
  if p=q then exit;
  t:=6-p-q;
  for i:=k-1 downto 1 do move(i,a[i],t);
  writeln('move ',k,' from ',s[p],' to ',s[q]);
  m:=m+1;
  a[k]:=q;
 end;
begin
assign(input,'Hanoi.in');reset(input);
assign(output,'Hanoi.out');rewrite(output);
readln(n);a[0]:=0;b[0]:=1;
for i:=1 to 3 do
begin
 read(m);
 for j:=1 to m do begin read(d);a[d]:=i end;
end;
readln;
for i:=1 to 3 do
begin
 read(m);
 for j:=1 to m do begin read(d);b[d]:=i end;
end;
readln;
m:=0;
for i:=n downto 1 do move(i,a[i],b[i]);
writeln(m);
close(input);close(output);
end.