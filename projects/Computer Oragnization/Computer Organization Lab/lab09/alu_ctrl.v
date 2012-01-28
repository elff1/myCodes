`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:31:39 04/15/2011 
// Design Name: 
// Module Name:    alu_ctrl 
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
module alu_ctl(
	input wire [1:0] aluop,
	input wire [5:0] func,
	output wire[2:0] ctl
	);
	or (t1, func[0], func[3]);
	and(t2, func[1], aluop[1]);
	or (ctl[2], t2, aluop[0]);
	or (ctl[1], ~func[2], ~aluop[1]);
	and(ctl[0], t1, aluop[1]);
endmodule
