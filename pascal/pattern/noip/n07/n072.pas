program n072;
var
        i,j,l,n,m,u,p1,p2,p3:longint;
        s,t:ansistring;

        function ok(k:longint):boolean;
        begin
        if(((s[k-1]<='Z')and(s[k-1]>='A')and(s[k+1]<='Z')and(s[k+1]>='A'))or
           ((s[k-1]<='z')and(s[k-1]>='a')and(s[k+1]<='z')and(s[k+1]>='a'))or
           ((s[k-1]<='9')and(s[k-1]>='0')and(s[k+1]<='9')and(s[k+1]>='0')))and
            (s[k-1]<s[k+1])then exit(true)else exit(false);
        end;

        procedure swap(var a,b:char);
        var m:char;
        begin
                m:=a;a:=b;b:=m;
        end;

        procedure add(c:char);
        var i:longint;
        begin
                for i:=1 to p2 do t:=t+c;
        end;

        procedure work(k:longint);
        var i,u,v,p,q:longint;
        begin
        u:=p2*(ord(s[k+1])-ord(s[k-1])-1);
        if u=0 then exit;
        if (s[k-1]<='Z')and(s[k-1]>='A') then p:=ord(s[k-1])-ord('A');
        if (s[k+1]<='Z')and(s[k+1]>='A') then q:=ord(s[k+1])-ord('A');
        if (s[k-1]<='z')and(s[k-1]>='a') then p:=ord(s[k-1])-ord('a');
        if (s[k+1]<='z')and(s[k+1]>='a') then q:=ord(s[k+1])-ord('a');
        case p1 of
                1:begin
                if(s[k-1]<='9')and(s[k-1]>='0')then
                  for i:=ord(s[k-1])+1 to ord(s[k+1])-1 do add(chr(i))
                else for i:=p+1 to q-1 do add(chr(i+ord('a')));
                end;
                2:begin
                if(s[k-1]<='9')and(s[k-1]>='0')then
                  for i:=ord(s[k-1])+1 to ord(s[k+1])-1 do add(chr(i))
                else for i:=p+1 to q-1 do add(chr(i+ord('A')));
                end;
                3:for i:=1 to u do t:=t+'*';
        end;
        if p3=2 then for i:=1 to u shr 1 do swap(t[j+i],t[j+u-i+1]);
        inc(j,u);
        end;

begin
readln(p1,p2,p3);
readln(s);l:=length(s);
i:=1;j:=1;t:=s[1];
repeat
        inc(i);
        if(i<l)and(s[i]='-')and ok(i) then work(i)
                else begin inc(j);t:=t+s[i];end;
until i>=l;
writeln(t);
readln;
end.

