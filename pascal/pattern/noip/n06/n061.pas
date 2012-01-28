program n061;
const maxn=400;
var
        n,nn,i,j,k,l,ans:longint;
        a:array[1..maxn]of record h,e:longint;end;
        f:array[1..maxn*2,1..maxn*2]of longint;
        function max(a,b:longint):longint;
        begin
                if a>b then exit(a)else exit(b);
        end;
begin
readln(n);
for i:=1 to n do read(a[i].h);readln;
for i:=1 to n-1 do a[i].e:=a[i+1].h;a[n].e:=a[1].h;
for i:=1 to n-1 do a[n+i]:=a[i];
nn:=n+n-1;
fillchar(f,sizeof(f),0);
for l:=2 to n do for i:=1 to nn-l+1 do
begin
        j:=l+i-1;
        for k:=i to j-1 do
                f[i,j]:=max(f[i,j],f[i,k]+f[k+1,j]+a[i].h*a[k].e*a[j].e);
end;
ans:=0;
for i:=1 to n do ans:=max(ans,f[i,i+n-1]);
writeln(ans);
readln;
end.
