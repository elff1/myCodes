`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:48:14 05/04/2011 
// Design Name: 
// Module Name:    mem_wrt 
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
module mem_wrt(clk, btn_in, switch, anode, segment);
	input wire clk;
	input wire[3:0] btn_in;
	input wire[7:0] switch;
	output wire [3:0] anode; // enable 1-out-of-4 asserted low
	output wire [7:0] segment;
	
	reg[7:0] addr;
	reg[31:0] df, ds, dina;
	reg[0:0] wea;
	reg[1:0] f;
	wire[31:0] douta;
	reg[6:0] addra;
	reg[15:0] dout;
	reg[15:0] dwrt;
	
	memory m0(clk, dina, addra, wea, douta);
	display d0(clk, 0, dout, 4'b1111, anode, segment);
	
	initial begin
		dina = 32'h00000000;
		addra = 7'b0000000;
		dout = 16'h0000;
		wea = 1'b0;
		f = 2'b00;
		dwrt = 16'hABCD;
	end
	
	always @(posedge clk)begin
		wea = 1'b0;
		addr = switch;
		addra = addr >> 2;
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
				if(btn_in[0] || btn_in[1] || btn_in[2] || btn_in[3])
					f = 2'b10;
				else
					f = 2'b00;
			end
			2'b10: begin		
				case(addr[1:0])
					2'b00: begin
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
