library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity AccN is
	generic(N    : positive := 4);
	port(reset   : in std_logic;
		  enable  : in std_logic;
		  clk     : in std_logic;
		  dataIn  : in std_logic_vector((N-1) downto 0);
		  dataOut : out std_logic_vector((N-1) downto 0));

end AccN;

architecture Structural of AccN is
		signal s_adderOut, s_regOut : unsigned((N-1) downto 0);
		
	begin 
		adderN: entity work.AdderN(Behavioral);
		
				 generic map(N => 4)
				 port map(operand0 => dataIn,
							 operand1 => s_regOut,
							 result   => s_adderOut);
							 
		regN: entity work.RegN(Behavioral);
				
				generic map(N => 4)
				port map(clk	 => clk,
							reset  => reset,
							enable => enable,
							dataIn => s_adderOut,
							dataOut=> s_regOut);
							
		dataOut <= std_logic_vector(s_regOut);
		
end Structural;
		  