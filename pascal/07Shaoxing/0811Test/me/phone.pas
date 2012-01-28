program z09;
type tp=array[0..100]of byte;
var s:string;a,t:tp;p:boolean;
    d:array[1..100]of tp;
    c:array[1..100]of string;
    n,i,l,m:integer;
 procedure charge(s:string;var b:tp);
 var i,l:byte;
 begin
  l:=length(s);b[0]:=l;
  for i:=1 to l do case s[i] of
   'a','b','c':b[i]:=1;
   'd','e','f':b[i]:=2;
   'g','h','i':b[i]:=3;
   'j','k','l':b[i]:=4;
   'm','n':b[i]:=5;
   'o','p','q':b[i]:=6;
   'r','s','t':b[i]:=7;
   'u','v','w':b[i]:=8;
   'x','y','z':b[i]:=9;
  end;
 end;
 function pd(k,j:integer):boolean;
 var i:integer;
 begin
  for i:=2 to d[j,0] do if a[i+k-1]<>d[j,i]then exit(false);
  exit(true)
 end;
 procedure pt;
 var i:integer;
 begin
  for i:=1 to m do write(c[t[i]],' ');
  writeln
 end;
 procedure work(k:integer);
 var i:byte;
 begin
  if k=l+1 then begin pt;p:=false;exit end;
  for i:=1 to n do 
  begin
   if(d[i,1]=a[k])and pd(k,i)then
    begin m:=m+1;t[m]:=i;work(k+d[i,0]);m:=m-1 end;
   if not p then exit
  end
 end;
begin
assign(input,'phone.in');reset(input);
assign(output,'phone.out');rewrite(output);
fillchar(a,sizeof(a),0);
fillchar(t,sizeof(t),0);
fillchar(d,sizeof(d),0);
readln(n);m:=0;p:=true;
readln(s);l:=length(s);
for i:=1 to l do val(s[i],a[i]);
for i:=1 to n do begin readln(s);c[i]:=s;charge(s,d[i])end;
work(1);
if p then writeln('No Solutions!');
close(input);close(output);
end.
