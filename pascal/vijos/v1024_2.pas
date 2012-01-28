program v02;
const cx:array[1..4]of integer=(-1,0,1,0);cy:array[1..4]of integer=(0,-1,0,1);
var
     n,m,i,j:integer;
     g:array[0..22,0..22]of char;
     

     procedure work;
     var
          i,j,k,d:integer;
          f:array[0..22,0..22]of integer;

          procedure paint(x,y,d:integer);
          var
               i:integer;
          begin
               if f[x,y]>0 then exit;
               f[x,y]:=d;
               for i:=1 to 4 do if g[x+cx[i],y+cy[i]]=g[x,y]then paint(x+cx[i],y+cy[i],d);
          end;
     
     begin
          fillchar(f,sizeof(f),255);
          for i:=1 to m do for j:=1 to n do f[i,j]:=0;
          for i:=1 to n do paint(1,i,1);
          d:=1;
          repeat
               inc(d);
               for i:=d to m do for j:=1 to n do for k:=1 to 4 do 
               if (f[i,j]=0)and(f[i+cx[k],j+cy[k]]=d-1) then paint(i,j,d);
               for i:=1 to n do if f[m,i]<>0 then begin writeln(f[m,i]);exit;end;
          until false;
     end;
          
begin
readln(m,n);
for i:=1 to m do
begin
     for j:=1 to  n do read(g[i,j]);
     readln;
end;
work;
readln;
end.