`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:49:32 12/24/2011 
// Design Name: 
// Module Name:    PS2Ctrl 
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
module PS2Ctrl(clk, reset, ps2Clk, ps2Data, scanDone, scanCode);

input clk;
input reset;
input ps2Clk;
input ps2Data;
output scanDone;
output [7:0] scanCode;

reg scanDone;				// get a scan code flag
reg [7:0] scanCode;		// the scan code

reg [2:0] clkLowFilter;
reg [2:0] clkHighFilter;
reg filterPS2Clk;			// the filtered PS2 clock
reg prePS2Clk;

reg [3:0] bitCount;		// the buffer length
reg [9:0] buffer;			// the data buffer

initial begin
	clkLowFilter <= 3'b000;
	clkHighFilter <= 3'b000;
	filterPS2Clk <= 1'b0;
	prePS2Clk <= 1'b0;
	
	bitCount <= 4'b0000;
	buffer <= 10'b00_0000_0000;
	
	scanDone <= 1'b0;
	scanCode <= 8'b0000_0000;
end

// Get the filter PS2 clock
always @(posedge clk or posedge reset) begin
	if(reset) begin
		clkLowFilter <= 3'b000;
		clkHighFilter <= 3'b000;
		filterPS2Clk <= 1'b0;
		prePS2Clk <= 1'b0;
	end
	else begin
		prePS2Clk <= filterPS2Clk;
		if(ps2Clk) begin
			clkLowFilter <= 3'b000;
			clkHighFilter <= clkHighFilter + 3'b001;
			if(clkHighFilter == 3'b011)
				filterPS2Clk <= 1'b1;
		end
		else if(!ps2Clk) begin
			clkHighFilter <= 3'b000;
			clkLowFilter <= clkLowFilter + 3'b001;
			if(clkLowFilter == 3'b011)
				filterPS2Clk <= 1'b0;
		end
	end
end

// scan the code
always @(posedge clk or posedge reset) begin
	if(reset) begin
		bitCount <= 4'b0000;
		buffer <= 10'b00_0000_0000;
	end
	else if(prePS2Clk == 1'b1 && filterPS2Clk == 1'b0)
	if(bitCount == 4'b0000) begin
		if(!ps2Data)
			bitCount <= 4'b0001;
	end
	else begin
		bitCount <= bitCount + 4'b0001;
		buffer <= {ps2Data, buffer[8:1]};
		
		if(bitCount == 4'b1001) begin
			// Get a scan code successfully
			scanDone <= 1'b1;
			scanCode <= buffer[8:1];
		end
		else if(bitCount == 4'b1010) begin
			// reset the scan state
			scanDone <= 1'b0;
			scanCode <= 8'b0000_0000;
			
			bitCount <= 4'b0000;
		end
	end
end

endmodule
