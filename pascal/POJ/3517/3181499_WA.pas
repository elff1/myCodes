program p3517;
var m,n,k:integer;

  procedure work;
  var
    i,j,p,q,h:integer;
    a:array[0..10000]of integer;
  begin
    for i:=2 to n do a[i-1]:=i;a[n]:=1;
    i:=1;j:=m;h:=j-1;a[h]:=a[j];
    if i<(n-1) then
    repeat              
      p:=(k-1) mod(n-i)+1;q:=0;
      while q<p do
      begin
        h:=j;j:=a[j];inc(q);
      end;
      a[h]:=a[j];j:=h;
      inc(i);
    until i=n-1;
    writeln(a[j]);
  end;

begin
readln(n,k,m);
while n>0 do
begin
  work;
  readln(n,k,m);
end;end.
