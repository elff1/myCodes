`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:19:12 11/18/2010 
// Design Name: 
// Module Name:    display 
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
module display(
input wire clk, reset,
input wire [15:0] disp_num, // hex digits
input wire [3:0] dp_in, // 4 decimal points
output reg [3:0] an, // enable 1©\out©\of©\4 asserted low
output reg [7:0] sseg // led segments
);
	
	localparam N = 18; //refreshing rate around 800 Hz (50 MHz/2^16)
	reg [N-1:0] q_reg; // internal signal declaration
	wire [N-1:0] q_next;
	reg [3:0] hex_in;
	reg dp;
	
	//N©\bit counter
	always @(posedge clk, posedge reset)
		if (reset)
			q_reg <= 0;
		else
			q_reg <= q_next;
	assign q_next = q_reg + 1; // next©\state logic
	
	always @*
		case (q_reg[N-1:N-2])
		2'b00:
			begin
				an = 4'b1110;
				hex_in = disp_num[3:0];
				dp = dp_in[0];
			end
		2'b01:
			begin
				an = 4'b1101;
				hex_in = disp_num[7:4];
				dp = dp_in[1];
			end
		2'b10:
			begin
				an = 4'b1011;
				hex_in = disp_num[11:8];
				dp = dp_in[2];
			end
		default:
			begin
				an = 4'b0111;
				hex_in = disp_num[15:12];
				dp = dp_in[3];
			end
		endcase
	
	always @*
	begin
		case(hex_in)
		4'h0: sseg[6:0] = 7'b1000000;
		4'h1: sseg[6:0] = 7'b1111001;
		4'h2: sseg[6:0] = 7'b0100100;
		4'h3: sseg[6:0] = 7'b0110000;
		4'h4: sseg[6:0] = 7'b0011001;
		4'h5: sseg[6:0] = 7'b0010010;
		4'h6: sseg[6:0] = 7'b0000010;
		4'h7: sseg[6:0] = 7'b1111000;
		4'h8: sseg[6:0] = 7'b0000000;
		4'h9: sseg[6:0] = 7'b0010000;
		4'ha: sseg[6:0] = 7'b0001000;
		4'hb: sseg[6:0] = 7'b0000011;
		4'hc: sseg[6:0] = 7'b1000110;
		4'hd: sseg[6:0] = 7'b0100001;
		4'he: sseg[6:0] = 7'b0000110;
		default: sseg[6:0] = 7'b0001110;
		//4'hf
		endcase
		sseg[7] = dp;
	end
	
endmodule
