program p1012;
const a:array[1..13]of longint=(2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881);
type lb=^node;
     node=record d:integer;n:lb end;
var x:integer;h,p:lb;
 procedure jl(s:integer);
 var q:lb;
 begin
  new(q);q^.d:=s;q^.n:=nil;
  if h=nil then begin h:=q;p:=q end else begin p^.n:=q;p:=q end
 end;
 procedure op;
 var q:lb;s:integer;
 begin
  q:=h;
  repeat s:=q^.d;if s>13 then writeln else writeln(a[s]);q:=q^.n until q=nil
 end;
begin
readln(x);h:=nil;
while x>0 do begin if x>13 then jl(0)else jl(x);readln(x)end;
if h<>nil then op
end.