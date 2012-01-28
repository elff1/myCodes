program all;{¸ß¾«¶È}
uses math;
const maxl=10000;maxll=4;maxw=100;
type tg=array[0..100]of longint;
var
   a,b:tg;
   
   procedure init;
   var s:string;
   begin
        fillchar(a,sizeof(a),0);
        fillchar(b,sizeof(b),0);
        readln(s);
        a[0]:=0;
        while length(s)>maxll do
        begin
             inc(a[0]);
             val(copy(s,length(s)-maxll+1,maxll),a[a[0]]);
             delete(s,length(s)-maxll+1,maxll);
        end;
        if s<>'' then begin inc(a[0]);val(s,a[a[0]]);end;
        readln(s);
        b[0]:=0;
        while length(s)>maxll do
        begin
             inc(b[0]);
             val(copy(s,length(s)-maxll+1,maxll),b[b[0]]);
             delete(s,length(s)-maxll+1,maxll);
        end;
        if s<>'' then begin inc(b[0]);val(s,b[b[0]]);end;
   end;
   
   function bigger(a,b:tg):boolean;
   var i:longint;
   begin
        if a[0]>b[0] then exit(true);
        if a[0]<b[0] then exit(false);
        for i:=a[0] downto 1 do
        begin
             if a[i]>b[i] then exit(true);
             if a[i]<b[i] then exit(false);
        end;
        exit(true);
   end;
   
   function sum(a,b:tg):tg;
   var i,l:longint;
   begin
        l:=max(a[0],b[0]);
        for i:=1 to l do
        begin
             inc(a[i],b[i]);
             inc(a[i+1],a[i]div maxl);
             a[i]:=a[i]mod maxl;
        end;
        if a[l+1]>0 then inc(l);
        a[0]:=l;
        exit(a);
   end;
   
   function minus(a,b:tg):tg;
   var i,l:longint;t:tg;
   begin
        if not bigger(a,b)then begin t:=a;a:=b;b:=t;end;
        l:=a[0];
        for i:=1 to l do
        begin
             if a[i]<b[i] then begin inc(a[i],maxl);dec(a[i+1]);end;
             dec(a[i],b[i]);
        end;
        while(l>1)and(a[l]=0)do dec(l);
        a[0]:=l;
        exit(a);
   end;
   
   function multiply1(a:tg;b:longint):tg;  {warning}
   var i:longint;c:tg;
   begin
        fillchar(c,sizeof(c),0);
        for i:=1 to a[0] do
        begin
             inc(c[i],a[i]*b);
             inc(c[i+1],c[i]div maxl);
             c[i]:=c[i]mod maxl;
        end;
        c[0]:=maxw;
        while c[c[0]]=0 do dec(c[0]);
        exit(c);
   end;
   
   function multiply2(a,b:tg):tg;         {warning}
   var i,j:longint;c:tg;
   begin
        fillchar(c,sizeof(c),0);
        for i:=1 to b[0] do for j:=1 to a[0] do
        begin
             inc(c[i+j-1],a[j]*b[i]);
             inc(c[i+j],c[i+j-1]div maxl);
             c[i+j-1]:=c[i+j-1]mod maxl;
        end;
        c[0]:=maxw;
        while c[c[0]]=0 do dec(c[0]);
        exit(c);
   end;
   
   function divide(a:tg;b:longint):tg;
   var i:longint;
   begin
        for i:=a[0] downto 2 do
        begin
             inc(a[i-1],a[i]mod b*maxl);
             a[i]:=a[i]div b;
        end;
        a[1]:=a[1]div b;        {warning}
        while(a[0]>1)and(a[a[0]]=0)do dec(a[0]);
        exit(a);
   end;
   
   procedure print(a:tg);
   var i,j:longint;s:string;
   begin
        write(a[a[0]]);
        for i:=a[0]-1 downto 1 do
        begin
             str(a[i],s);
             for j:=1 to maxll-length(s)do write(0);
             write(a[i]);
        end;
        writeln;
   end;
        
begin
init;
write('a:');print(a);
write('b:');print(b);
writeln(bigger(a,b));
write('a+b:');print(sum(a,b));
write('a-b:');print(minus(a,b));
write('a*200000:');print(multiply1(a,200000));
write('a*b:');print(multiply2(a,b));
write('a/7:');print(divide(a,7));
readln;
end.

