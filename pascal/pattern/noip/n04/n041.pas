program n041;
const n=12;
var
   i,m,h,s:longint;
   f:array[0..n]of longint;
begin
h:=0;s:=0;
for i:=1 to n do
begin
     readln(m);
     inc(h,300);
     dec(h,m);
     if h<0 then begin writeln(-i);readln;exit;end;
     inc(s,h div 100*100);
     h:=h mod 100;
end;
inc(s,s div 5);
writeln(s+h);
readln;
end.

