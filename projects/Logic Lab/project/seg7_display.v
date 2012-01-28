`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    20:13:10 12/26/2010 
// Design Name: 
// Module Name:    seg7_display 
// Project Name:   8-to-16bit Unsigned Integer Divider
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
module seg7_display(
    input CLK,
    input CLK_1ms,
	 input CLK_500ms,
	 input [19:0] SEG7DATA,
    input [3:0] SEG7BLINK,
	 output reg [3:0] O_DIGIT_ANODE,
	 output reg [7:0] O_SEGMENT
    );

    reg [4:0] code = 5'b00000;
	 reg [3:0] cnt4 = 0;
	 
	 initial begin
	    O_DIGIT_ANODE = 0;
		 O_SEGMENT = 8'b00000000;
	 end
	 
    always @(posedge CLK_1ms) begin
       if (cnt4 <= 3) begin
		    O_DIGIT_ANODE <= {3'b111, (SEG7BLINK[0] & CLK_500ms)};
		    code <= SEG7DATA[4:0];
		 end else if(cnt4 <= 7) begin
		    O_DIGIT_ANODE <= {3'b11, (SEG7BLINK[1] & CLK_500ms), 1'b1};
		    code <= SEG7DATA[9:5];
		 end else if(cnt4 <= 11) begin
		    O_DIGIT_ANODE <= {3'b1, (SEG7BLINK[2] & CLK_500ms), 2'b11};
		    code <= SEG7DATA[14:10];
		 end else if(cnt4 <= 15) begin
		    O_DIGIT_ANODE <= {(SEG7BLINK[3] & CLK_500ms),3'b111};
		    code <= SEG7DATA[19:15];
		 end
		 cnt4 <= cnt4 + 1;
    end  
	 
	 always @(posedge CLK) begin
       case(code)
		    5'b00000: O_SEGMENT <= 8'b11000000;
		    5'b00001: O_SEGMENT <= 8'b11111001;
		    5'b00010: O_SEGMENT <= 8'b10100100;
		    5'b00011: O_SEGMENT <= 8'b10110000;
		    5'b00100: O_SEGMENT <= 8'b10011001;
		    5'b00101: O_SEGMENT <= 8'b10010010;
		    5'b00110: O_SEGMENT <= 8'b10000010;
		    5'b00111: O_SEGMENT <= 8'b11111000;
		    5'b01000: O_SEGMENT <= 8'b10000000;
		    5'b01001: O_SEGMENT <= 8'b10010000;
		    5'b01010: O_SEGMENT <= 8'b10001000;
		    5'b01011: O_SEGMENT <= 8'b10000011;
		    5'b01100: O_SEGMENT <= 8'b11000110;
		    5'b01101: O_SEGMENT <= 8'b10100001;
		    5'b01110: O_SEGMENT <= 8'b10000110;
		    5'b01111: O_SEGMENT <= 8'b10001110;

		    5'b10000: O_SEGMENT <= 8'b00000000;
		    5'b10001: O_SEGMENT <= 8'b10111111;
		    default:  O_SEGMENT <= 8'b11111111;
		 endcase
	 end
endmodule
