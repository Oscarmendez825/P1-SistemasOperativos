`timescale 1 ps / 1 ps
module top (
		input  logic [3:0]  buttons_0_ext_export,    
		input  logic        clk_clk,                 
		input  logic        key_select_0_ext_export, 
		output logic [12:0] memory_mem_a,            
		output logic [2:0]  memory_mem_ba,           
		output logic        memory_mem_ck,           
		output logic        memory_mem_ck_n,         
		output logic        memory_mem_cke,          
		output logic        memory_mem_cs_n,         
		output logic        memory_mem_ras_n,        
		output logic        memory_mem_cas_n,        
		output logic        memory_mem_we_n,         
		output logic        memory_mem_reset_n,      
		inout  logic [7:0]  memory_mem_dq,           
		inout  logic        memory_mem_dqs,          
		inout  logic        memory_mem_dqs_n,        
		output logic        memory_mem_odt,          
		output logic        memory_mem_dm,           
		input  logic        memory_oct_rzqin,        
		input  logic        mode_0_ext_export,
		input  logic        percent_ext_export,		
		input  logic        reset_reset,
		output logic        sdram_clk_clk,   
		output logic [12:0] sdram_wire_addr, 
		output logic [1:0]  sdram_wire_ba,   
		output logic        sdram_wire_cas_n,
		output logic        sdram_wire_cke,  
		output logic        sdram_wire_cs_n, 
		inout  logic [15:0] sdram_wire_dq,   
		output logic [1:0]  sdram_wire_dqm,  
		output logic        sdram_wire_ras_n,
		output logic        sdram_wire_we_n, 
		output logic [6:0] pio_7segments_0,
		output logic [6:0] pio_7segments_1,
		output logic [6:0] pio_7segments_2,
		output logic [6:0] pio_7segments_3,       
		input  logic        start_ext_export         
	);
	
	
	logic [6:0] seg7_0_ext_export,
					seg7_1_ext_export,
					seg7_2_ext_export,
					seg7_3_ext_export;
	
	platform plat (
		buttons_0_ext_export,    
		clk_clk,                 
		key_select_0_ext_export, 
		memory_mem_a,            
		memory_mem_ba,           
		memory_mem_ck,           
		memory_mem_ck_n,         
		memory_mem_cke,          
		memory_mem_cs_n,         
		memory_mem_ras_n,        
		memory_mem_cas_n,        
		memory_mem_we_n,         
		memory_mem_reset_n,     
		memory_mem_dq,           
		memory_mem_dqs,          
		memory_mem_dqs_n,        
		memory_mem_odt,          
		memory_mem_dm,           
		memory_oct_rzqin,        
		mode_0_ext_export,
		percent_ext_export,
		reset_reset,
		sdram_clk_clk,
		sdram_wire_addr,
		sdram_wire_ba,
		sdram_wire_cas_n,
		sdram_wire_cke,
		sdram_wire_cs_n,
		sdram_wire_dq,
		sdram_wire_dqm,
		sdram_wire_ras_n,
		sdram_wire_we_n,
		seg7_0_ext_export,       
		seg7_1_ext_export,       
		seg7_2_ext_export,       
		seg7_3_ext_export,       
		start_ext_export         
	);
	
	
	display7 s0(seg7_0_ext_export[3:0], pio_7segments_0);
	display7 s1(seg7_1_ext_export[3:0], pio_7segments_1);
	display7 s2(seg7_2_ext_export[3:0], pio_7segments_2);
	display7 s3(seg7_3_ext_export[3:0], pio_7segments_3);
	


endmodule
