program n051;
const maxn=100;
var
   i,j,m,n,s,a,b,c,d,e:longint;
   f:array[0..maxn]of record m:longint;n:string;end;
   u:char;t:string;
begin
fillchar(f,sizeof(f),0);
readln(n);
for i:=1 to n do
begin
     t:='';
     read(u);while u<>' ' do begin t:=t+u;read(u);end;
     f[i].n:=t;
     read(a,b);
     read(u,u);if u='Y' then c:=1 else c:=0;
     read(u,u);if u='Y' then d:=1 else d:=0;
     readln(e);
     m:=0;
     if(a>80)and(e>=1)then inc(m,8000);
     if(a>85)and(b>80)then inc(m,4000);
     if a>90 then inc(m,2000);
     if(a>85)and(d=1)then inc(m,1000);
     if(b>80)and(c=1)then inc(m,850);
     f[i].m:=m;
end;
m:=0;s:=0;
for i:=1 to n do
begin
     if f[i].m>f[m].m then m:=i;
     inc(s,f[i].m);
end;
writeln(f[m].n);
writeln(f[m].m);
writeln(s);
readln;
end.
