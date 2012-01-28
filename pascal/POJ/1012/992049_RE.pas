program p1012(input,output);
var k,n,i,j:byte;m:longint;
    a:array[1..100]of byte;
 function bg(m:longint):boolean;
 var a:array[1..26]of boolean;
     i:byte;j,h:longint;
 begin
   for i:=1 to n do a[i]:=true;
   bg:=true;h:=0;
   while(h<k)and(i>k)do begin j:=0;
    while j<>m do begin i:=i+1;
     if i=n+1 then i:=1;
     if a[i]then j:=j+1
    end;
    a[i]:=false;h:=h+1
   end;
   if(h=k)and(i>k)then bg:=false
 end;
begin
  readln(a[1]);i:=1;
  while a[i]<>0 do begin i:=i+1;readln(a[i])end;
  for j:=1 to i-1 do begin k:=a[j];
   if(k<0)or(k>13)then writeln('input error')else
     begin n:=k*2;m:=2;while bg(m)do m:=m+1;writeln(m)end
   end
end.