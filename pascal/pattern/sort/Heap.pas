program n042;
const maxn=10000;maxl=maxlongint;
var
   i,j,n,m,ans:longint;
   d:array[0..maxn]of longint;
   
   procedure swap(var a,b:longint);
   var t:longint;
   begin
        t:=a;a:=b;b:=t;
   end;
   
   procedure up(p:longint);
   var q:longint;
   begin
        q:=p shr 1;
        while(q>=1)and(d[p]<d[q])do
        begin
             swap(d[p],d[q]);
             p:=q;q:=p shr 1;
        end;
   end;
   
   procedure down(k,n:longint);
   var p,q:longint;
   begin
        repeat
              p:=k shl 1;q:=p+1;
              if q>n then begin if d[p]<d[k] then swap(d[p],d[k]);exit;end;
              if(d[p]>=d[k])and(d[q]>=d[k])then exit;
              if d[p]<d[q]then begin swap(d[p],d[k]);k:=p;end else
                 begin swap(d[q],d[k]);k:=q;end;
        until k shl 1>n;
   end;
   
begin
fillchar(d,sizeof(d),0);
readln(n);
{½¨¶Ñ}
read(d[1]);
for i:=2 to n do begin read(d[i]);up(i);end;readln;

ans:=0;
for i:=2 to n do
begin
     m:=d[1];d[1]:=d[n-i+2];down(1,n-i+1);
     inc(d[1],m);inc(ans,d[1]);down(1,n-i+1);
end;
writeln(ans);
readln;
end.