`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:51:50 04/15/2011 
// Design Name: 
// Module Name:    alu 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// revision: 
// revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module alu(
	input wire [31:0] A,
	input wire [31:0] B,
	input wire [2:0] ctl,
	output wire [31:0] result,
	output wire zero,
	output wire carryout,
	output wire overflow
	);
	
	wire slt, caryt, overf;
	wire[31:0] andr, orr, addr; 
	
   and32 and1(andr, A, B); 
   or32 or1(orr, A, B);
   add32 ad(A, B, ctl[2], ctl[2], addr, caryt, overf);
	mux32_4_1 mx4(result, ctl[1:0], andr, orr, addr, {31'h0,slt});

	xor(cyt, caryt, ctl[2]);
	xor(slt, overf, addr[31]); 
	and(carryout, ctl[1], ~ctl[0], cyt);
	and(overflow, ctl[1], ~ctl[0], overf);
	
	nor(zero, result[0], result[ 1], result[ 2], result[ 3],
		result[ 4], result[ 5], result[ 6], result[ 7],
		result[ 8], result[ 9], result[10], result[11],
		result[12], result[13], result[14], result[15],
		result[16], result[17], result[18], result[19],
		result[20], result[21], result[22], result[23],
		result[24], result[25], result[26], result[27],
		result[28], result[29], result[30], result[31]);
endmodule
