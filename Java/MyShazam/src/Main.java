import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in); // Reading from console

        while (scanner.hasNext())
        {
            String fileName = scanner.nextLine(); // Reading name of the song

            Searcher searcher = new Searcher();

            searcher.run(fileName);
        }
    }
}


