const
	d:array[13..24]of longint=
	(1,2,8,9,6,9,29,39,38,65,88,128);
	name='matches';
var
	n:longint;
begin
assign(input,name+'.in');reset(input);
assign(output,name+'.out');rewrite(output);
readln(n);
if(n<=24)and(n>=13)then writeln(d[n])else writeln(0);
//readln;
close(input);close(output);
end.