// 1. das programm 2 mal so laufen lassen
// 2. entferne /tmp/linktest
// 3. ln -s /tmp/lalalala /tmp/linktest
// 4. programm laufen lassen
// 5. real path in der ausgabe zeigt /tmp/lalalala und nicht /tmp/linktest
// ergo: symlinks wird blind gefolgt


import java.io.*;

public class resi_afg2d
{
	public static void main(String[] args)
	{
		File		file_info = new File("/tmp/linktest");
		FileWriter	file;

		
		System.out.println("Try to open file "+file_info.getName());
		if(file_info.exists())
			System.out.println("\tFile exists.");
		else
			System.out.println("\tFile does not exist.");

                
		try
		{
			file = new FileWriter(file_info);
			System.out.println("Real path: "+file_info.getCanonicalPath());
			file.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

	}
}
