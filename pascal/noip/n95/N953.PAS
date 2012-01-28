program n953;
var a:array[1..255]of byte;
    n,m,i:integer;
 procedure se(x:integer);
 begin
  m:=0;
  repeat
   m:=m+1;
   a[m]:=x mod 2;
   x:=x div 2
  until x=0
 end;
 function ab:boolean;
 var j,x:integer;
 begin
  x:=0;
  for j:=1 to m do
   if a[j]=1 then x:=x+1;
  if x>m-x then ab:=true else ab:=false
 end;
begin
for i:=1 to 1000 do
begin
 se(i);
 if ab then n:=n+1
end;
writeln('A=',n,' B=',1000-n);readln
end.