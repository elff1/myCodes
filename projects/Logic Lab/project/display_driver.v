`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    18:41:52 12/26/2010 
// Design Name: 
// Module Name:    display_driver 
// Project Name:   8-to-16bit Unsigned Integer Divisor
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
module display_driver(
    input CLK,
    input [15:0] DIVIDEND,   // dividend 
    input [7:0] DIVISOR,     // divisor 
    input [7:0] QUOTIENT,    // quotient 
    input [7:0] REMAINDER,   // remainder 
    input DZ,                // divided by zero flag
    input DO,                // divider overflow flag
    input OPERR,             // operation input error
    input [1:0] DATA_SELECT, // 00 - dividend, 01 - divisor
	                          // 10 - quotient, 11 - remainder
    input [1:0] BIT_SELECT,  // 00 - dividend[3:0] or divisor[3:0] or quotient[3:0] or remainder[3:0]
	                          // 01 - dividend[7:4] or divisor[7:4] or quotient[7:4] or remainder[7:4]
									  // 10 - dividend[11:8]
									  // 11 - dividend[15:12]
    output reg [19:0] SEG7DATA,
    output reg [3:0] SEG7BLINK,
    output reg [2:0] LEDLAMP
    );
	 
	 initial begin
	    SEG7DATA[19:0] = 20'h0;
		 SEG7BLINK[3:0] = 4'b0000;
		 LEDLAMP[2:0] = 3'b000;
	 end

    always @(posedge CLK) begin
	    case({DATA_SELECT[1:0],BIT_SELECT[1:0]})
          4'b0000: begin SEG7DATA[4:0] <= DIVIDEND[3:0]; SEG7DATA[9:5] <= DIVIDEND[7:4]; 
			                SEG7DATA[14:10] <= DIVIDEND[11:8]; SEG7DATA[19:15] <= DIVIDEND[15:12]; 
			                SEG7BLINK[3:0] = 4'b0001; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0001: begin SEG7DATA[4:0] <= DIVIDEND[3:0]; SEG7DATA[9:5] <= DIVIDEND[7:4]; 
			                SEG7DATA[14:10] <= DIVIDEND[11:8]; SEG7DATA[19:15] <= DIVIDEND[15:12]; 
			                SEG7BLINK[3:0] = 4'b0010; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0010: begin SEG7DATA[4:0] <= DIVIDEND[3:0]; SEG7DATA[9:5] <= DIVIDEND[7:4]; 
			                SEG7DATA[14:10] <= DIVIDEND[11:8]; SEG7DATA[19:15] <= DIVIDEND[15:12]; 
			                SEG7BLINK[3:0] = 4'b0100; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0011: begin SEG7DATA[4:0] <= DIVIDEND[3:0]; SEG7DATA[9:5] <= DIVIDEND[7:4]; 
			                SEG7DATA[14:10] <= DIVIDEND[11:8]; SEG7DATA[19:15] <= DIVIDEND[15:12]; 
			                SEG7BLINK[3:0] = 4'b1000; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          
			 4'b0100: begin SEG7DATA[4:0] <= DIVISOR[3:0]; SEG7DATA[9:5] <= DIVISOR[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0001; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0101: begin SEG7DATA[4:0] <= DIVISOR[3:0]; SEG7DATA[9:5] <= DIVISOR[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0010; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0110: begin SEG7DATA[4:0] <= DIVISOR[3:0]; SEG7DATA[9:5] <= DIVISOR[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          4'b0111: begin SEG7DATA[4:0] <= DIVISOR[3:0]; SEG7DATA[9:5] <= DIVISOR[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {1'b0, 1'b0, OPERR}; end
          
			 4'b1000: begin SEG7DATA[4:0] <= QUOTIENT[3:0]; SEG7DATA[9:5] <= QUOTIENT[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1001: begin SEG7DATA[4:0] <= QUOTIENT[3:0]; SEG7DATA[9:5] <= QUOTIENT[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1010: begin SEG7DATA[4:0] <= QUOTIENT[3:0]; SEG7DATA[9:5] <= QUOTIENT[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1011: begin SEG7DATA[4:0] <= QUOTIENT[3:0]; SEG7DATA[9:5] <= QUOTIENT[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          
			 4'b1100: begin SEG7DATA[4:0] <= REMAINDER[3:0]; SEG7DATA[9:5] <= REMAINDER[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1101: begin SEG7DATA[4:0] <= REMAINDER[3:0]; SEG7DATA[9:5] <= REMAINDER[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1110: begin SEG7DATA[4:0] <= REMAINDER[3:0]; SEG7DATA[9:5] <= REMAINDER[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          4'b1111: begin SEG7DATA[4:0] <= REMAINDER[3:0]; SEG7DATA[9:5] <= REMAINDER[7:4]; 
			                SEG7DATA[14:10] <= 5'b10001; SEG7DATA[19:15] <= 5'b10001; 
			                SEG7BLINK[3:0] = 4'b0000; LEDLAMP[2:0] = {  DO,   DZ, OPERR}; end
          
			 default: $display("Invalid operation input!");	 
		 endcase
	 end
endmodule
