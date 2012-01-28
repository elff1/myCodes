program z05;
var s:string;i,l,j,t:integer;
    a:array[byte]of integer;
begin
assign(input,'bracket.in');
reset(input);
assign(output,'bracket.out');
rewrite(output);
readln(s);l:=length(s);a[0]:=0;
for i:=1 to l do
 case s[i]of
  '[':a[i]:=-1;
  ']':a[i]:=1;
  '(':a[i]:=-2;
  ')':a[i]:=2;
 end;
for i:=1 to l do if a[i]>0 then
begin
 j:=i-1;t:=0;
 while(j>0)and(a[i]+a[j]<>0)
  or((a[i]+a[j]=0)and(t mod 2=1))do
  begin if a[j]=0 then t:=t+1;j:=j-1;end;
 if j>0 then begin a[i]:=0;a[j]:=0;end;
end;
for i:=1 to l do
 case abs(a[i])of
  1:write('[]');
  2:write('()');
  0:write(s[i]);
 end;
writeln;
close(input);close(output)
end.
