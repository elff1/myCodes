program QuickSort;{øÏÀŸ≈≈–Ú}
var
   a:array[1..100000]of longint;
   n,i:longint;
   
   procedure swap(var a,b:longint);
   var
      t:longint;
   begin
        t:=a;a:=b;b:=t;
   end;
   
   procedure qsort(p,q:longint);
   var
      i,j,m:longint;
   begin
        i:=p;j:=q;m:=a[random(q-p+1)+p];
        repeat
              while a[i]<m do inc(i);
              while a[j]>m do dec(j);
              if i<=j then begin swap(a[i],a[j]);inc(i);dec(j);end;
        until i>j;
        if i<q then qsort(i,q);
        if j>p then qsort(p,j);
   end;
   
begin
readln(n);
for i:=1 to n do read(a[i]);readln;
randomize;
qsort(1,n);
for i:=1 to n do write(a[i],' ');writeln;
readln;
end.
