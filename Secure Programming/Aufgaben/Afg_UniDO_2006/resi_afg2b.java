import java.io.*;

public class resi_afg2b
{
	public static void main(String[] args)
	{
		int	i,
			i_max = Integer.MAX_VALUE,
			i_min = Integer.MIN_VALUE;
		
		i = i_max + 1;
		System.out.println("i_max ("+i_max+", 0b"+Integer.toBinaryString(i_max)+") + 1 = "+i+" (0b"+Integer.toBinaryString(i)+")");

		i = i_min - 1;
		System.out.println("i_min ("+i_min+", 0b"+Integer.toBinaryString(i_min)+") - 1 = "+i+" (0b"+Integer.toBinaryString(i)+")");
		
		System.exit(0);
	}
}