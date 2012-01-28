`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:54:39 11/25/2010 
// Design Name: 
// Module Name:    test_wave 
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
module test_wave;
	reg clk = 1'b0, rst = 1'b0;
	wire Qa, Qb, Qc, Qd, Rc;
	
	parameter PERIOD = 200;
	parameter real DUTY_CYCLE = 0.5;
	initial forever begin
		clk = 1'b0;
		#(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
		#(PERIOD*DUTY_CYCLE);
	end
	counter_4bit INST(.clk(clk), .Qa(Qa), .Qb(Qb), .Qc(Qc), .Qd(Qd), .Rc(Rc));
endmodule
