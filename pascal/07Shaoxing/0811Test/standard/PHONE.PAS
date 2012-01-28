program phone(input,output);
const  table:array['a'..'z']of longint
=(1,1,1,2,2,2,3,3,3,4,4,4,5,5,6,6,6,7,7,7,8,8,8,9,9,9);
var   voca:array[1..100]of string;
pass:string;
i,j,k,l,m,n:longint;
data:array[1..100,1..100]of longint;

procedure print(be,en:longint);
  var  i:longint;
  begin
    if data[be,en]>10000 then  begin 
                                 if be>1 then write(' ' );
                                 write(voca[data[be,en]-10000]);
                               end
                         else  begin
                                 print(be,data[be,en]);
                                 print(data[be,en]+1,en);
                               end;
  end;

function pei(s:string;be,en:longint):boolean; 
  var   i:longint;
  begin
    for i:=be to en do
      begin
        if pass[i]<>char(table[s[i-be+1]]+48) then exit(false);
      end;
    pei:=true;
  end;

procedure qiu(be,en:longint);
  var  i:longint;
  begin
    for i:=1 to n do                     
      if length(voca[i])=en-be+1 then
        begin
          if pei(voca[i],be,en) then
            begin
              data[be,en]:=10000+i;
              exit;
            end;
        end;
    for i:=be to en-1 do    
      begin
        if data[be,i]=0 then qiu(be,i);
        if data[i+1,en]=0 then qiu(i+1,en);
        if (data[be,i]=-1)or(data[i+1,en]=-1) then continue else
          begin
            data[be,en]:=i;
            exit;
          end;
      end;
    data[be,en]:=-1;   
  end;

begin   {main}
  assign(input,'phone.in');
  assign(output,'phone.out');
  reset(input);rewrite(output);
  readln(n);   
  readln(pass); 
  for i:=1 to n do 
    readln(voca[i]);
  qiu(1,length(pass)); 
  if data[1,length(pass)]=-1 then  
    begin
      writeln('No Solutions!');
      close(output);halt;
    end;
  print(1,length(pass));  
  close(output);
end.
