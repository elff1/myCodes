program kmp;
const maxn=100000;
var
   n,i,m,ls,lt:longint;
   pi,d:array[0..maxn]of longint;
   s,t:ansistring;

   procedure makepi;
   var i,k:longint;
   begin
        fillchar(pi,sizeof(pi),0);
        k:=0;
        for i:=2 to lt do
        begin
             while(k>0)and(t[i]<>t[k+1]) do k:=pi[k];
             if t[i]=t[k+1]then inc(k);
             pi[i]:=k;
        end;
   end;
   
   procedure kmp;
   var i,j,k:longint;
   begin
        k:=0;
        for i:=1 to ls do
        begin
             while(k>0)and(s[i]<>t[k+1])do k:=pi[k];
             if s[i]=t[k+1]then inc(k);
             if k=lt then begin inc(m);d[m]:=i-lt+1;k:=pi[k];end;
        end;
   end;
   
begin
readln(t);readln(s);
lt:=length(t);ls:=length(s);
makepi;{²úÉúpi}
m:=0;
kmp;
if m=0 then writeln('There must be something wrong.')else
   begin writeln(m);for i:=1 to m do writeln(d[i]);end;
readln;
end.

