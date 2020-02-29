-- Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, the Altera Quartus Prime License Agreement,
-- the Altera MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Altera and sold by Altera or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 15.1.1 Build 189 12/02/2015 SJ Lite Edition"

-- DATE "11/28/2017 22:45:43"

-- 
-- Device: Altera EP4CE6E22C6 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Guiao6_Ex5 IS
    PORT (
	F : OUT std_logic;
	C2 : IN std_logic;
	A : IN std_logic;
	B : IN std_logic;
	C0 : IN std_logic;
	C1 : IN std_logic
	);
END Guiao6_Ex5;

-- Design Ports Information
-- F	=>  Location: PIN_33,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A	=>  Location: PIN_30,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B	=>  Location: PIN_28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- C1	=>  Location: PIN_38,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- C0	=>  Location: PIN_31,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- C2	=>  Location: PIN_32,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Guiao6_Ex5 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_F : std_logic;
SIGNAL ww_C2 : std_logic;
SIGNAL ww_A : std_logic;
SIGNAL ww_B : std_logic;
SIGNAL ww_C0 : std_logic;
SIGNAL ww_C1 : std_logic;
SIGNAL \F~output_o\ : std_logic;
SIGNAL \C0~input_o\ : std_logic;
SIGNAL \C1~input_o\ : std_logic;
SIGNAL \C2~input_o\ : std_logic;
SIGNAL \A~input_o\ : std_logic;
SIGNAL \B~input_o\ : std_logic;
SIGNAL \inst|sub|81~0_combout\ : std_logic;
SIGNAL \inst|sub|81~1_combout\ : std_logic;

BEGIN

F <= ww_F;
ww_C2 <= C2;
ww_A <= A;
ww_B <= B;
ww_C0 <= C0;
ww_C1 <= C1;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: IOOBUF_X0_Y6_N23
\F~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|sub|81~1_combout\,
	devoe => ww_devoe,
	o => \F~output_o\);

-- Location: IOIBUF_X0_Y7_N1
\C0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_C0,
	o => \C0~input_o\);

-- Location: IOIBUF_X1_Y0_N22
\C1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_C1,
	o => \C1~input_o\);

-- Location: IOIBUF_X0_Y6_N15
\C2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_C2,
	o => \C2~input_o\);

-- Location: IOIBUF_X0_Y8_N15
\A~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A,
	o => \A~input_o\);

-- Location: IOIBUF_X0_Y9_N8
\B~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B,
	o => \B~input_o\);

-- Location: LCCOMB_X1_Y8_N24
\inst|sub|81~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|sub|81~0_combout\ = (\A~input_o\ & ((\B~input_o\ & ((!\C1~input_o\))) # (!\B~input_o\ & ((\C0~input_o\) # (\C1~input_o\))))) # (!\A~input_o\ & ((\B~input_o\ & ((\C0~input_o\) # (\C1~input_o\))) # (!\B~input_o\ & (!\C0~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011111101001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A~input_o\,
	datab => \B~input_o\,
	datac => \C0~input_o\,
	datad => \C1~input_o\,
	combout => \inst|sub|81~0_combout\);

-- Location: LCCOMB_X1_Y8_N26
\inst|sub|81~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|sub|81~1_combout\ = (\C2~input_o\ & ((\C0~input_o\ & (!\C1~input_o\ & !\inst|sub|81~0_combout\)) # (!\C0~input_o\ & (\C1~input_o\ $ (\inst|sub|81~0_combout\))))) # (!\C2~input_o\ & ((\inst|sub|81~0_combout\) # ((!\C0~input_o\ & !\C1~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001111101100001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C0~input_o\,
	datab => \C1~input_o\,
	datac => \C2~input_o\,
	datad => \inst|sub|81~0_combout\,
	combout => \inst|sub|81~1_combout\);

ww_F <= \F~output_o\;
END structure;


