program v01;
var
  i,j,n:integer;
  a:array[1..1000]of integer;
  d:array[1..1000]of string;
  s:ansistring;
  
  procedure change(p,q:integer);
  var t:integer;s:string;
  begin
    t:=a[p];a[p]:=a[q];a[q]:=t;
    s:=d[p];d[p]:=d[q];d[q]:=s;
  end;
      
  procedure qsort(p,q:integer);
  var i,j,m:integer;
  begin
    m:=a[random(q-p)+p];i:=p;j:=q;
    repeat
      while(a[i]<m)do inc(i);
      while(a[j]>m)do dec(j);
      if i<=j then begin change(i,j);inc(i);dec(j);end;
    until i>j;
    if i<q then qsort(i,q);
    if j>p then qsort(p,j);
  end;
  
begin
readln(s);
n:=0;i:=pos(' ',s);
repeat
  inc(n);
  val(copy(s,1,i-1),a[n]);
  delete(s,1,i);
  i:=pos(' ',s);
until i=0;
inc(n);
val(s,a[n]);
readln(s);
for j:=1 to n-1 do
begin
  i:=pos(' ',s);
  d[j]:=copy(s,1,i-1);
  delete(s,1,i);
end;
d[n]:=s;
qsort(1,n);
for i:=1 to n do writeln(a[i],' ',d[i]);
readln;
end.

