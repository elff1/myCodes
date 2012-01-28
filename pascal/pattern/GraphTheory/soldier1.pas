program soldier1;
type tp=0..26;
var a:array[tp,tp]of boolean;
    b:array[tp]of boolean;
    d,m,n:array[tp]of tp;
    x:array[tp]of string;
    s:set of tp;i,j,c,p,q,k,w:tp;

  procedure dfs(j:tp);
  var i:tp;
  begin
    w:=w+1;n[w]:=m[j];d[m[j]]:=26;
    for i:=1 to k do
     if(a[m[j],m[i]])then dec(d[m[i]]);
    for i:=1 to k do if d[m[i]]=0 then dfs(i);
  end;

begin
fillchar(a,sizeof(a),0);
fillchar(d,sizeof(d),0);
fillchar(n,sizeof(n),0);
s:=[];readln(c);
for i:=1 to c do
begin
 readln(p,q);
 s:=s+[p,q];
 a[p,q]:=true;
 inc(d[q]);
end;
k:=0;w:=0;
for i:=1 to 26 do if i in s then
 begin k:=k+1;m[k]:=i;b[i]:=false;end;
for i:=1 to k do if d[i]=0 then dfs(i);
for i:=1 to k do write(n[i],' ');
writeln;
readln
end.