library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity Register_N is

	generic(N: integer := 32);
	
	port(clk    : in  std_logic;
		  writeEnable : in std_logic;
		  dataIn : in  std_logic_vector(N-1 downto 0);
		  dataOut: out std_logic_vector(N-1 downto 0));
		  
end Register_N;

architecture Behavioral of Register_N is

	signal s_data : std_logic_vector(N-1 downto 0);
	
begin
	process(clk)
	begin
		if (rising_edge(clk)) then
			if (writeEnable = '1') then
				s_data <= dataIn;
			end if;
			dataOut <= s_data;
		end if;
	end process;
	
end Behavioral;