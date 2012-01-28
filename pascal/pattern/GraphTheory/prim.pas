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
   {寻找离生成树最近的未加入顶点k}
      min:=maxlongint;
      for j:=1 to n do
         if (lowcost[j]<min) and (lowcost[j]<>0) then begin
            min:=lowcost[j];
            k:=j;
         end;
      lowcost[k]:=0; {将顶点k加入生成树}
      {生成树中增加一条新的边k到closest[k]}
      {修正各点的lowcost和closest值}
      for j:=1 to n do
         if cost[k,j]<lowcost[j] then begin
            lowcost[j]:=cost[k,j];
            closest[j]:=k;
         end;
   end;
end;{prim}