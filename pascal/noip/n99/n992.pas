program n992;
type tp=array[byte]of byte;
var a:tp;m:string;t:boolean;
    n,l,i,step:integer;

  function ok:boolean;
  var i:integer;
  begin
   for i:=1 to (l div 2) do
    if a[i]<>a[l-i+1]then exit(false);
   exit(true);
  end;

  procedure db(var a:tp);
  var b:tp;i:integer;
  begin
   fillchar(b,sizeof(b),0);
   for i:=1 to l do b[i]:=a[l-i+1];
   for i:=1 to l do
   begin
     inc(a[i],b[i]);
     inc(a[i],a[i-1]div n);
     a[i-1]:=a[i-1]mod n;
   end;
   while a[l]>n-1 do
   begin
     l:=l+1;
     a[l]:=a[l-1]div n;
     a[l-1]:=a[l-1]mod n;
   end;
  end;

begin
readln(m);
l:=pos(' ',m);
val(copy(m,1,l-1),n,step);
delete(m,1,l);
step:=0;l:=length(m);
fillchar(a,sizeof(a),0);
for i:=1 to l do
 case m[i]of
   '0'..'9':a[i]:=ord(m[i])-48;
   'A'..'F':a[i]:=ord(m[i])-55;
 end;
t:=ok;
while not(t)and(step<30)do
 begin
   inc(step);
   db(a);
   t:=ok;
 end;
if not(t)and(step=30)then writeln('Impossible!')
                     else writeln(step);
readln;
end.
