library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity ChronometerCore is
	port(reset		 : in  std_logic;
		  clk50MHz	 : in  std_logic;
		  statop		 : in  std_logic;
		  laprst		 : in  std_logic;
		  dispOut0_n : out std_logic_vector(6 downto 0);
		  dispOut1_n : out std_logic_vector(6 downto 0);
		  dispOut2_n : out std_logic_vector(6 downto 0);
		  dispOut3_n : out std_logic_vector(6 downto 0);
		  dispOut4_n : out std_logic_vector(6 downto 0);
		  dispOut5_n : out std_logic_vector(6 downto 0));
end ChronometerCore;

architecture Structural of ChronometerCore is

	signal s_clk100Hz 						: std_logic;
	signal s_statop, s_laprst				: std_logic;
	signal s_cntReset, s_cntEnable		: std_logic;
	signal s_regEnable 						: std_logic;
	signal s_counterOut, s_registerOut	: std_logic_vector(23 downto 0);

begin
	clk_divider_500000 : entity WORK.ClkDividerN(Behavioral)
		generic map(divFactor => 500000)
		port map(reset			 => '0',
					clkIn			 => clk50MHz,
					clkOut		 => s_clk100Hz);

	statop_debounce : entity WORK.DebounceUnit(Behavioral)
		generic map(clkFrekHz => 50000,
						blindmSec => 100,
						inPol		 => '0',
						outPol	 => '1')
		port map(reset			 => reset,
					refClk		 => clk50MHz,
					dirtyIn		 => statop,
					pulsedOut	 => s_statop);

	laprst_debounce : entity WORK.DebounceUnit(Behavioral)
		generic map(clkFrekHz => 50000,
						blindmSec => 100,
						inPol		 => '0',
						outPol	 => '1')
		port map(reset			 => reset,
					refClk		 => clk50MHz,
					dirtyIn		 => laprst,
					pulsedOut	 => s_laprst);

	control_unit : entity WORK.ControlUnit(Behavioral)
		port map(reset			 => reset,
					clk			 => clk50MHz,
					statop		 => s_statop,
					laprst		 => s_laprst,
					cntReset		 => s_cntReset,
					cntEnable	 => s_cntEnable,
					regEnable	 => s_regEnable);

	bcd_counter : entity WORK.CntBCDUp4(Behavioral)
		port map(reset			 => s_cntReset,
					clk			 => s_clk100Hz,
					clkEnable	 => s_cntEnable,
					count			 => s_counterOut);

	freeze_register : entity WORK.RegN(Behavioral)
		generic map(size		 => 24,
					  resetValue => "000000000000000000000000")
		port map(asyncReset	 => '0',
					clk			 => clk50MHz,
					clkEnable	 => s_regEnable,
					syncReset	 => '0',
					dataIn		 => s_counterOut,
					dataOut		 => s_registerOut);

	disp_0_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(3 downto 0),
               decOut_n		 => dispOut0_n);

	disp_1_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(7 downto 4),
					decOut_n		 => dispOut1_n);

	disp_2_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(11 downto 8),
					decOut_n		 => dispOut2_n);

	disp_3_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(15 downto 12),
					decOut_n		 => dispOut3_n);
					
	disp_4_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(19 downto 16),
					decOut_n		 => dispOut4_n);
					
	disp_5_decoder : entity WORK.Bin7SegDecoder(Behavioral)
		port map(binInput		 => s_registerOut(23 downto 20),
					decOut_n		 => dispOut5_n);
					
end Structural;
