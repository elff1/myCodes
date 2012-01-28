program sum;
var n,i,k,m:longint;l,j:integer;
    s:array[byte]of longint;
 procedure gc(b:longint);
 var i:integer;m:longint;
 begin
  m:=k;
  repeat l:=l+1;s[l]:=m mod 10;m:=m div 10 until m=0;
  for i:=1 to l do
  begin
   s[i]:=s[i]*b+s[i-1]div 10;s[i-1]:=s[i-1]mod 10;
  end;
  while s[l]>9 do
  begin
   l:=l+1;s[l]:=s[l-1]div 10;s[l-1]:=s[l-1]mod 10;
  end;
 end;
 procedure gj(b:longint);
 var i:integer;
 begin
  inc(s[1],b);
  i:=1;
  while s[i]>9 do
  begin
   inc(s[i+1],s[i]div 10);s[i]:=s[i]mod 10;i:=i+1;
  end;
  if i>l then l:=i;
 end;
begin
assign(input,'sum.in');reset(input);
assign(output,'sum.out');rewrite(output);
readln(n,k);l:=0;
fillchar(s,sizeof(s),0);
if n>k then begin gc(n-k);m:=k-1 end else m:=n;
for i:=2 to m do
 if(i*2>k)then gj(k-i)else gj(k mod i);
if l=0 then write(0) else for j:=l downto 1 do write(s[j]);
writeln;
close(input);close(output);
end.
