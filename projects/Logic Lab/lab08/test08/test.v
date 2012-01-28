`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:41:03 11/26/2010
// Design Name:   counter_4bit
// Module Name:   D:/elf/test.v
// Project Name:  elf
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: counter_4bit
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test;

	// Inputs
	reg clk = 1'b0, rst = 1'b0;

	// Outputs
	wire Qa;
	wire Qb;
	wire Qc;
	wire Qd;
	wire Rc;

	// Instantiate the Unit Under Test (UUT)
	counter_4bit INST(.clk(clk), .Qa(Qa), .Qb(Qb), .Qc(Qc), .Qd(Qd), .Rc(Rc));

	parameter PERIOD = 200;
	parameter real DUTY_CYCLE = 0.5;
	
	initial forever begin
		// Initialize Inputs
		clk = 1'b0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		#(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
		#(PERIOD*DUTY_CYCLE);
	end
      
endmodule

