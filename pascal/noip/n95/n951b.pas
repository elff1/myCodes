program n951b;
var a,b:array[byte]of byte;
    n,t,i,j:byte;s:set of byte;
begin
readln(n);s:=[];
for i:=1 to n do read(a[i]);readln;
for i:=n downto 1 do
begin
 t:=a[i]+1;
 while t in s do t:=t+1;
 b[i]:=t;
 s:=s+t;
end;
for i:=1 to n do write(b[i]);
writeln
end.