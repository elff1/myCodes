{单源最短路径的Bellman-ford算法执行v-1次，每次对每条边进行松弛操作
如有负权回路则输出"Error"}
 const  maxn=100;maxe=maxn*(maxn-1)div 2;
 type  edge=record a,b,w  :integer;end;
 var
  edges :array[1..maxe]of edge;
  dis   :array[1..maxn]of integer;
  pre   :array[1..maxn]of integer;
  e,n,s :integer;
  
 procedure init;
 var  i :integer;
 begin
   e:=0;
   assign(input,'g.in');reset(input);
   readln(n,s);
   while not eof do
   begin
      inc(e);
      with edges[e] do readln(a,b,w);
   end;
   fillchar(dis,sizeof(dis),$7f);//$7f是什么，解释替换
   dis[s]:=0;pre[s]:=s;
 end;
  
 procedure relax(u,v,w:integer);
 begin
   if dis[u]+w<dis[v] then
   begin
      dis[v]:=dis[u]+w;
      pre[v]:=u;
   end
 end;
 
 function bellman_ford:boolean;
 var  i,j:integer;
 begin
   for i:=1 to n-1 do for j:=1 to e do with edges[j] do relax(a,b,w);
   for i:=1 to e do with edges[i] do
       if dis[a]+w<dis[b] then exit(false);
   exit(true)
 end;
 
 procedure print_path(i:integer);
 begin
   if pre[i]<>s then print_path(pre[i]);
   write('-->',i)
 end;
 
 procedure show;
 var  i:integer;
 begin
   for i:=1 to n do
   begin
      write(i:3,':',dis[i]:3,':',s);
      print_path(i);
      writeln
   end;
 end;     {========main========}
begin
init;
if bellman_ford then show else writeln('Error!!')
end.