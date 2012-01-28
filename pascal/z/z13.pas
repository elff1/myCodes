program point24;
const b:array[1..4]of char=('+','-','*','/');
var a:array[1..4]of 1..9;c:array[1..3]of string;
    i,k:integer;t:boolean;s:set of 1..4;
 procedure work(m:integer);
 var i,j,x:integer;
  procedure print(p,j,q:integer);
  var w:integer;r:string;
  begin
   k:=k-1;
   if q>p then begin w:=q;q:=p;p:=w end;
   str(p,r);c[k]:=c[k]+r;c[k]:=c[k]+b[j];
   str(q,r);c[k]:=c[k]+r;c[k]:=c[k]+'=';
   str(x,r);c[k]:=c[k]+r;
  end;
 begin
  if(m=24)and(s=[])then t:=true;
  if s=[] then exit;
  for i:=1 to 4 do if i in s then
   begin
    s:=s-[i];
    for j:=1 to 4 do
    begin
     case j of
      1:begin x:=m+a[i];work(x)end;
      2:if m>=a[i]then begin x:=m-a[i];work(x)end;
      3:begin x:=m*a[i];work(x)end;
      4:if m mod a[i]=0 then begin x:=m div a[i];work(x)end
     end;
     if t then break;
    end;
    if t then begin print(m,j,a[i]);exit end;
    s:=s+[i]
   end
 end;
begin
for i:=1 to 4 do read(a[i]);readln;
t:=false;s:=[1,2,3,4];k:=4;
for i:=1 to 4 do
 begin s:=s-[i];work(a[i]);if t then break;s:=s+[i] end;
if t then for i:=1 to 3 do writeln(c[i]) else writeln('No answer!');
readln
end.
