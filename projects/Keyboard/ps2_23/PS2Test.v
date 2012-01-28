`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:24:43 01/14/2012 
// Design Name: 
// Module Name:    PS2Test 
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
module PS2Test(clk, ps2Clk, ps2Data, reset, led);
input clk;
input ps2Clk;
input ps2Data;
input reset;
output [7:0] led;

wire dataReady;
wire [31:0] data;

wire [31:0] commond;
reg [7:0] displayData;			// the data display by LED

initial begin
	displayData <= 8'b0000_0000;
end

PS2Top pt(clk, ps2Clk, ps2Data, reset, commond, dataReady, data);

DisplayData dd(displayData, led);

always @(posedge dataReady) begin
	displayData <= data[7:0];
end

endmodule
