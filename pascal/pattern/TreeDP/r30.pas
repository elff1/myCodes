type point=record
      l,r:integer;
      end;
var m,n,i,j,k:longint;
     w:array[1..1000] of longint;
     f:array[0..1000,0..100] of longint;
     s:array[0..1000] of point;
procedure init;
var a,b,c:longint;
begin
     readln(n,m);
     fillchar(s,sizeof(s),0);
     fillchar(f,sizeof(f),0);
     for i:=1 to n do read(w[i]);
     for i:=1 to n do
     begin
          readln(a,b);
          c:=s[a].l;
          if c=0 then s[a].l:=b
          else 
          begin
          while s[c].r<>0 do 
           c:=s[c].r;
          s[c].r:=b;
          end;
     end;
end;
function max(a,b:longint):longint;
begin
     if a>b then exit(a) else exit(b);
end;
procedure dp(k,p:longint);
var i,j:longint;
begin
     if (k=0) or (p=0) or (f[k,p]<>0) then exit;
     dp(s[k].r,p);
     f[k,p]:=f[s[k].r,p];
     for i:=0 to p-1 do 
     begin
          dp(s[k].r,i);
          dp(s[k].l,p-i-1);
          f[k,p]:=max(f[k,p],f[s[k].r,i]+f[s[k].l,p-i-1]+w[k]);
     end;
  

end;
begin
     init;
     dp(s[0].l,m);
     writeln(f[s[0].l,m]);
end.
