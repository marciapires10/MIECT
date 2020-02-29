--------------------------------------------
-- Paulo Gil
-- paulogil@ua.pt
-- LSD-2016
--------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity Register8 is
	port(clk			:	in		std_logic;
		  enable		:	in		std_logic;
		  dataIn		:	in		std_logic_vector(7 downto 0);
		  dataOut	:	out	std_logic_vector(7 downto 0));
end Register8;

architecture Behavioral of Register8 is
begin
	process(clk)
	begin
		if(rising_edge(clk) and enable = '1') then
			dataOut	<= dataIn;
		end if;
	end process;
end Behavioral;
		  