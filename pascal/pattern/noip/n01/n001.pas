program n001;
const c:string[20]='0123456789ABCDEFGHI';
var
   n,r:longint;
   procedure work(n,r:longint);
   var m:longint;
   begin
        if n=0 then exit;
        m:=n mod r;n:=n div r;
        if m<0 then begin m:=m-r;n:=n+1;end;
        work(n,r);
        write(c[m+1]);
   end;
begin
readln(n,r);
work(n,r);
writeln;
readln;
end.

