program p1002(input,output);
var n,i,j,m,k,s:byte;st:string;
    bb:boolean;x,y:integer;h:longint;
    a:packed array[1..100]of string;
    b:packed array[1..100]of longint;
    c:packed array[1..50]of longint;
    d:array[1..50]of byte;
begin
readln(n);for i:=1 to n do readln(a[i]);
for i:=1 to n do
 begin
  st:=a[i];s:=length(st);bb:=false;j:=0;m:=s;
  repeat
   j:=j+1;k:=j+m-s;delete(a[i],k,1);
   if(ord(st[j])>64)and(ord(st[j])<90)and(st[j]<>'Q')then
    case st[j]of
     'A','B','C':insert('2',a[i],k);
     'D','E','F':insert('3',a[i],k);
     'G','H','I':insert('4',a[i],k);
     'J','K','L':insert('5',a[i],k);
     'M','N','O':insert('6',a[i],k);
     'P','R','S':insert('7',a[i],k);
     'T','U','V':insert('8',a[i],k);
     'W','X','Y':insert('9',a[i],k)
    end
   else if(ord(st[j])>47)and(ord(st[j])<58)then insert(st[j],a[i],k)
         else if st[j]='-'then m:=m-1 else
               begin bb:=true;writeln('No.',i,' error')end
  until(j=s)or bb;
  if not bb then val(a[i],b[i],x)
 end;
s:=0;
for i:=1 to n-1 do if b[i]>0 then
 begin
   k:=1;
   for j:=i+1 to n do
    if b[j]=b[i]then
     begin k:=k+1;if k=2 then begin s:=s+1;c[s]:=b[i]end;b[j]:=0;d[s]:=k end
 end;
for i:=1 to s-1 do
 for j:=i+1 to s do
  if c[i]>c[j]then
   begin h:=c[i];c[i]:=c[j];c[j]:=h;m:=d[i];d[i]:=d[j];d[j]:=m end;
for i:=1 to s do
 begin x:=c[i]div 10000;y:=c[i]mod 10000;writeln(x,'-',y,' ',d[i])end
end.