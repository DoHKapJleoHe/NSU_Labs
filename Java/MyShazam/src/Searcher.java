import jdk.jfr.StackTrace;

import java.io.*;
import java.util.Scanner;

public class Searcher
{
    public Searcher() {}

    public void run() throws FileNotFoundException
    {
        File root = new File("C:/Users/eduar/Desktop/Тексты песен");

        Scanner scanner = new Scanner(System.in);
        System.out.println("Write song name: ");
        String songName;

        while(scanner.hasNext())
        {
            songName = scanner.nextLine();
            if (root.isDirectory())
            {
                File[] filesInDirectory = root.listFiles(); //listing files of directory in an array
                if (filesInDirectory == null)
                {
                    System.out.println("There is no files in the directory!");
                    System.exit(0);
                }

                for (File file : filesInDirectory)
                {
                    if (file.getName().replace(".txt", "").equals(songName))
                    {
                        showFile(file);
                    }
                }
            }
            System.out.println("Write song name: ");
        }
    }

    public void showFile(File fileToShow) throws FileNotFoundException
    {
        String pathToFile = fileToShow.getPath();
        FileReader fileReader = new FileReader(pathToFile);
        BufferedReader reader = new BufferedReader(fileReader);

        try
        {
            String lineFromFile = reader.readLine();
            while(lineFromFile != null)
            {
                System.out.println(lineFromFile);
                lineFromFile = reader.readLine();
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

}
