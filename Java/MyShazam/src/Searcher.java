import jdk.jfr.StackTrace;

import java.io.*;

public class Searcher
{
    public Searcher() {}

    public void run(String fileName) throws FileNotFoundException {
        File root = new File("C:\\Users\\eduar\\Desktop\\Тексты песен");

        if(root.isDirectory())
        {
            File[] filesInDirectory = root.listFiles(); //listing files of directory in an array
            if (filesInDirectory == null) {
                System.out.println("There is no files in the directory!");
                System.exit(0);
            }

            File searchedFile = new File(fileName);

            for (File file : filesInDirectory)
            {
                if (file.compareTo(searchedFile) == 0) //if they are equal
                {
                    showFile(file);
                }
            }
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
