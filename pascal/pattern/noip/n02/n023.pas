program n023;
const d=0.00001;
var
   h,s,k,l,v,s1,s2:extended;
   i,j,m,n,n1,n2:longint;
begin
readln(h,s,v,l,k,n);
s1:=s-v*sqrt(2*(h-k)/10)+l+d;
s2:=s-v*sqrt(2*h/10)-d;
n1:=trunc(s1);
if trunc(s2)<s2 then n2:=trunc(s2)+1 else n2:=trunc(s2);
m:=0;
if n2<0 then n2:=0;
if n1>n-1 then n1:=n-1;
m:=0;
if n1>=n2 then m:=n1-n2+1;
writeln(m);
readln;
end.

