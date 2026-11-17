----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 17.11.2026 12:33:04
-- Design Name: 
-- Module Name: digital_circuit_ex_1 - Behavioral
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

entity digital_circuit_ex_1 is
    Port ( A, B, C, D : in STD_LOGIC;
           E, F, G, H : out STD_LOGIC);
end digital_circuit_ex_1;

architecture behav_logic_circuit of digital_circuit_ex_1 is
begin
    E <= A or B;
    F <= A and B and C and D;
    G <= not D;
    H <= A xor B;

end behav_logic_circuit;
