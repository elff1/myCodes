`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:19:58 05/26/2011 
// Design Name: 
// Module Name:    dispaly_ASCII 
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
module display_seg(clk, reset, disp_num, dp_in, an, sseg);
	input wire clk, reset;
	input wire [31:0] disp_num; // ASCII
	input wire [3:0] dp_in; // 4 decimal points
	output reg [3:0] an; // enable 1-out-of-4 asserted low
	output reg [7:0] sseg;
  
    localparam N = 18; //refreshing rate around 800 Hz (50 MHz/2^16)
    reg [N-1:0] q_reg; // internal signal declaration
    wire [N-1:0] q_next;
    reg [7:0] seg_in;
    reg dp;
    //N-bit counter
    always @(posedge clk, posedge reset)
    if (reset)
        q_reg <= 0;
    else
        q_reg <= q_next;
        
    assign q_next = q_reg + 1; // next©\state logic
    always @*
    case (q_reg[N-1:N-2])
        2'b00:
        begin
            an = 4'b1110;
            seg_in = disp_num[7:0];
            dp = dp_in[0];
        end
        2'b01:
        begin
            an = 4'b1101;
            seg_in = disp_num[15:8];
            dp = dp_in[1];
        end
        2'b10:
        begin
            an = 4'b1011;
            seg_in = disp_num[23:16];
            dp = dp_in[2];
        end
        default:
        begin
            an = 4'b0111;
            seg_in = disp_num[31:24];
            dp = dp_in[3];
        end
    endcase    
    always @*
    begin
        sseg[6:0] = ~seg_in[6:0];
        sseg[7] = dp;
    end    
endmodule 