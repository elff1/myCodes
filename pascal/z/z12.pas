program skackl;
var n:integer;m:longint;
 procedure work(p,q,i:integer);
 begin
  if(p=q)and(i=n)then begin m:=m+1;exit end;
  if p=q then work(p,q+1,i+1)else
   if i=n then work(p+1,q,i)else
    begin work(p+1,q,i);work(p,q+1,i+1)end
 end;
begin
readln(n);
m:=0;work(0,0,0);
writeln(m);readln
end.
