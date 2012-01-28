program p3340;
var a:array[1..100]of integer;
    w,i:integer;s,m:string;
 procedure work(var n:integer);
 var i,j,l,t:integer;a,b:array[1..10]of byte;p:boolean;
 begin
  l:=length(s);n:=0;j:=1;t:=0;
  for i:=1 to l do
  begin
   if s[i]='?' then a[i]:=10 else a[i]:=ord(s[i])-48;
   b[i]:=ord(m[i])-48
  end;
  while j<=l do
  begin
   i:=j;p:=true;
   while(a[i]<=b[i])do if a[i]=b[i]then i:=i+1 else exit;
   j:=i;t:=1;
   if a[j]<10 then begin for i:=j to l do if a[i]=10 then t:=t*10;n:=n+t;exit end;
   t:=a[j]-b[j]-1;j:=j+1;
   for i:=j to l do if a[i]=10 then begin t:=t*10;p:=false end;
   if p then
   begin
    p:=false;n:=n+t;
    while(a[j]>=b[j])and(j<=l)do
     begin if a[j]>b[j]then begin p:=true;break end;j:=j+1;end;
    if p then n:=n+1;
    exit;
   end;
   n:=n+t;
  end;
 end; 
begin
readln(s);w:=0;
while(s<>'#')do
begin
 readln(m);w:=w+1;
 work(a[w]);
 readln(s)
end;
for i:=1 to w do writeln(a[i]);
end.
