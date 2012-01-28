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
		dout = 16'h0000;
		f = 2'b00;
		wea = 1'b0;
		addra = switch >> 2;
		dwrt = 16'hABCD;
	end
	
	always @(posedge clk)begin
		addr = switch;
		case(f)
			2'b00: begin
				df = douta;
				f = 2'b01;
				wea = 1'b0;
				addra = (addr >> 2) + 1;		// the address of the next time
			end
			2'b01: begin
				ds = douta;
				case(addr[1:0])
					2'b00: dout = df[31:16];
					2'b01: dout = df[23:8];
					2'b10: dout = df[15:0];
					2'b11: dout = {df[7:0],ds[31:24]};
				endcase
				if(btn_in[0] || btn_in[1] || btn_in[2] || btn_in[3]) begin
					f = 2'b10;
					wea = 1;
					case(addr[1:0])
						2'b00: begin
							dina = {dwrt,df[15:0]};
						end
						2'b01: begin
							dina = {df[31:24],dwrt,df[7:0]};
						end
						2'b10: begin
							dina = {df[31:16],dwrt};
						end
						2'b11: begin
							dina = {df[31:8],dwrt[15:8]};
						end
					endcase
				end
				else begin
					f = 2'b00;
					wea = 1'b0;
				end
				addra = addr >> 2;		// the address of the next time
			end
			2'b10: begin
				if(addr[1:0] == 2'b11)begin
					f = 2'b11;
					wea = 1'b1;
					addra = (addr >> 2) + 1;	// the address of the next time
					dina = {dwrt[7:0],ds[23:0]};
				end
				else begin
					f = 2'b00;
					wea = 1'b0;
					addra = addr >> 2;		// the address of the next time
				end
			end
			2'b11: begin
				f = 2'b00;
				wea = 0;
				addra = addr >> 2;		// the address of the next time
			end
		endcase
	end
endmodule
