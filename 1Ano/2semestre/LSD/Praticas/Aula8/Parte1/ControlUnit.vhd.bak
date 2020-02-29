library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity ControlUnit is
	port(reset		: in  std_logic;
		  clk			: in  std_logic;
		  statop		: in  std_logic;
		  laprst		: in  std_logic;
		  cntReset	: out std_logic;
		  cntEnable	: out std_logic;
		  regEnable	: out std_logic);
end ControlUnit;

architecture Behavioral of ControlUnit is

	type TState is (TCleared, TStarted, TStopped, TLapView);
	signal s_currentState, s_nextState : TState;

begin
	sync_proc : process(clk)
	begin
		if (rising_edge(clk)) then
			if (reset = '1') then
				s_currentState <= TCleared;
			else
				s_currentState <= s_nextState;
			end if;
		end if;
	end process;

	comb_proc : process(s_currentState, statop, laprst)
	begin
		case (s_currentState) is
		when TCleared =>
			cntReset  <= '1';
			cntEnable <= '1';
			regEnable <= '1';
			if (statop = '1') then
				s_nextState <= TStarted;
			else
				s_nextState <= TCleared;
			end if;

		when TStarted =>
			cntReset  <= '0';
			cntEnable <= '1';
			regEnable <= '1';
			if (statop = '1') then
				s_nextState <= TStopped;
			elsif (laprst = '1') then
				s_nextState <= TLapView;
			else
				s_nextState <= TStarted;
			end if;

		when TStopped =>
			cntReset  <= '0';
			cntEnable <= '0';
			regEnable <= '1';
			if (statop = '1') then
				s_nextState <= TStarted;
			elsif (laprst = '1') then
				s_nextState <= TCleared;
			else
				s_nextState <= TStopped;
			end if;

		when TLapView =>
			cntReset  <= '0';
			cntEnable <= '1';
			regEnable <= '0';
			if (laprst = '1') then
				s_nextState <= TStarted;
			elsif(statop='1') then
				regEnable <= '1';
				s_nextState <= TCleared;
			else
				s_nextState <= TLapView;
			end if;
		end case;

	end process;

end Behavioral;
