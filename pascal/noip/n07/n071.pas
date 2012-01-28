program n071;
const maxn=200000;
var
        n,i,j,m,t:longint;
        a:array[1..maxn] of longint;

        procedure swap(p,q:longint);
        var t:longint;
        begin
                t:=a[p];a[p]:=a[q];a[q]:=t;
        end;

        procedure qsort(p,q:longint);
        var i,j,m:longint;
        begin
                i:=p;j:=q;m:=a[random(q-p+1)+p];
                repeat
                        while a[i]<m do inc(i);
                        while a[j]>m do dec(j);
                        if i<=j then begin swap(i,j);inc(i);dec(j);end;
                until i>j;
                if i<q then qsort(i,q);
                if j>p then qsort(p,j);
        end;

begin
randomize;
readln(n);
for i:=1 to n do readln(a[i]);
qsort(1,n);
i:=0;
repeat
        inc(i);m:=1;t:=a[i];
        while(i<n)and(a[i+1]=t)do begin inc(i);inc(m);end;
        writeln(t,' ',m);
until i>=n;
readln;
end.