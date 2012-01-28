program compage;
var a:array[0..20]of byte;
    i,j,n,r:byte;
begin
fillchar(a,sizeof(a),0);
readln(n,r);
i:=0;
if(r>0)and(n>=r)then
 repeat
  while a[i]>n-r+i do begin i:=i-1;inc(a[i])end;
  if i=r then
   begin
    for j:=1 to r do write(a[j]:3);writeln;
    inc(a[i])
   end
  else
   begin i:=i+1;a[i]:=a[i-1]+1 end
 until a[0]>0;
readln;
end.
