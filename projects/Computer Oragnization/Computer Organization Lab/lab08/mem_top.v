`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:30:28 04/27/2011 
// Design Name: 
// Module Name:    mem_top 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module mem_top(clk, switch, anode, segment);
	input wire clk;
	input wire[7:0] switch;
	output wire [3:0] anode; // enable 1-out-of-4 asserted low
	output wire [7:0] segment;
	
	reg[7:0] addr;
	reg[31:0] df, ds, dina;
	reg[0:0] wea;
	reg[0:0] f;
	wire[31:0] douta;
	reg[6:0] addra;
	reg[15:0] dout;
	
	memory m0(clk, dina, addra, wea, douta);
	display d0(clk, 0, dout, 4'b1111, anode, segment);
	
	initial begin
		dina = 32'h00000000;
		addra = 7'b0000000;
		dout = 16'h0000;
		wea = 1'b0;
		f = 1'b0;
	end
	
	always @(posedge clk)begin
		addr = switch;
		addra = addr >> 2;
		if(!f)begin
			df = douta;
			f = 1'b1;
		end
		else begin
			addra = addra + 1;
			ds = douta;
			case(addr[1:0])
				2'b00: dout = df[31:16];
				2'b01: dout = df[23:8];
				2'b10: dout = df[15:0];
				2'b11: dout = {df[7:0],ds[31:24]};
			endcase
			f = 1'b0;
		end
		//dout = df[15:0];
	end
endmodule
