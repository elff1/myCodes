program z04;
var n,k,m:integer;
    a:array[1..199]of boolean;
 procedure work(b,d:integer);
 var i,j:integer;
 begin
  if d=k+1 then begin m:=m+1;if m=504 then m:=0;exit end;
  for i:=b to 2*n-k+d-1 do
   for j:=1 to (i+1)div 2*2-1 do
   if a[j]then begin a[j]:=false;work(i+1,d+1);a[j]:=true end;
 end;
begin
assign(input,'empire.in');reset(input);
assign(output,'empire.out');rewrite(output);
readln(n,k);
m:=0;fillchar(a,sizeof(a),1);
work(1,1);
writeln(m);
close(input);close(output);
end.
