// code 2 mal ausführen, wenn file nicht existiert, dann ok
// wenn es existiert und der attacker es rm'n kann, dann schlecht

import java.io.*;
import java.lang.*;

public class resi_afg2c
{
	public static void main(String[] args)
	{
		File			file_info = new File("/tmp/racetest");
		FileWriter	file;
		Process		p;

		
		System.out.println("Try to open file "+file_info.getName());
		if(file_info.exists())
		{
			System.out.println("\tFile exists.");
			// ok the file exists, the attcker has the privileges
			// to remove the file and redirect it to a new one
			// while this code is working on it
			// attacker executes in a shell:
			
			try
			{
				System.out.println("\t\tattacker: rm /tmp/racetest");
				p = Runtime.getRuntime().exec("rm /tmp/racetest");
			
				System.out.println("\t\tattacker: touch /tmp/racetest_anotherfile");
				p = Runtime.getRuntime().exec("touch /tmp/racetest_anotherfile");
			
				System.out.println("\t\tattacker: ln -s /tmp/racetest_anotherfile /tmp/racetest");
				p = Runtime.getRuntime().exec("ln -s /tmp/racetest_anotherfile /tmp/racetest");
			}
			catch(Throwable t)
			{
				t.printStackTrace();
			}
		}
		else
		{
			try
			{
				System.out.println("\tFile does not exist.");

				System.out.println("\t\tattacker: touch /tmp/racetest_anotherfile");
				p = Runtime.getRuntime().exec("touch /tmp/racetest_anotherfile");
			
				System.out.println("\t\tattacker: ln -s /tmp/racetest_anotherfile /tmp/racetest");
				p = Runtime.getRuntime().exec("ln -s /tmp/racetest_anotherfile /tmp/racetest");
			}
			catch(Throwable t)
			{
				t.printStackTrace();
			}
		}
		
                
		try
		{
			file = new FileWriter(file_info);
			System.out.println("Real path: "+file_info.getCanonicalPath());
			file.write("AAAAAAAAAAAAA\n");
			file.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

	}
}
