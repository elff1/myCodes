program n002;
var n,k,i:integer;
    s:string;m:qword;
    a:array[byte]of byte;

  function max(a,b:qword):qword;
  begin
    if a>b then exit(a) else exit(b);
  end;

  function js:qword;
  var i,c:integer;q:qword;
       b:array[byte]of qword;
  begin
    fillchar(b,sizeof(b),0);
    for i:=1 to k do val(copy(s,a[i-1]+1,a[i]-a[i-1]),b[i],c);
    val(copy(s,a[k]+1,n-a[k]),b[k+1],c);
    q:=1;
    for i:=1 to k+1 do q:=q*b[i];
    js:=q;
  end;

  procedure work(j,h:integer);
  var i:integer;
  begin
    if j=k+1 then begin m:=max(m,js);exit end;
    for i:=h to n-k+j-1 do
     begin a[j]:=i;work(j+1,i+1);end;
  end;

begin
readln(n,k);
readln(s);
m:=0;
fillchar(a,sizeof(a),0);
work(1,1);
writeln(m);
readln;
end.
