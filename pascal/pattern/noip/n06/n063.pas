program n063;
const maxn=20;
var
   n,m,i,j,ans:longint;
   t,h,e:array[0..maxn,0..maxn]of longint;
   a:array[0..maxn,0..maxn*maxn*maxn]of boolean;
   d,c:array[0..maxn*maxn]of longint;
   
   function max(a,b:longint):longint;
   begin
        if a>b then exit(a)else exit(b);
   end;
   
   function check(hh,s,e:longint):boolean;
   var i:longint;
   begin
        for i:=s to e do if a[hh,i] then exit(false);
        exit(true);
   end;
   
   function next(hh,s:longint):longint;
   begin
        while not a[hh,s]do inc(s);
        while a[hh,s]do inc(s);
        exit(s);
   end;
   
   procedure work(p,q:longint);
   var i,hh,tt,s:longint;
   begin
        s:=e[p,q-1]+1;hh:=h[p,q];tt:=t[p,q];
        while not check(hh,s,s+tt-1) do s:=next(hh,s);
        e[p,q]:=s+tt-1;
        for i:=s to e[p,q] do a[hh,i]:=true;
   end;
   
begin
readln(m,n);
for i:=1 to m*n do read(d[i]);readln;
for i:=1 to n do for j:=1 to m do read(h[i,j]);
for i:=1 to n do for j:=1 to m do read(t[i,j]);
readln;
fillchar(a,sizeof(a),0);
fillchar(e,sizeof(e),0);
fillchar(c,sizeof(c),0);
for i:=1 to m*n do
begin
     inc(c[d[i]]);
     work(d[i],c[d[i]]);
end;
ans:=0;
for i:=1 to n do ans:=max(ans,e[i,m]);
writeln(ans);
readln;
end.