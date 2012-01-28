`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:01:30 04/15/2011 
// Design Name: 
// Module Name:    extend 
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
module extend(
   input wire [15:0] i_16,
   output wire [31:0] o_32
   );
	assign o_32 = {{16{i_16[15]}},i_16};
endmodule
