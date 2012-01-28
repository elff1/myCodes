program word;
const maxn=100;name='word';
var
   i,j,k,m,n,max,min,l:longint;
   s:string;
   b:array[0..maxn]of boolean;

   procedure mb;
   var i,j,k,l:longint;
   begin
        b[0]:=false;b[1]:=false;
        i:=2;
        while i<=maxn do
        begin
             if b[i] then
             begin
                  j:=i+i;
                  while j<=maxn do begin b[j]:=false;j:=j+i;end;
             end;
             inc(i);
        end;
   end;

begin
assign(input,name+'.in');reset(input);
assign(output,name+'.out');rewrite(output);
fillchar(b,sizeof(b),1);
mb;
//for i:=1 to maxn do write(i,b[i],' ');writeln;readln;end.
readln(s);l:=length(s);
for i:=1 to l do s[i]:=upcase(s[i]);
max:=0;min:=101;
for i:=1 to 26 do
begin
     m:=0;
     for j:=1 to l do if ord(s[j])-ord('A')=i-1 then inc(m);
     //writeln(chr(ord('a')+i-1),':',m);
     if m>max then max:=m;
     if(m>0)and(m<min)then min:=m;
end;
//writeln(max,' ',min);readln;end.
m:=max-min;
if b[m] then begin writeln('Lucky Word');writeln(m);end
   else begin writeln('No Answer');writeln(0);end;
//readln;
close(input);close(output);
end.

