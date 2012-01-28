program n954;
var a,b:array[0..255] of integer;i,n:integer;
 procedure bm;
 var j,m:integer;t:boolean;
 begin
  m:=0;
  for j:=i+1 to n-1 do if b[i]>=a[j] then m:=m+1;
  a[i]:=b[i]+m;
  repeat
   t:=false;
   for j:=i+1 to n-1 do if a[i]=a[j] then t:=true;
   if t then a[i]:=a[i]+1
  until not t
 end;
begin
write('n=');readln(n);write('B(0,',n-1,'):');
for i:=0 to n-1 do read(b[i]);readln;
for i:=n-1 downto 0 do bm;
for i:=0 to n-1 do write(a[i],' ');
writeln;readln
end.