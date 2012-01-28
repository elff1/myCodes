`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    16:11:29 12/26/2010 
// Design Name: 
// Module Name:    data_input 
// Project Name:   8-to-16bit Unsigned Integer Divider
// Target Devices: Spartan-3 Board & Kits
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
module data_input(
   input CLK,
   input [1:0] DATA_SELECT, // 00 - dividend, 01 - divisor
	                         // 10 - quotient, 11 - remainder
   input [1:0] BIT_SELECT,  // 00 - dividend[3:0] or divisor[3:0]
	                         // 01 - dividend[7:4] or divisor[7:4]
									 // 10 - dividend[11:8]
									 // 11 - dividend[15:12]
	input INCREMENT,         // increment 1 each posedge
   input CLEAR,             // clear dividend and divisor
	input RESET,
   output reg [15:0] DIVIDEND,
   output reg [ 7:0] DIVISOR,
	output reg OPERR
   );
	
	initial begin
	   DIVIDEND[15:0] = 0;
		DIVISOR[7:0]  = 0;
		OPERR = 0;
	end

	always @(posedge CLK) begin
		casex({DATA_SELECT[1:0],BIT_SELECT[1:0]})
		   4'b00xx: OPERR = 1'b0;
		   4'b010x: OPERR = 1'b0;
			default: OPERR = 1'b1; //$display("Forbid to operate!")
		endcase
	end
	   
	always @(posedge INCREMENT) begin
		if(CLEAR || RESET) begin
		   DIVIDEND[15:0] = 16'h0000;
			DIVISOR[7:0]  = 8'h00;
		end else begin
			case({DATA_SELECT[1:0],BIT_SELECT[1:0]})
				4'b0000: begin DIVIDEND[ 3:0] = DIVIDEND[ 3:0] + 4'b0001; end
				4'b0001: begin DIVIDEND[ 7:4] = DIVIDEND[ 7:4] + 4'b0001; end
				4'b0010: begin DIVIDEND[11:8] = DIVIDEND[11:8] + 4'b0001; end
				4'b0011: begin DIVIDEND[15:12]= DIVIDEND[15:12]+ 4'b0001; end
				4'b0100: begin DIVISOR[3:0] = DIVISOR[3:0] + 4'b0001; end
				4'b0101: begin DIVISOR[7:4] = DIVISOR[7:4] + 4'b0001; end
				default: $display("Forbid to operate!");
			endcase
      end
	end

endmodule
