program soldier;
var a:array[1..26,1..26]of boolean;
    d,n,m:array[1..26]of 0..26;
    x:array[1..26]of string;
    s:set of 0..26;i,j,c,p,q,k:0..26;
begin
fillchar(a,sizeof(a),0);
fillchar(d,sizeof(d),0);
fillchar(n,sizeof(n),0);
s:=[];readln(c);
for i:=1 to c do
begin
 readln(p,q);
 s:=s+[p];s:=s+[q];
 a[p,q]:=true;
 inc(d[q]);
end;
k:=0;
for i:=1 to 26 do if i in s then
 begin k:=k+1;m[k]:=i;end;
for i:=1 to k do
begin
 j:=1;
 while(j<k)and(d[m[j]]>0)do j:=j+1;
 if(j=k)and(d[m[j]]>0)then
  begin writeln('wrong');halt end;
 n[i]:=m[j];d[m[j]]:=26;
 for c:=1 to k do if a[m[j],m[c]]then dec(d[m[c]]);
end;
for i:=1 to k do write(n[i],' ');
writeln;
readln
end.
