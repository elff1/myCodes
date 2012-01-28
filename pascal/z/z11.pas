program knight;
const r:array[1..8,1..2]of integer=
 ((-1,-2),(1,-2),(-2,-1),(2,-1),(-2,1),(2,1),(-1,2),(1,2));
var s,a,b,n,m,e:integer;
    t:array[1..9,1..2]of integer;
 procedure pre(a,b:integer);
 var i,p,q:integer;
 begin
  fillchar(t,sizeof(t),0);
  t[1,1]:=a;t[1,2]:=b;e:=1;
  for i:=1 to 8 do
  begin
   p:=a+r[i,1];q:=b+r[i,2];
   if(p>=0)and(q>=0)and(p<=n)and(q<=m)then
    begin e:=e+1;t[e,1]:=p;t[e,2]:=q end;
  end;
 end;
 function tf(a,b:integer):boolean;
 var i:integer;k:boolean;
 begin
  k:=true;
  for i:=1 to e do if(t[i,1]=a)and(t[i,2]=b)then
   begin k:=false;break end;
  tf:=k
 end;
 procedure work(i,j:integer);
 begin
  if(i=n)and(j=m)then begin s:=s+1;exit end;
  if i<n then if tf(i+1,j)then work(i+1,j);
  if j<m then if tf(i,j+1)then work(i,j+1);
 end;
begin
readln(n,m,a,b);
pre(a,b);
s:=0;work(0,0);
writeln(s);readln
end.
