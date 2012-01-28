program r238;
var
     a,b,c,d:real;
begin
readln(a,b,c,d);
b:=sqrt(b);
d:=sqrt(d);
writeln(sqrt(sqr(b+d)+sqr(a-c)):0:3);
readln;
end.