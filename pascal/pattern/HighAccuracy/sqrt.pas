type
    num=record
        l:longint;
        w:array[0..300]of longint;
    end;

function max(a,b:longint):longint;begin if a>b then exit(a)else exit(b);end;

procedure zl(var a:num);
    var i:longint;
    begin
        i:=1;
        while(a.w[i]>0)or(i<=a.l)do begin
            inc(a.w[i+1],a.w[i]div 10);
            a.w[i]:=a.w[i]mod 10;
            inc(i);
        end;
        dec(i);
        if i=0 then i:=1;
        a.l:=i;
    end;

procedure setn(w:longint;var s:num);
    begin
        s.w[1]:=w;
        s.l:=1;
        zl(s);
    end;

procedure jia(a:num;var b:num);
    var i,l:longint;
    begin
        l:=max(a.l,b.l);
        for i:=1 to l do inc(b.w[i],a.w[i]);
        zl(b);
    end;

procedure cy(t:longint;var a:num);
    var i:longint;
    begin
        for i:=1 to a.l do a.w[i]:=a.w[i]*t;
        zl(a);
    end;

procedure pr(a:num);
    var i:longint;
    begin
        for i:=a.l downto 1 do write(a.w[i]);
        writeln;
    end;

procedure cyy(b:num;var a:num);
    var
        i,j:longint;
        t,tt,s:num;
    begin
        for i:=0 to 300 do s.w[i]:=0;s.l:=1;
        for i:=1 to a.l do begin
            t:=b;
            cy(a.w[i],t);
            for j:=t.l downto 1 do t.w[j+i-1]:=t.w[j];
            for j:=i-1 downto 1 do t.w[j]:=0;
            inc(t.l,i-1);
            jia(t,s);
        end;
        s.l:=b.l+a.l-1;
        zl(s);
        a:=s;
    end;

procedure putin(var a:num);
    var k:string;i:longint;
    begin
        read(k);readln;
        a.l:=length(k);
        for i:=a.l downto 1 do
            a.w[i]:=ord(k[a.l-i+1])-48;
    end;

procedure pj(a,b:num;var c:num);
    var i:longint;
    begin
        c:=a;
        jia(b,c);
        for i:=c.l downto 1 do begin
            if odd(c.w[i])then inc(c.w[i-1],10);
            c.w[i]:=c.w[i] shr 1;
        end;
        c.w[0]:=0;
        if c.w[c.l]=0 then dec(c.l);
    end;

function small(a,b:num):boolean;
    var l:longint;
    begin
        if a.l>b.l then exit(false);
        if a.l<b.l then exit(true);
        l:=a.l;
        while(l>0)and(a.w[l]=b.w[l])do dec(l);
        if l=0 then exit(true);
        exit(a.w[l]<=b.w[l]);
    end;

procedure sqrt(b:num;var a:num);
    var
        i,l:longint;
        p,q,r,an,t,pp:num;f1,f2:boolean;
    begin
        l:=(b.l+1)shr 1;
        p.l:=l;
        q.l:=l;
        for i:=0 to 300 do begin p.w[i]:=0;q.w[i]:=0;end;
        for i:=1 to l do q.w[i]:=9;
        p.w[l]:=1;
        r:=q;
        cyy(r,r);
        if small(r,b)then begin a:=q;exit;end;
        t:=p;
        while true do begin
            pj(p,q,r);
            t:=r;
            cyy(r,r);
            f1:=small(r,b);
            if f1 then begin
                p:=t;
                jia(one,t);
                cyy(t,t);
                f2:=small(t,b);
                if f1 and not f2 then begin a:=p;exit;end;
            end else q:=t;
        end;
    end;