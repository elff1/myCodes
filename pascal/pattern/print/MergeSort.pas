program MergerSort;{归并排序,稳定,用于’逆序对‘or’顺序对‘}
var
        a,b:array[1..100000]of longint;
        n,i:longint;

        procedure merge(p,m,q:longint);
        var
                i,j,k:longint;
        begin
                i:=p;j:=m+1;k:=p;
                while k<=q then
                begin
                  if(i<=m){左序列有剩余}and((j>q)or(a[i]<=a[j]))
                  then                    {满足取左边序列当前元素的要求}
                    begin b[k]:=a[i];inc(i);end
                  else
                    begin b[k]:=a[j];inc(j);end;
                  inc(k);
                end;
                for i:=p to q do a[i]:=b[i];
        end;

        procedure msort(p,q:longint);
        var
                i,m:longint;
        begin
                if p<q then
                begin
                        m:=random(q-p)+p;
                        msort(p,m);
                        msort(m+1,q);
                        merge(p,m,q);
                end;
        end;

begin
readln(n);
for i:=1 to n do read(a[i]);readln;
msort(1,n);
for i:=1 to n do write(a[i],' ');writeln;
readln;
end.
