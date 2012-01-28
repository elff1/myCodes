program n043;
const maxn=100;
var
   i,j,n,ans,m,p,q:longint;
   a,b,d:array[0..maxn]of longint;

   function max(a,b:longint):longint;
   begin
        if a>b then exit(a)else exit(b);
   end;
   
begin
readln(n);
fillchar(a,sizeof(a),0);
fillchar(b,sizeof(b),0);
for i:=1 to n do begin a[i]:=1;b[i]:=1;read(d[i]);end;readln;
a[1]:=1;
for i:=2 to n do for j:=1 to i-1 do if d[i]>d[j]then a[i]:=max(a[i],a[j]+1);
for i:=n-1 downto 1 do for j:=n downto i+1 do
    if d[i]>d[j]then b[i]:=max(b[i],b[j]+1);
m:=0;
for i:=1 to n do m:=max(m,a[i]+b[i]);
writeln(n-m+1);
readln;
end.

