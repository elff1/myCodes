program n981;
var k,g:array[0..20,1..2]of integer;
    n,m,a,x,i,y:integer;
begin
readln(a,n,m,x);
k[0,1]:=0;k[0,2]:=0;
k[1,1]:=1;k[1,2]:=0;
k[2,1]:=0;k[2,2]:=1;
for i:=3 to n-3 do
begin
 k[i,1]:=k[i-1,1]+k[i-2,1];
 k[i,2]:=k[i-1,2]+k[i-2,2];
end;
g[1,1]:=1;g[1,2]:=0;
g[n,1]:=0;g[n,2]:=0;
for i:=2 to n-1 do
begin
 g[i,1]:=k[i-2,1]+g[i-1,1];
 g[i,2]:=k[i-2,2]+g[i-1,2];
end;
y:=(m-g[n-1,1]*a)div g[n-1,2];
writeln(g[x,1]*a+g[x,2]*y);
readln;
end.