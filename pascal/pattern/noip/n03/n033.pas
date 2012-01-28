program n033;
const maxn=30;
var
   i,j,l,k,n,m,bk:longint;t:int64;
   f:array[0..maxn,0..maxn]of int64;
   b:array[0..maxn,0..maxn]of longint;
   d:array[0..maxn]of longint;
   
   procedure print(p,q:longint);
   var i,j:longint;
   begin
        write(b[p,q],' ');
        if p=q then exit;
        if p<=b[p,q]-1 then print(p,b[p,q]-1);
        if b[p,q]+1<=q then print(b[p,q]+1,q);
   end;
   
begin
readln(n);
fillchar(f,sizeof(f),0);
fillchar(b,sizeof(b),0);
for i:=1 to n do begin read(d[i]);f[i,i]:=d[i];f[i,i-1]:=1;b[i,i]:=i;end;readln;
for l:=2 to n do for i:=1 to n-1 do
begin
     j:=i+l-1;
     m:=0;
     for k:=i to j do
     begin
          t:=f[i,k-1]*f[k+1,j]+d[k];
          if t>m then begin m:=t;bk:=k;end;
     end;
     f[i,j]:=m;b[i,j]:=bk;
end;
writeln(f[1,n]);
print(1,n);writeln;
readln;
end.

