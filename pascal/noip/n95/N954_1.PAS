program n954_1;
var a,b:array[0..255] of integer;
    i,j,n:integer;
    s:set of byte;
 function bt:boolean;
 var e:integer;
 begin
  e:=0;
  for j:=0 to a[i]-1 do if not(j in s) then e:=e+1;
  if e=b[i] then bt:=false else bt:=true
 end;
 procedure bm;
 var t:boolean;
 begin
  a[i]:=b[i];
  s:=s+[a[i]];
  while bt do
   begin
    s:=s-[a[i]];a[i]:=a[i]+1;
    repeat
     t:=false;
     if a[i]in s then t:=true;
     if t then a[i]:=a[i]+1
    until not t;
    s:=s+[a[i]]
   end
 end;
begin
write('n=');readln(n);write('B(0,',n-1,'):');
for i:=0 to n-1 do read(b[i]);readln;
for i:=n-1 downto 0 do bm;
for i:=0 to n-1 do write(a[i],' ');
writeln;readln
end.