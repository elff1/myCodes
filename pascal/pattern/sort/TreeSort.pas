procedure print(k:integer);
begin
     if k=0 then exit;
     print(t[k].l);
     writeln(a[k]);
     print(t[k].r);
end;

procedure creaktree;
var
     i,k:integer;
begin
     for i:=2 to n do
     begin
          k:=1;
          repeat
               if small(a[i],a[k])then
                    if t[k].l=0 then begin t[k].l:=i;break;end 
                      else k:=t[k].l
               else
                    if t[k].r=0 then begin t[k].r:=i;break;end 
                      else k:=t[k].r;
          until false;
     end;
end;