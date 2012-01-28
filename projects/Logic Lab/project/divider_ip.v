/*******************************************************************************
*     This file is owned and controlled by Xilinx and must be used             *
*     solely for design, simulation, implementation and creation of            *
*     design files limited to Xilinx devices or technologies. Use              *
*     with non-Xilinx devices or technologies is expressly prohibited          *
*     and immediately terminates your license.                                 *
*                                                                              *
*     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"            *
*     SOLELY FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR                  *
*     XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION          *
*     AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION              *
*     OR STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS                *
*     IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,                  *
*     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE         *
*     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY                 *
*     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE                  *
*     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR           *
*     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF          *
*     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          *
*     FOR A PARTICULAR PURPOSE.                                                *
*                                                                              *
*     Xilinx products are not intended for use in life support                 *
*     appliances, devices, or systems. Use in such applications are            *
*     expressly prohibited.                                                    *
*                                                                              *
*     (c) Copyright 1995-2007 Xilinx, Inc.                                     *
*     All rights reserved.                                                     *
*******************************************************************************/
// The synthesis directives "translate_off/translate_on" specified below are
// supported by Xilinx, Mentor Graphics and Synplicity synthesis
// tools. Ensure they are correct for your synthesis tool(s).

// You must compile the wrapper file divider_ip.v when simulating
// the core, divider_ip. When compiling the wrapper file, be sure to
// reference the XilinxCoreLib Verilog simulation library. For detailed
// instructions, please refer to the "CORE Generator Help".

`timescale 1ns/1ps

module divider_ip(
	clk,
	dividend,
	divisor,
	quotient,
	remainder,
	rfd);


input clk;
input [15 : 0] dividend;
input [7 : 0] divisor;
output [15 : 0] quotient;
output [7 : 0] remainder;
output rfd;

// synthesis translate_off

      DIV_GEN_V1_0 #(
		.ALGORITHM_TYPE(1),
		.BIAS(0),
		.C_HAS_ACLR(0),
		.C_HAS_CE(0),
		.C_HAS_SCLR(0),
		.C_SYNC_ENABLE(0),
		.DIVCLK_SEL(1),
		.DIVIDEND_WIDTH(16),
		.DIVISOR_WIDTH(8),
		.EXPONENT_WIDTH(8),
		.FRACTIONAL_B(0),
		.FRACTIONAL_WIDTH(8),
		.LATENCY(1),
		.MANTISSA_WIDTH(8),
		.SIGNED_B(0))
	inst (
		.CLK(clk),
		.DIVIDEND(dividend),
		.DIVISOR(divisor),
		.QUOTIENT(quotient),
		.REMAINDER(remainder),
		.RFD(rfd),
		.CE(),
		.ACLR(),
		.SCLR(),
		.DIVIDEND_MANTISSA(),
		.DIVIDEND_SIGN(),
		.DIVIDEND_EXPONENT(),
		.DIVISOR_MANTISSA(),
		.DIVISOR_SIGN(),
		.DIVISOR_EXPONENT(),
		.QUOTIENT_MANTISSA(),
		.QUOTIENT_SIGN(),
		.QUOTIENT_EXPONENT(),
		.OVERFLOW(),
		.UNDERFLOW());


// synthesis translate_on

// XST black box declaration
// box_type "black_box"
// synthesis attribute box_type of divider_ip is "black_box"

endmodule

