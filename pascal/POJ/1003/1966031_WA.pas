program p1003;
type lb=^node;
     node=record d,m:longint;n:lb end;
var h,e,g,p,q,r:lb;s:real;n,y:longint;
begin
readln(s);n:=0;h:=nil;
while s>0 do
 begin
  n:=n+1;new(r);y:=trunc(s*100);r^.d:=y;r^.m:=n;r^.n:=nil;
  if h=nil then h:=r else
   begin 
    p:=nil;q:=h;
    while(q<>nil)and(q^.d<y)do begin p:=q;q:=q^.n end;
    if p=nil then begin r^.n:=h;h:=r end else
     if q=nil then p^.n:=r else begin r^.n:=q;p^.n:=r end
   end;
  readln(s)
 end;
n:=0;s:=0;g:=h;e:=nil;
while g<>nil do
 begin
  y:=g^.d;
  if y>520 then n:=0 else while s<y do begin n:=n+1;s:=s+100/(n+1)end;
  new(r);r^.d:=n;y:=g^.m;r^.m:=y;r^.n:=nil;g:=g^.n;
  if e=nil then e:=r else
   begin 
    p:=nil;q:=e;
    while(q<>nil)and(q^.m<y)do begin p:=q;q:=q^.n end;
    if p=nil then begin r^.n:=e;e:=r end else
     if q=nil then p^.n:=r else begin r^.n:=q;p^.n:=r end
   end
 end;
p:=e;while p<>nil do begin if p^.d=0 then writeln else writeln(p^.d,' card(s)');p:=p^.n end
end.