//Floyd:All Pairs Shortest Paths;
const
  maxn=300;
var
  dis   :array[1..maxn,1..maxn]of integer;
  n     :integer;

procedure init;
var
  i,j   :integer;
begin
  assign(input,'g.in');reset(input);
  readln(n);
  for i:=1 to n do
    for j:=1 to n do
      begin
        read(dis[i,j]);
        if (dis[i,j]=0)and(i<>j)then dis[i,j]:=maxint;
      end;
end;

procedure main;
var
  i,j,k :integer;
begin
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        if (dis[i,j]>dis[i,k]+dis[k,j])then
          dis[i,j]:=dis[i,k]+dis[k,j];
end;

procedure print;
var
  i,j   :integer;
begin
  for i:=1 to n do
    begin
      for j:=1 to n do write(dis[i,j]:6);
      writeln
    end;
end;
{===========main===========}
begin
  init;
  main;
  print;
end.
