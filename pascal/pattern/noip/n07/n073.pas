program n013;
const maxn=80;
type node=array[0..15]of longint;
var
        n,m,i,j,x:longint;
        s:node;
        d:array[1..maxn]of longint;
        f:array[1..maxn,1..maxn]of node;

        function add(a:node;b:longint):node;
        begin
                inc(a[1],b);exit(a);
        end;

        function sum(a,b:node):node;
        var i,j:longint;
        begin
                i:=0;j:=0;
                repeat
                        inc(i);inc(j);
                        inc(a[i],b[i]);
                        inc(a[i+1],a[i] div 10000);
                        a[i]:=a[i] mod 10000;
                until (i>=a[0])and(j>=b[0]);
                if a[i+1]>0 then
                  begin inc(i);a[i+1]:=a[i] div 10000;a[i]:=a[i] mod 10000;end;
                a[0]:=i;
                exit(a);
        end;

        function max(a,b:node):node;
        var i:longint;
        begin
                if a[0]>b[0] then exit(a)else if a[0]<b[0] then exit(b);
                i:=a[0]+1;
                repeat
                        dec(i);
                        if a[i]>b[i] then exit(a)else if a[i]<b[i]then exit(b);
                until i=1;
                exit(a);
        end;

        function work:node;
        var
                i,j,l:longint;
        begin
                fillchar(f,sizeof(f),0);
                for i:=1 to m do begin f[i,i,0]:=1;f[i,i,1]:=d[i];end;
                for l:=2 to m do for i:=1 to m-l+1 do
                begin
                        j:=i+l-1;
                        f[i,j]:=max(sum(f[i,j-1],add(f[i,j-1],d[j])),
                                    sum(f[i+1,j],add(f[i+1,j],d[i])));
                end;
                exit(f[1,m]);
        end;

        procedure print(a:node);
        var i:longint;s:string;
        begin
                write(a[a[0]]);
                for i:=a[0]-1 downto 1 do
                begin
                        str(a[i],s);
                        for j:=1 to 4-length(s) do write(0);
                        write(a[i]);
                end;
                writeln;
        end;

begin
readln(n,m);
fillchar(s,sizeof(s),0);
for i:=1 to n do
begin
        for j:=1 to m do begin read(x);d[j]:=x+x;end;readln;
        s:=sum(s,work);
end;
print(s);
readln;
end.
