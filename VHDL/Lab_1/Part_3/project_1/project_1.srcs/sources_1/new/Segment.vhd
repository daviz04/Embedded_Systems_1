----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.11.2026 12:34:21
-- Design Name: 
-- Module Name: Segment - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Segment is
    Port ( X, DSI : in STD_LOGIC_VECTOR(3 DOWNTO 0);
           DSO: out STD_LOGIC_VECTOR(3 DOWNTO 0);
           Y : out STD_LOGIC_VECTOR (6 DOWNTO 0));
end Segment;

architecture Behav_Segment of Segment is
begin
    DSO <= not DSI;
    proc_behav_segment: process(X)
    begin
        if(X = "0000") then
        Y <= "0000001";
        
        elsif(X = "0001") then
        Y <= "1001111";
        
        elsif(X = "0010") then
        Y <= "0010010";
        
        elsif(X = "0011") then
        Y <= "0000110";
        
        elsif(X = "0100") then
        Y <= "1001100";
        
        elsif(X = "0101") then
        Y <= "0100100";
        
        elsif(X = "0110") then
        Y <= "1100000";
        
        elsif(X = "0111") then
        Y <= "0001111";
        
        elsif(X = "1000") then
        Y <= "0000000";
        
        elsif(X = "1001") then
        Y <= "0000100";
        
        end if;
    end process;
end Behav_Segment;
