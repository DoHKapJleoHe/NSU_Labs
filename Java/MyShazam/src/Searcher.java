import java.io.File;

public class Searcher
{
    public Searcher() {}

    public void run(String fileName)
    {
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

    public void showFile(File fileToShow)
    {
        String pathToFile = fileToShow.getPath();

    }

}
