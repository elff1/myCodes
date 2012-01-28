program p1002(input,output);
const ca=['-','0'..'9'];cb=['A'..'P','R'..'Y'];
type pt=^node;
     node=record s,m:longint;n:pt end;
var h,p:pt;x,n:longint;s:string;
 function ok:boolean;
 var t:boolean;i,l,k:integer;
 begin
  readln(s);l:=length(s);t:=true;k:=0;
  for i:=1 to l do if not((s[i]in ca)or(s[i]in cb))then
     begin t:=false;break end;
  if t then
  begin
   for i:=l downto 1 do if s[i]='-'then
    begin delete(s,i,1);k:=k+1 end;
   l:=l-k;if l<>7 then t:=false
  end;
  ok:=t
 end;
 function ce:longint;
 var i,z:integer;c:longint;
 begin
  for i:=1 to 7 do if s[i]in cb then
    case s[i]of
     'A','B','C':s[i]:='2';
     'D','E','F':s[i]:='3';
     'G','H','I':s[i]:='4';
     'J','K','L':s[i]:='5';
     'M','N','O':s[i]:='6';
     'P','R','S':s[i]:='7';
     'T','U','V':s[i]:='8';
     'W','X','Y':s[i]:='9'
    end;
  val(s,c,z);ce:=c
 end;
 procedure jr(c:longint);
 var q,t,r:pt;
 begin
  if h=nil then
    begin new(p);p^.s:=c;p^.m:=1;p^.n:=nil;h:=p end
  else
    if c<h^.s then
      begin new(q);q^.s:=c;q^.m:=1;q^.n:=h;h:=q end
    else
      begin
       t:=nil;r:=h;
       while(r^.s<c)and(r<>nil)do begin t:=r;r:=r^.n end;
       if c=r^.s then inc(r^.m)
        else
          if r=nil then
            begin
              new(q);q^.s:=c;q^.m:=1;
              q^.n:=nil;p^.n:=q;p:=q
            end
          else
            begin
              new(q);q^.s:=c;q^.m:=1;
              q^.n:=r;t^.n:=q
            end
      end
 end;
 procedure op;
 var t:boolean;q:pt;
 begin
  t:=true;q:=h;
  while q<>nil do
  begin
   if q^.m>1 then begin t:=false;
    writeln(q^.s div 10000,'-',q^.s mod 10000,' ',q^.m)end;
   q:=q^.n
  end;
  if t then writeln('No duplicates.')
 end;
begin
readln(n);h:=nil;
for x:=1 to n do if ok then jr(ce);op
end.