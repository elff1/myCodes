program n052;
const maxn=20000;
var
   l,s,t,m,i,j,k,n,h,e:longint;
   f,b,d:array[0..maxn]of longint;
   
   function min(a,b:longint):longint;
   begin
        if a<b then exit(a)else exit(b);
   end;
   
begin
readln(l);
readln(s,t,m);
fillchar(b,sizeof(b),0);
fillchar(d,sizeof(d),0);
if s=t then
begin
     n:=0;
     for i:=1 to m do begin read(e);if e mod s=0 then inc(n);end;readln;
     writeln(n);
     close(input);close(output);
     exit;
end;
read(d[1]);
for i:=2 to m do
begin
     read(e);
     j:=i;
     while e<d[j-1] do begin dec(j);d[j+1]:=d[j];end;
     d[j]:=e;
end;
readln;
h:=0;
for i:=1 to m do if d[i]-d[i-1]>100 then begin h:=h+100;b[h]:=1;end
    else begin h:=h+d[i]-d[i-1];b[h]:=1;end;
if l-d[m]>100 then l:=h+100 else l:=h+l-d[m];{Â·¾¶Ñ¹Ëõ}
for i:=1 to l do f[i]:=maxlongint;
f[0]:=0;
for i:=0 to l do if f[i]<maxlongint then for j:=s to t do
    begin k:=min(i+j,l);f[k]:=min(f[k],f[i]+b[k]);end;
writeln(f[l]);
end.
