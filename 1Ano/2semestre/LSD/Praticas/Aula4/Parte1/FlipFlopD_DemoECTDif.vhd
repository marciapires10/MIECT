--------------------------------------------
-- Paulo Gil
-- paulogil@ua.pt
-- LSD-2016
--------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity FlipFlopD_Demo is
	port(KEY		:	in		std_logic_vector(0 downto 0);
		  SW		:	in 	std_logic_vector(2 downto 0);
		  LEDR	:	out 	std_logic_vector(0 downto 0));
end FlipFlopD_Demo;

architecture Shell of FlipFlopD_Demo is
begin

	ff_d :	entity work.FlipFlopD(Behavioral)
		
		port map(clk	=>	KEY(0),
					reset => SW(2),
					set	=>	SW(1),
					d		=> SW(0),
					q		=>	LEDR(0));
end Shell;