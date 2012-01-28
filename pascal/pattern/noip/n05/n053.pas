program n053;
const maxn=50000;
var
   n,i,j,k,h,m:longint;
   d:array[0..maxn,0..2]of longint;
   a,b,c,f:array[0..maxn]of longint;
   
   procedure swap(var a,b:longint);
   var t:longint;
   begin
        t:=a;a:=b;b:=t;
   end;
   
   procedure work;
   var t,i,j:longint;
   begin
        fillchar(f,sizeof(f),0);
        for i:=1 to n do begin t:=(n+a[i]-b[i])mod n;inc(f[t]);end;
        for i:=0 to n-1 do if f[i]>m then m:=f[i];
   end;
        
begin
readln(n);
fillchar(d,sizeof(d),0);
for i:=1 to n do readln(d[i,1],d[i,2]);
fillchar(b,sizeof(b),0);
b[1]:=1;
i:=1;h:=1;k:=d[1,1];b[1]:=1;d[1,0]:=1;
repeat
      inc(i);
      b[i]:=k;d[k,0]:=1;
      if d[k,1]<>h then begin h:=k;k:=d[k,1];end else begin h:=k;k:=d[k,2];end;
until d[k,0]=1;
if k<>1 then begin writeln(-1);readln;exit;end;
for i:=1 to n do write(b[i],' ');writeln;
m:=0;
for i:=1 to n do a[i]:=i;work;
for i:=1 to n do a[i]:=n-i+1;work;
writeln(n-m);
readln;
end.