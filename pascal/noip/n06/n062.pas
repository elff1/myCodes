program n062;
const maxm=60;maxn=32000;
type node=record v,p,q:longint;end;
var
   n,nn,k,i,j,m,mm,u,v:longint;
   a:array[1..maxm]of node;
   b:array[1..maxm,1..4]of node;
   f:array[1..maxn]of longint;
   function max(a,b:longint):longint;
   begin
        if a>b then exit(a)else exit(b);
   end;
begin
readln(n,m);
for i:=1 to m do with a[i] do readln(v,p,q);
mm:=0;
fillchar(b,sizeof(b),0);
for i:=1 to m do if a[i].q=0 then
begin
     inc(mm);u:=0;v:=0;
     for j:=1 to m do if a[j].q=i then if u=0 then u:=j else v:=j;
     b[mm,1]:=a[i];b[mm,1].p:=a[i].v*a[i].p;
     if u>0 then
     begin b[mm,2].v:=a[i].v+a[u].v;b[mm,2].p:=a[i].p*a[i].v+a[u].p*a[u].v;end;
     if v>0 then
     begin
          b[mm,3].v:=a[i].v+a[v].v;b[mm,3].p:=a[i].p*a[i].v+a[v].p*a[v].v;
          b[mm,4].v:=a[i].v+a[u].v+a[v].v;
          b[mm,4].p:=a[i].p*a[i].v+a[u].p*a[u].v+a[v].p*a[v].v;
     end;
end;
fillchar(f,sizeof(f),0);
for i:=1 to mm do for k:=n downto 0 do for j:=1 to 4 do 
    if (b[i,j].v>0)and(b[i,j].v<=k)then f[k]:=max(f[k],f[k-b[i,j].v]+b[i,j].p);
writeln(f[n]);
end.