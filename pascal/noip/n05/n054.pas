program n05_4;
type ae=array[0..100]of byte;
var a,b:ae;k,i,n,m,j,l:integer;
 function qk:byte;
 var q:byte;t:boolean;
 begin
  if a[k]>0 then q:=2 else
   begin
    t:=true;
    for i:=2 to k do if a[i]=0 then begin t:=false;break end;
    if t then begin if(a[1]=0)or(a[1]=1)then q:=1 else t:=false end;
    if not(t)then q:=0
   end;
  qk:=q
 end;
 procedure mt(var b:ae);
 var c,d:ae;
 begin
  d:=b;fillchar(b,sizeof(b),0);
  for i:=1 to l do if a[i]>0 then
   begin
    fillchar(c,sizeof(c),0);
    for j:=1 to k do if d[j]>0 then if i+j<k+2 then
     begin c[i+j-1]:=a[i]*d[j]+c[i+j-2]div 10;
           c[i+j-2]:=c[i+j-2]mod 10 end;
    c[k]:=c[k]mod 10;
    for j:=1 to k do begin b[j]:=b[j]+c[j]+b[j-1]div 10;
                           b[j-1]:=b[j-1]mod 10 end;
    b[k]:=b[k]mod 10
   end
 end;
 function xd:boolean;
 var t:boolean;
 begin
  t:=true;
  for i:=1 to k do if a[i]<>b[i]then begin t:=false;break end;
  xd:=t
 end;
begin
readln(n,k);
fillchar(a,sizeof(a),0);i:=0;
repeat i:=i+1;a[i]:=n mod 10;n:=n div 10 until n=0;
l:=i;
case qk of
 0:writeln(-1);
 1:writeln(1);
 else begin l:=k;b:=a;m:=0;repeat m:=m+1;mt(b)until xd;writeln(m)end
end;
readln
end.
