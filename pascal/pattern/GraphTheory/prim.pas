procedure prim(v0:integer);
 
var
   lowcost,closest:array[1..maxn] of integer;
   i,j,k,min:integer;
begin
   for i:=1 to n do begin
      lowcost[i]:=cost[v0,i];
      closest[i]:=v0;
   end;
   for i:=1 to n-1 do begin
   {Ѱ���������������δ���붥��k}
      min:=maxlongint;
      for j:=1 to n do
         if (lowcost[j]<min) and (lowcost[j]<>0) then begin
            min:=lowcost[j];
            k:=j;
         end;
      lowcost[k]:=0; {������k����������}
      {������������һ���µı�k��closest[k]}
      {���������lowcost��closestֵ}
      for j:=1 to n do
         if cost[k,j]<lowcost[j] then begin
            lowcost[j]:=cost[k,j];
            closest[j]:=k;
         end;
   end;
end;{prim}