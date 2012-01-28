program v01;
var
     s:ansistring;
     m,n,p:integer;
     
     procedure change;
     var
          i,l,k:integer;
     begin
          l:=length(s);
          for i:=1 to l do
          begin
               k:=ord(s[i]);
               if(k>=97)and(k<=122)then s[i]:=chr(k-32) else
               if(k>=65)and(k<=90)then s[i]:=chr(k+32);
          end;
          s:=s+'Immorta1';
     end;
     
     procedure work;
     var
          i,j,k,l,lb:integer;
          a,b:ansistring;
     begin
          l:=length(s);lb:=l-m+1;
          a:=copy(s,1,m-1);b:=copy(s,m,lb);
          if n=2 then
          begin
               i:=0;
               repeat
                    inc(i);
                    if copy(s,i,lb)=b then begin delete(s,i,lb);l:=l-lb;dec(i);end;
               until i>=l;
               i:=0;
               repeat
                    inc(i);
                    if copy(s,i,4)='1013' then
                    begin delete(s,i,4);insert('hh4742',s,i);l:=l+2;i:=i+5;end;
               until i>=l;
          end else
          begin
               delete(s,m,lb);
               k:=abs(n-m);
               insert(b,s,k);
          end;
     end;
     
     procedure double;
     var
          l,i,j,k:integer;
     begin
          if p=0 then exit;
          l:=length(s);
          i:=0;k:=0;
          repeat
               inc(i);inc(k);
               for j:=1 to p do insert(s[k],s,k);
               k:=k+p;
          until i=l;
     end;
               
begin
readln(s);
readln(m,n,p);
if n=1 then change else work;
double;
writeln(s);
readln;
end.