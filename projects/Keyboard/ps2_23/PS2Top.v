`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:15:20 12/23/2011 
// Design Name: 
// Module Name:    PS2Top 
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

module PS2Top(clk, ps2Clk, ps2Data, reset, commond, dataReady, data);
input clk;
input ps2Clk;
input ps2Data;
input reset;
input [31:0] commond;
output dataReady;
output [31:0] data;

wire scanDone;						// the scanned flag
wire [7:0] scanCode;				// the scan code

wire dataReady;					// the data ready flag
wire [31:0] data;					// the decode data

PS2Ctrl pc(clk, reset, ps2Clk, ps2Data, scanDone, scanCode);
PS2Decode pd(clk, reset, scanDone, scanCode, dataReady, data);

endmodule
