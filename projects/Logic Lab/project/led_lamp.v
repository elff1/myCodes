`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    19:50:37 12/26/2010 
// Design Name: 
// Module Name:    Led_Lamp 
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
module led_lamp(
    input CLK_500ms,
    input [2:0] LEDLAMP,
    output[2:0] O_LEDLAMP
    );

	 assign O_LEDLAMP = LEDLAMP & {3{CLK_500ms}};
endmodule
