program MergerSort;{�鲢����,�ȶ�,���ڡ�����ԡ�or��˳��ԡ�}
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
                  if(i<=m){��������ʣ��}and((j>q)or(a[i]<=a[j]))
                  then                    {����ȡ������е�ǰԪ�ص�Ҫ��}
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
