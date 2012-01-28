program MergerSort;{πÈ≤¢≈≈–Ú}
var
        a,b:array[1..100000]of longint;
        n,i:longint;

        procedure merge(p,m,q:longint);
        var
                i,j,k:longint;
        begin
                i:=p;j:=m+1;k:=p-1;
                while(i<=m)and(j<=q)do
                begin
                        if a[i]<a[j]then begin k:=k+1;b[k]:=a[i];i:=i+1;end
                        else begin k:=k+1;b[k]:=a[j];j:=j+1;end;
                end;
                while(i<=m)do begin k:=k+1;b[k]:=a[i];i:=i+1;end;
                while(j<=q)do begin k:=k+1;b[k]:=a[j];j:=j+1;end;
                for k:=p to q do a[k]:=b[k];
        end;

        procedure msort(p,q:longint);
        var
                i,l,m,t,j:longint;
        begin
             m:=trunc(sqrt(n))+1;t:=1;
             for l:=1 to m do
             begin
                  i:=1;
                  while i<=n do
                  begin
                       j:=i+t+t-1;if j>n then j:=n;
                       merge(i,i+t-1,j);
                       i:=j+1;
                  end;
                  t:=t shl 1;
             end;
        end;

begin
readln(n);
for i:=1 to n do read(a[i]);readln;
msort(1,n);
for i:=1 to n do write(a[i],' ');writeln;
readln;
end.
