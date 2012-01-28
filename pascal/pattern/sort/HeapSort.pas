program HeapSort;{¶ÑÅÅÐò}
var
   a:array[1..100000]of longint;
   n,i:longint;
   
   procedure swap(var a,b:longint);
   var
      t:longint;
   begin
        t:=a;a:=b;b:=t;
   end;
   
   procedure up(p:longint);
   var q:longint;
   begin
        q:=p shr 1;
        while(q>=1)and(a[p]<a[q])do
        begin
             swap(a[p],a[q]);
             p:=q;q:=p shr 1;
        end;
   end;
   
   procedure down(k,n:longint);
   var
      p,q:longint;
   begin
        while(k shl 1)<=n do
        begin
             p:=k shl 1;q:=p+1;
             if q>n then begin if a[k]<a[p] then swap(a[k],a[p]);exit;end;
             if(a[k]>=a[p])and(a[k]>=a[q])then exit;
             if(a[p]<a[q])then begin swap(a[k],a[q]);k:=q;end
                          else begin swap(a[k],a[p]);k:=p;end;
        end;
   end;
   
   procedure hsort;
   var
      i:integer;
   begin
        for i:=n shr 1 downto 1 do down(i,n);{½¨¶Ñ,or for i:=2 to n do up(i);}
        for i:=n downto 2 do begin swap(a[1],a[i]);down(1,i-1);end;
   end;
   
begin
readln(n);
for i:=1 to n do read(a[i]);
readln;
hsort;
for i:=1 to n do write(a[i],' ');
writeln;
readln;
end.

