library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

library work;
use work.DisplayUnit_pkg.all;
use work.MIPS_pkg.all;

entity RAM is
	
	generic(	ADDR_BUS_SIZE : positive := 6;
				DATA_BUS_SIZE : positive := 32);
				
	port(	clk : in std_logic;
		readEn : in std_logic;
		writeEn : in std_logic;
		address : in std_logic_vector(ADDR_BUS_SIZE-1 downto 0);
		writeData : in std_logic_vector(DATA_BUS_SIZE-1 downto 0);
		readData : out std_logic_vector(DATA_BUS_SIZE-1 downto 0));
		
end RAM;

