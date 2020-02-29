library IEEE;
use IEEE.std_logic_1164.all;

entity DrinksMachine is

	port(	CLOCK_50	:	in std_logic;
			SW			:	in std_logic_vector(2 downto 0);
			KEY		:	in std_logic_vector(0 downto 0);
			LEDG		:	out std_logic_vector(0 downto 0);
			HEX7		:	out std_logic_vector(6 downto 0);
			HEX6		:	out std_logic_vector(6 downto 0);
			HEX5		:	out std_logic_vector(6 downto 0));

end DrinksMachine;

architecture Shell of DrinksMachine is

	signal clk50Mhz, s_clk	:	std_logic;
	signal sm_money, sc_money : std_logic_vector(3 downto 0);
	signal s_hex6, s_hex7, s_hex5	:	std_logic_vector(6 downto 0);

begin

	clk50MHz <= CLOCK_50;

	sw_debounce : entity WORK.DebounceUnit(Behavioral)
		generic map(clkFrekHz => 50000,
						blindmSec => 100,
						inPol		 => '0',
						outPol	 => '1')
		port map(reset			 => SW(0),
					refClk		 => clk50MHz,
					dirtyIn		 => KEY(0),
					pulsedOut	 => s_clk);
					
	drink_core	:	entity work.DrinksFSM(Behavioral)
		port map(C		=>	SW(2),
					V		=>	SW(1),
					reset =>	SW(0),
					clk	=>	s_clk,
					drink	=>	LEDG(0),
					m_money => sm_money,
					c_money => sc_money);
					
	hex7_seg_dec	:	entity work.Bin7SegDecoder(Behavioral)
		port map(binInput => sc_money,
					decOut_n => s_hex7);
					
	hex6_seg_dec	:	entity work.Bin7SegDecoder(Behavioral)
		port map(binInput => sm_money,
					decOut_n => s_hex6);
	hex5_seg_dec	:	entity work.Bin7SegDecoder(Behavioral)
		port map(binInput => "0000",
					decOut_n => s_hex5);
	
	HEX7 <= s_hex7;
	HEX6 <= s_hex6;
	HEX5 <= s_hex5;

end Shell;