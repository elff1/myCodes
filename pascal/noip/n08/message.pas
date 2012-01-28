program message3;
//uses math;
const maxn=51;name='message';
var
   g,d,f1,f2:array[0..maxn,0..maxn]of longint;
   i,j,n,m,ans:longint;
  function max(a,b:longint):longint;
  begin if a>b then exit(a);exit(b);end;
   procedure dp;
   var i,j,p,q,u:longint;
   begin
        fillchar(f1,sizeof(f1),0);
        for j:=1 to n do f1[1,j]:=d[1,j];
        for u:=2 to m do
        begin
             fillchar(f2,sizeof(f2),0);
             for i:=1 to n-1 do for j:=i+1 to n do
                 for p:=1 to i do for q:=i+1 to j do
                 f2[i,j]:=max(f2[i,j],f1[p,q]+d[u,i]-d[u,p-1]+d[u,j]-d[u,q-1]);
             f1:=f2;
             //writeln(u);for i:=1 to n do
             //begin for j:=1 to n do write(f2[i,j],' ');writeln;end;
        end;
   end;
   
begin
assign(input,name+'.in');reset(input);
assign(output,name+'.out');rewrite(output);
readln(m,n);
fillchar(d,sizeof(d),0);
for i:=1 to m do for j:=1 to n do
    begin read(g[i,j]);d[i,j]:=d[i,j-1]+g[i,j];end;
readln;
//for i:=1 to m do begin for j:=1 to n do write(d[i,j],' ');writeln;end;readln;end.
dp;
ans:=0;
for i:=1 to n do for j:=1 to n do ans:=max(ans,f1[i,j]);
writeln(ans);
//readln;
close(input);close(output);
end.
