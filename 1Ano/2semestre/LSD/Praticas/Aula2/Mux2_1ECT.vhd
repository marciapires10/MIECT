library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity Mux2_1 is
	port(	dataln	:	in STD_LOGIC_VECTOR(3 downto 0);
			sel		:	in STD_LOGIC_VECTOR(1 downto 0);
			dataOut	:	out STD_LOGIC);
end Mux2_1;

Architecture BehavProcess of Mux2_1 is
begin

	process(sel,dataln)
	begin
		if(sel="00") then
			dataOut <= dataln(0);
		elsif(sel="01") then
			dataOut <= dataln(1);
		elsif(sel="10") then
			dataOut <= dataln(2);
		else
			dataOut <= dataln(3);
		end if;
	end process;
end BehavProcess;
