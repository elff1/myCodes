program distinct;
type tp=^node;
     node=record
           n:integer;s:char;m:longint;
           k:array[1..26]of tp;
          end;
          
var head:tp;a:array[1..50000]of char;
    n,i:integer;
    
 procedure make(k:integer);
 var i,j,qn:integer;p,q:tp;t:boolean;
 begin
  q:=head;p:=q;
  for i:=k to n do
  begin
   t:=false;qn:=q^.n;
   for j:=1 to qn do
    if q^.k[j]^.s=a[i]then begin t:=true;break end;
   if t then begin q:=q^.k[j];continue;end;
   new(p);inc(q^.n);q^.k[q^.n]:=p;
   p^.s:=a[i];p^.n:=0;q:=p;
  end;
 end;
 
 procedure rdln(q:tp);
 var i,qn:integer;p:tp;
 begin
  qn:=q^.n;q^.m:=qn;
  for i:=1 to qn do
  begin
   p:=q^.k[i];rdln(p);
   inc(q^.m,p^.m)
  end;
 end;
 
begin
assign(input,'distinct.in');
assign(output,'distinct.out');
reset(input);rewrite(output);
n:=0;
repeat n:=n+1;read(a[n])until eoln;
new(head);head^.n:=0;
for i:=1 to n do make(i);
rdln(head);writeln(head^.m);
close(input);close(output);
end.
