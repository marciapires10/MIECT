library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;

entity DrinksFSM is

	port(	C		:	in std_logic;
			V		:	in std_logic;
			reset	:	in std_logic;
			clk	:	in std_logic;
			drink	:	out std_logic;
			m_money	:	out std_logic_vector(3 downto 0);
			c_money	:	out std_logic_vector(3 downto 0));


end DrinksFSM;

architecture Behavioral of DrinksFSM is

	type Tstate is (S0,S1,S2,S3,S4,S5, S6, S7, S8, S9, S10, S11);
	signal pState, nState	:	Tstate;
	signal sm_money	:	unsigned(3 downto 0);
	signal sc_money	:	unsigned(3 downto 0);
	signal s_reset		:	std_logic;

	
begin
	m_money <= std_logic_vector(sm_money);
	c_money <= std_logic_vector(sc_money);

	clk_proc: process(clk, reset)
	begin
		if(reset = '1') then
			pState <= S0;
		elsif(rising_edge(clk)) then
			pState <= nState;
		end if;
	end process;

	comb_process: process(pState, C, V)
	begin
		drink <= '0';
		sc_money <= "0000";
		case pState is
			when S0 =>
				sm_money <= "0000";
				if(C='1') then
					nState <= S6;
				elsif(V='1') then
					nState <= S1;
				else
					nState <= S0;
				end if;
			when S1 =>
				sm_money <= "0010";
				if(C='1') then
					nState <= S7;
				elsif(V='1') then
					nState <= S2;
				else
					nState <= S1;
				end if;
			when S2 =>
				sm_money <= "0100";
				if(C='1') then
					nState <= S8;
				elsif(V='1') then
					nState <= S3;
				else
					nState <= S2;
				end if;

			when S3 =>
				sm_money <= "0110";
				if(C='1') then
					nState <= S10;
				elsif(V='1') then
					nState <= S4;
				else
					nState <= S3;
				end if;
				
			when S4 =>
				sm_money <= "1000";
				if(C='1') then
					nState <= S11;
				elsif(V='1') then
					nState <= S5;
				else
					nState <= S4;
				end if;
			when S5 =>
				sm_money <= "0000";
				sc_money <= "0001";
				nState <= S5;
				drink <= '1';
			when S6 =>
				sm_money <= "0101";
				if(C='1') then
					nState <= S5;
				elsif(V='1') then
					nState <= S7;
				else
					nState <= S6;
				end if;
			when S7 =>
				sm_money <= "0111";
				if(C='1') then
					nState <= S9;
				elsif(V='1') then
					nState <= S8;
				else
					nState <= S7;
				end if;
			when S8 =>
				sm_money <= "1001";
				nState <= S8;
				drink <= '1';
			when S9 =>
				sm_money <= "0010";
				sc_money <= "0001";
				nState <= S9;
				drink <= '1';
			when S10=>
				sm_money <= "0001";
				sc_money <= "0001";
				nState <= S10;
				drink <= '1';
			when S11=>
				sm_money <= "0010";
				sc_money <= "0001";
				nState <= S11;
				drink <= '1';
			
			end case;
	end process;

end Behavioral;