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

-- DATE "11/28/2017 20:51:22"

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

ENTITY 	Guiao6_Ex4C IS
    PORT (
	\Out\ : OUT std_logic;
	B : IN std_logic;
	C : IN std_logic;
	D : IN std_logic;
	A : IN std_logic
	);
END Guiao6_Ex4C;

-- Design Ports Information
-- Out	=>  Location: PIN_34,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A	=>  Location: PIN_32,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- C	=>  Location: PIN_43,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B	=>  Location: PIN_33,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- D	=>  Location: PIN_31,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Guiao6_Ex4C IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \ww_Out\ : std_logic;
SIGNAL ww_B : std_logic;
SIGNAL ww_C : std_logic;
SIGNAL ww_D : std_logic;
SIGNAL ww_A : std_logic;
SIGNAL \Out~output_o\ : std_logic;
SIGNAL \A~input_o\ : std_logic;
SIGNAL \B~input_o\ : std_logic;
SIGNAL \D~input_o\ : std_logic;
SIGNAL \C~input_o\ : std_logic;
SIGNAL \inst|6~0_combout\ : std_logic;
SIGNAL \inst|ALT_INV_6~0_combout\ : std_logic;

BEGIN

\Out\ <= \ww_Out\;
ww_B <= B;
ww_C <= C;
ww_D <= D;
ww_A <= A;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\inst|ALT_INV_6~0_combout\ <= NOT \inst|6~0_combout\;

-- Location: IOOBUF_X0_Y5_N16
\Out~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|ALT_INV_6~0_combout\,
	devoe => ww_devoe,
	o => \Out~output_o\);

-- Location: IOIBUF_X0_Y6_N15
\A~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A,
	o => \A~input_o\);

-- Location: IOIBUF_X0_Y6_N22
\B~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B,
	o => \B~input_o\);

-- Location: IOIBUF_X0_Y7_N1
\D~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_D,
	o => \D~input_o\);

-- Location: IOIBUF_X5_Y0_N22
\C~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_C,
	o => \C~input_o\);

-- Location: LCCOMB_X1_Y6_N0
\inst|6~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|6~0_combout\ = (\C~input_o\ & (((!\D~input_o\)))) # (!\C~input_o\ & (\B~input_o\ $ (((\A~input_o\) # (\D~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100110110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A~input_o\,
	datab => \B~input_o\,
	datac => \D~input_o\,
	datad => \C~input_o\,
	combout => \inst|6~0_combout\);

\ww_Out\ <= \Out~output_o\;
END structure;


