`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:30:46 12/24/2011 
// Design Name: 
// Module Name:    PS2Decode 
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
module PS2Decode(clk, reset, scanDone, scanCode, dataReady, data);

input clk;
input reset;
input scanDone;
input [7:0] scanCode;
output dataReady;
output [31:0] data;

reg preScan;
reg dataReady;
reg [31:0] data;

reg capsLock;						// the caps lock
reg shift;							// shift case flag
reg breakCode;						// break code flag

wire upper;							// the upper-case flag

assign upper = capsLock ^ shift;

initial begin
	preScan <= 1'b0;
	dataReady <= 1'b0;
	data <= 32'h0000_0000;
	
	capsLock <= 1'b0;
	shift <= 1'b0;
	breakCode <= 1'b0;
end

always @(posedge clk or posedge reset) begin
	preScan <= scanDone;
	if(reset)
		preScan <= 0;
end

always @(posedge clk or posedge reset) begin
	if(reset == 1) begin
		dataReady <= 1'b0;
		data <= 32'h0000_0000;
		
		breakCode <= 1'b0;
		shift <= 1'b0;
	end
	
	// pull down the dataReady signal
	else if(scanDone == 1'b0)
		dataReady <= 1'b0;
	
	// get a new scan code
	else if(preScan == 1'b0 && scanDone == 1'b1)
	// break code
	if(breakCode) begin
		// get the second scan code of a break code
		if((scanCode == 8'h12) || (scanCode == 8'h59)) begin
			shift <= 1'b0;
		end
		breakCode <= 1'b0;
	end
	// get the first scan code of a break code
	else if(scanCode == 8'hF0)
		breakCode <= 1'b1;
		
	// make code
	else
	begin
		case (scanCode)
			// control characters
			8'h12, 8'h59: begin								// shift
				data <= 32'h0000_0000;
				shift <= 1'b1;
			end
			8'h58: begin										// caps lock
				data <= 32'h0000_0000;
				capsLock <= ~capsLock;
			end
			8'h66:												// Backspace
				data <= 32'h0000_0008;
			8'h0D:												// Tab
				data <= 32'h0000_0009;
			8'h5A:												// Enter
				data <= 32'h0000_000A;
			8'h76:												// Escape
				data <= 32'h0000_001B;
				
			// printable characters
			8'h1C:												// the A character
				data <= (upper == 1'b1) ? 32'h0000_0041 : 32'h0000_0061;
			8'h32:												// the B character
				data <= (upper == 1'b1) ? 32'h0000_0042 : 32'h0000_0062;
			8'h21:												// the C character
				data <= (upper == 1'b1) ? 32'h0000_0043 : 32'h0000_0063;
			8'h23:												// the D character
				data <= (upper == 1'b1) ? 32'h0000_0044 : 32'h0000_0064;
			8'h24:												// the E character
				data <= (upper == 1'b1) ? 32'h0000_0045 : 32'h0000_0065;
			8'h2B:												// the F character
				data <= (upper == 1'b1) ? 32'h0000_0046 : 32'h0000_0066;
			8'h34:												// the G character
				data <= (upper == 1'b1) ? 32'h0000_0047 : 32'h0000_0067;
			8'h33:												// the H character
				data <= (upper == 1'b1) ? 32'h0000_0048 : 32'h0000_0068;
			8'h43:												// the I character
				data <= (upper == 1'b1) ? 32'h0000_0049 : 32'h0000_0069;
			8'h3B:												// the J character
				data <= (upper == 1'b1) ? 32'h0000_004A : 32'h0000_006A;
			8'h42:												// the K character
				data <= (upper == 1'b1) ? 32'h0000_004B : 32'h0000_006B;
			8'h4B:												// the L character
				data <= (upper == 1'b1) ? 32'h0000_004C : 32'h0000_006C;
			8'h3A:												// the M character
				data <= (upper == 1'b1) ? 32'h0000_004D : 32'h0000_006D;
			8'h31:												// the N character
				data <= (upper == 1'b1) ? 32'h0000_004E : 32'h0000_006E;
			8'h44:												// the O character
				data <= (upper == 1'b1) ? 32'h0000_004F : 32'h0000_006F;
			8'h4D:												// the P character
				data <= (upper == 1'b1) ? 32'h0000_0050 : 32'h0000_0070;
			8'h15:												// the Q character
				data <= (upper == 1'b1) ? 32'h0000_0051 : 32'h0000_0071;
			8'h2D:												// the R character
				data <= (upper == 1'b1) ? 32'h0000_0052 : 32'h0000_0072;
			8'h1B:												// the S character
				data <= (upper == 1'b1) ? 32'h0000_0053 : 32'h0000_0073;
			8'h2C:												// the T character
				data <= (upper == 1'b1) ? 32'h0000_0054 : 32'h0000_0074;
			8'h3C:												// the U character
				data <= (upper == 1'b1) ? 32'h0000_0055 : 32'h0000_0075;
			8'h2A:												// the V character
				data <= (upper == 1'b1) ? 32'h0000_0056 : 32'h0000_0076;
			8'h1D:												// the W character
				data <= (upper == 1'b1) ? 32'h0000_0057 : 32'h0000_0077;
			8'h22:												// the X character
				data <= (upper == 1'b1) ? 32'h0000_0058 : 32'h0000_0078;
			8'h35:												// the Y character
				data <= (upper == 1'b1) ? 32'h0000_0059 : 32'h0000_0079;
			8'h1A:												// the Z character
				data <= (upper == 1'b1) ? 32'h0000_005A : 32'h0000_007A;
				
			8'h45:												// the 0 or ) character
				data <= (shift == 1'b0) ? 32'h0000_0030 : 32'h0000_0029;
			8'h16:												// the 1 or ! character
				data <= (shift == 1'b0) ? 32'h0000_0031 : 32'h0000_0021;
			8'h1E:												// the 2 or @ character
				data <= (shift == 1'b0) ? 32'h0000_0032 : 32'h0000_0040;
			8'h26:												// the 3 or # character
				data <= (shift == 1'b0) ? 32'h0000_0033 : 32'h0000_0023;
			8'h25:												// the 4 or $ character
				data <= (shift == 1'b0) ? 32'h0000_0034 : 32'h0000_0024;
			8'h2E:												// the 5 or % character
				data <= (shift == 1'b0) ? 32'h0000_0035 : 32'h0000_0025;
			8'h36:												// the 6 or ^ character
				data <= (shift == 1'b0) ? 32'h0000_0036 : 32'h0000_005E;
			8'h3D:												// the 7 or & character
				data <= (shift == 1'b0) ? 32'h0000_0037 : 32'h0000_0026;
			8'h3E:												// the 8 or * character
				data <= (shift == 1'b0) ? 32'h0000_0038 : 32'h0000_002A;
			8'h46:												// the 9 or ( character
				data <= (shift == 1'b0) ? 32'h0000_0039 : 32'h0000_0028;
				
			8'h0E:												// the ` or ~ character
				data <= (shift == 1'b0) ? 32'h0000_0060 : 32'h0000_0021;
			8'h4E:												// the - or _ character
				data <= (shift == 1'b0) ? 32'h0000_002D : 32'h0000_005F;
			8'h55:												// the = or + character
				data <= (shift == 1'b0) ? 32'h0000_003D : 32'h0000_002B;
			8'h5D:												// the \ or | character
				data <= (shift == 1'b0) ? 32'h0000_005C : 32'h0000_007C;
			8'h54:												// the [ or { character
				data <= (shift == 1'b0) ? 32'h0000_005B : 32'h0000_007B;
			8'h5B:												// the ] or } character
				data <= (shift == 1'b0) ? 32'h0000_005D : 32'h0000_007D;
			8'h4C:												// the ; or : character
				data <= (shift == 1'b0) ? 32'h0000_003B : 32'h0000_003A;
			8'h52:												// the ' or " character
				data <= (shift == 1'b0) ? 32'h0000_0027 : 32'h0000_0022;
			8'h41:												// the , or < character
				data <= (shift == 1'b0) ? 32'h0000_002C : 32'h0000_003C;
			8'h49:												// the . or > character
				data <= (shift == 1'b0) ? 32'h0000_002E : 32'h0000_003E;
			8'h4A:												// the / or ? character
				data <= (shift == 1'b0) ? 32'h0000_002F : 32'h0000_003F;
			
			8'h29:												// the space character
				data <= 32'h0000_0020;
			
			default:
				data <= 32'h0000_0000;
		endcase
		
		dataReady <= 1'b1;
	end
end

endmodule
