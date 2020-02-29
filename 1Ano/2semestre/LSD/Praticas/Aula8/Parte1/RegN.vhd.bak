library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity RegN is
	generic(size		: integer := 32;
			 resetValue	: std_logic_vector);
	port(asyncReset	: in  std_logic;
		  clk				: in  std_logic;
		  clkEnable		: in  std_logic;
		  syncReset		: in  std_logic;
		  dataIn			: in  std_logic_vector((size - 1) downto 0);
		  dataOut		: out std_logic_vector((size - 1) downto 0));
end RegN;

architecture Behavioral of RegN is
begin
	process(asyncReset, clk)
	begin
		if (asyncReset = '1') then
			dataOut <= resetValue;
		elsif (rising_edge(clk)) then
			if (clkEnable = '1') then
				if (syncReset = '1') then
					dataOut <= resetValue;
				else
					dataOut <= dataIn;
				end if;
			end if;
		end if;
	end process;
end Behavioral;
