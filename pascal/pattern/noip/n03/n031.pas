program n031;
const maxn=200;
var
   i,j,n,m,p,q:longint;
   w:array[0..maxn,0..maxn]of longint;
   f,u:array[0..maxn]of longint;
   b:array[0..maxn]of boolean;
   
   procedure work(k:longint);
   var i,j,t:longint;
   begin
        if f[k]<>0 then exit;
        for i:=1 to n do if w[k,i]<>0 then work(i);
        t:=0;
        for i:=1 to n do if(w[k,i]<>0)and(f[i]>0)then inc(t,f[i]*w[k,i]);
        f[k]:=t-u[k];
   end;
   
begin
readln(n,m);
fillchar(w,sizeof(w),0);
fillchar(b,sizeof(b),0);
for i:=1 to n do readln(f[i],u[i]);
for i:=1 to m do begin read(p,q);readln(w[q,p]);b[p]:=true;end;
for i:=1 to n do work(i);
for i:=1 to n do write(f[i],' ');writeln;
m:=0;
for i:=1 to n do if not b[i]and(f[i]>0)then
    begin inc(m);writeln(i,' ',f[i]);end;
if m=0 then writeln('NULL');
readln;
end.

