import java.io.*;

public class resi_afg2a
{
	public static void main(String[] args)
	{
		byte	b[] = new byte[10];
		int	i;

		System.out.println("start copying data into a 10 byte array byte-by-byte");
		for(i = 0; i < 20; i++)
		{
			System.out.println("\ti = "+i);
			try
			{
				b[i] = (byte) 0xFF;
			}
			catch(Exception e)
			{
				e.printStackTrace();
			} 
		
		}

		
		System.exit(0);
	}
}