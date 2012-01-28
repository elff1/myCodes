`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    18:29:49 12/26/2010 
// Design Name: 
// Module Name:    divisor_top 
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
module Divider_top(
    input CLK,
    input I_RST,
	 input [3:0] I_SW,
	 input [1:0] I_BTN,
	 output [3:0] O_DIGIT_ANODE,
	 output [7:0] O_SEGMENT,
	 output [2:0] O_LEDLAMP
    );

    wire CLK_1ms, CLK_500ms;
	 wire [1:0] BTN;
	 wire [15:0] DIVIDEND;
	 wire [7:0] DIVISOR;
	 wire [7:0] QUOTIENT;
	 wire [7:0] REMAINDER;
	 wire DZ, DO, OPERR;
	 wire [19:0] SEG7DATA;
    wire [3:0] SEG7BLINK;
    wire [2:0] LEDLAMP;
    wire [1:0] DATA_SELECT;
    wire [1:0] BIT_SELECT;
	 wire INCREMENT;
    wire CLEAR;
	 
	 assign DATA_SELECT[1] = I_SW[3];
	 assign DATA_SELECT[0] = I_SW[2];
	 assign BIT_SELECT[1] = I_SW[1];
	 assign BIT_SELECT[0] = I_SW[0];
	 assign INCREMENT = BTN[1];
	 assign CLEAR = BTN[0];

    clk_divider CLK_Divider(CLK,CLK_1ms,CLK_500ms);
	 anti_jitter Anti_Jitter(CLK_1ms,I_BTN,BTN);
    data_input Data_Input(CLK,DATA_SELECT,BIT_SELECT,INCREMENT,CLEAR,I_RST,DIVIDEND,DIVISOR,OPERR);
    
	 
	 /*  add your designed divider_vx here!  */
	 //divider_v1 Divider_V1(CLK_1ms,DIVIDEND,DIVISOR,QUOTIENT,REMAINDER,DZ,DO);
	 divider Divider(CLK_1ms,DIVIDEND,DIVISOR,QUOTIENT,REMAINDER,DZ,DO);
	 
	 
	 display_driver Display_Driver(CLK,DIVIDEND,DIVISOR,QUOTIENT,REMAINDER,DZ,DO,OPERR,DATA_SELECT,BIT_SELECT,SEG7DATA,SEG7BLINK,LEDLAMP);
	 led_lamp LED_Lamp(CLK_500ms,LEDLAMP,O_LEDLAMP);
	 seg7_display Seg7_Display(CLK, CLK_1ms,CLK_500ms,SEG7DATA,SEG7BLINK,O_DIGIT_ANODE,O_SEGMENT);
endmodule
