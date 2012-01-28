//这是我的程序，要具体了解kmp，matrix67神牛的
  blog：http://www.matrix67.com/blog/archives/115
var s,t:string;
    i,j,ls,lt:integer;
    next:array[0..1000] of integer;
procedure init;
begin
  //  assign(input,'kmp.in');    reset(input);
  //  assign(output,'kmp.out');rewrite(output);
    readln(s);readln(t);
    ls:=length(s);lt:=length(t);
end;
procedure  makenext;
begin
    fillchar(next,sizeof(next),0);
    i:=1;j:=0;
    while i<=lt do
        if (j=0) or (t[i]=t[j]) then
        begin
            inc(i);
            inc(j);
            next[i]:=j;
        end
        else j:=next[j];
end;
procedure work;
begin
    i:=1;j:=1;
    while (i<=ls) and (j<=lt) do
    begin
        if (j=0)or (s[i]=t[j]) then
        begin
            inc(i);inc(j);
        end
        else
            j:=next[j];
    end;
    if j>lt then writeln(i-j+1) else writeln('no found');
end;
begin
    init;
    makenext;
    for i:=1 to lt do write(next[i],' ');
    work;
end.