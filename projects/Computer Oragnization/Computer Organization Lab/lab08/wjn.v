module top(
input wire clk,
input wire [3:0] switch,
input wire btn_east_in,
output wire lcd_rs,
output wire lcd_rw,
output wire lcd_e,
output wire [3:0] lcd_d);
reg[6:0] addr;
reg[31:0] df, ds, dina;
reg[0:0] wea;
reg[1:0] f;
wire[31:0] douta;
reg[4:0] addra;
reg[15:0] dout;
reg[15:0] dwrt;
//pbdebounce m0(clk,btn_east_in,btn_east);
ram m1(addra, dina, clk, wea, douta);
display m2(clk,1'b0,dout,lcd_rs,lcd_rw,lcd_e,lcd_d);
initial begin
dina = 32'h00000000;
addra = 5'b00000;
dout = 16'h0000;
wea = 1'b0;
f = 2'b00;
dwrt = 16'hABCD;
end
always @(posedge clk)begin
wea = 1'b0;
addr = {3'b0,switch};
addra = addr[6:2];
case(f)
2'b00: begin
df = douta;
f = 2'b01;
end
2'b01: begin
addra = addra + 1;
ds = douta;
case(addr[1:0])
2'b00: dout = df[31:16];
2'b01: dout = df[23:8];
2'b10: dout = df[15:0];
2'b11: dout = {df[7:0],ds[31:24]};
endcase
if(btn_east_in)
	f = 2'b10;
	else
	f = 1'b00;
end
2'b10: begin 
case(addr[1:0])2'b00: begin
dina = {dwrt,df[15:0]};
addra = addra;
wea = 1;
f = 2'b00;
end
2'b01: begin
dina = {df[31:24],dwrt,df[7:0]};
addra = addra;
wea = 1;
f = 2'b00;
end
2'b10: begin
dina = {df[31:16],dwrt};
addra = addra;
wea = 1;
f = 2'b00;
end
2'b11: begin
dina = {df[31:8],dwrt[15:8]};
addra = addra;
wea = 1;
f = 2'b11;
end
endcase
end
2'b11: begin
addra = addra + 1;
dina = {dwrt[7:0],ds[23:0]};
wea = 1;
f = 2'b00;
end
endcase
end
endmodule