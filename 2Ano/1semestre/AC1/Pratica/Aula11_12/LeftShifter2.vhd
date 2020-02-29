library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity LeftShifter2 is
	generic(N: integer := 32);
	port(dataIn : in  std_logic_vector(N-1 downto 0);
		  dataOut: out std_logic_vector(N-1 downto 0));
end LeftShifter2;

architecture Behavioral of LeftShifter2 is
begin
		dataOut <= std_logic_vector(shift_left(signed(dataIn), 2));
end Behavioral;