program t01;
var
  n,k,i,j,bi,bj,bl:longint;
  t:boolean;d,m,p:integer;
  a:array[1..100000]of integer;
  b:array[1..30000]of integer;
  f:array[1..30000]of longint;
begin
fillchar(a,sizeof(a),0);
fillchar(b,sizeof(b),0);
readln(n,k);
m:=0;
for i:=1 to n do
begin
  read(d);a[i]:=d;t:=true;
  for j:=1 to m do if b[j]=d then t:=false;
  if t then begin inc(m);b[m]:=d;end;
end;
readln;
bl:=n+1;bi:=0;bj:=0;
for i:=1 to n do
begin
  fillchar(f,sizeof(f),0);
  for j:=i to n do
  begin
    if j-i+1=bl then break;
    inc(f[a[j]]);
    t:=true;
    for p:=1 to m do if f[b[p]]<k then t:=false;
    if t and(j-i+1<bl)then
    begin
      bl:=j-i+1;bi:=i;bj:=j;break;
    end;
  end;
end;
if bl=n+1 then writeln('-1')else writeln(bi,' ',bj);
readln;
end. 
