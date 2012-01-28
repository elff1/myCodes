program twostack;
const maxn=1001;name='twostack';
var
   a,b,d:array[0..maxn]of longint;
   u:array[0..2*maxn]of longint;
   i,j,n,m,k,h1,h2,nn:longint;
   
   procedure stop;
   begin
        //readln;
        close(input);close(output);
        halt;
   end;
   
begin
assign(input,name+'.in');reset(input);
assign(output,name+'.out');rewrite(output);
readln(n);
if n<=0 then begin writeln(0);stop;end;
if n=1 then begin writeln('a b');stop;end;
nn:=n+n;
for i:=1 to n do read(d[i]);readln;
fillchar(a,sizeof(a),0);
fillchar(b,sizeof(b),0);
fillchar(u,sizeof(u),0);
k:=1;u[1]:=1;
i:=1;j:=1;
a[0]:=maxlongint;b[0]:=a[0];
a[1]:=d[1];h1:=1;h2:=0;
repeat
      while(a[h1]=i)or(b[h2]=i)do
      begin
           if a[h1]=i then begin inc(k);u[k]:=2;inc(i);dec(h1);end;
           if b[h2]=i then begin inc(k);u[k]:=4;inc(i);dec(h2);end;
      end;
      if j<n then
      begin
           inc(j);
           if d[j]<a[h1] then begin inc(h1);a[h1]:=d[j];inc(k);u[k]:=1;end else
              if d[j]<b[h2]then begin inc(h2);b[h2]:=d[j];inc(k);u[k]:=3;end
              else begin writeln(0);stop;end;
      end;
until i>n;
for i:=1 to nn-1 do write(chr(ord('a')+u[i]-1),' ');
writeln(chr(ord('a')+u[nn]-1));
stop;
end.

