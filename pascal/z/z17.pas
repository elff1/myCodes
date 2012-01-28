program track;
var a:array[-1..20]of byte;
    n,r:byte;
 procedure work(k:integer);
 var i:byte;
 begin
  a[k]:=a[k-1]+1;
  repeat
   if k=r then
    begin
     for i:=1 to r do write(a[i]:3);writeln
    end
   else work(k+1);
   inc(a[k])
  until(a[k]>n-r+k)or(a[0]>0)
 end;
begin
fillchar(a,sizeof(a),0);
readln(n,r);
a[-1]:=-1;work(0);
readln
end.