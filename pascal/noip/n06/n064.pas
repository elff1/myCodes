program n064;
const maxm=3334;maxe=512;d=10000000;
type node=array[0..30]of longint;
var
   k,w,i,j,h,m,e:longint;
   f:array[0..maxe,0..maxe]of node;
   ans:node;
   
   function one:node;
   begin
        fillchar(one,sizeof(one),0);
        one[0]:=1;one[1]:=1;
   end;
   
   function sum(a,b:node):node;
   var i,l:longint;
   begin
        if a[0]>b[0]then l:=a[0]else l:=b[0];
        for i:=1 to l do
        begin
             a[i]:=a[i]+b[i];
             a[i+1]:=a[i+1]+a[i] div d;
             a[i]:=a[i]mod d;
        end;
        if a[l+1]>0 then inc(l);
        a[0]:=l;
        exit(a);
   end;
   
   procedure print(a:node);
   var i:longint;s:string;
   begin
        write(a[a[0]]);
        for i:=a[0]-1 downto 1 do
        begin
             str(a[i],s);
             for j:=1 to 7-length(s) do write(0);
             write(a[i]);
        end;
        writeln;
   end;
   
begin
readln(k,w);
m:=(w-1)div k+1;h:=(w-1)mod k+1;
h:=1 shl h-1;e:=1 shl k-1;
if m>e then begin m:=e;h:=1;end;
if h>e-m+1 then h:=e-m+1;
fillchar(f,sizeof(f),0);
for i:=1 to m do f[i,e-i+1]:=one;
for i:=1 to e do f[1,i]:=one;
for i:=2 to m do for j:=e-i downto 0 do f[i,j]:=sum(f[i,j+1],f[i-1,j+1]);
ans:=f[m,h];
for i:=1 to h-1 do ans:=sum(ans,f[m,i]);
for i:=3 to m do ans:=sum(ans,f[i,0]);
print(ans);
for i:=1 to m do begin for j:=1 to e-i+1 do print(f[i,j]);writeln;end;
readln;
end.