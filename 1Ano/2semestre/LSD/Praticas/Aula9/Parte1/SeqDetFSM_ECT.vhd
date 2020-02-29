library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity SeqDetFSM is

	port(xin	 :	in std_logic;
		  yout :	out std_logic;
		  clk	 :	in std_logic);

end SeqDetFSM;


architecture MealyArch of SeqDetFSM is

	type Tstate is (S0, S1, S2, S3);
	signal pState, nState	:	Tstate;

begin

	clkproc: process(clk)
	
	begin
	
		if(rising_edge(clk)) then
		
			pState <= nState;
			
		end if;
		
	end process;

	combProcess: process(xin, pState)
	
	begin
	
		yout <= '0';
		
		case pState is
		
			when S0=>
				if(xin='1') then
					nState <= S1;
				else
					nState <= S0;
				end if;
				
			when S1=>
				if(xin='1') then
					nState <= S1;
				else
					nState <= S2;
				end if;
				
			when S2=>
				if(xin='1') then
					nState <= S3;
				else
					nState <= S0;
				end if;
				
			when S3=>
				if(xin='1') then
					nState <= S1;
					yout <= '1';
				else
					nState <= S2;
				end if;
				
			when others =>
				nState <= S0;
			end case;
	end process;

end MealyArch;

architecture MooreArch of SeqDetFSM is

	type Tstate is (S0, S1, S2, S3, S4, S5);
	signal pState, nState	:	Tstate;

begin

	clkproc: process(clk)
	begin
		if(rising_edge(clk)) then
			pState <= nState;
		end if;
	end process;

	combProcess: process(xin, pState)
	begin
		yout <= '0';
		case pState is
			when S0=>
				if(Xin='1') then
					nState <= S1;
				else
					nState <= S5;
				end if;
			
			when S1 =>
				if(Xin='1') then
					nState <= S1;
				else
					nState <= S2;
				end if;
				
			when S2 =>
				if(Xin='1') then
					nState <= S3;
				else
					nState <= S5;
				end if;
			
			when S3 =>
				if(Xin='1') then
					nState <= S4;
				else
					nState <= S2;
				end if;
				
			when S4 =>
				yout <= '1';
				if(Xin='1') then
					nState <= S1;
				else
					nState <= S2;
				end if;
				
			when S5 =>
				if(Xin='1') then
					nState <= S1;
				else
					nState <= S5;
				end if;
			when others =>
				nState <= S0;
			end case;
		end process;
			
end MooreArch;