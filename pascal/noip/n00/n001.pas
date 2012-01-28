program n001;
const d:string[20]='0123456789ABCDEFGHI';
var n,m,r,i:integer;
    a:array[byte]of byte;
begin
readln(n,r);
i:=0;
repeat
 i:=i+1;
 m:=n mod r;
 n:=n div r;
 if m<0 then begin m:=m-r;n:=n+1;end;
 a[i]:=m;
until n=0;
for n:=i downto 1 do write(d[a[n]+1]);
writeln;
readln;
end.
