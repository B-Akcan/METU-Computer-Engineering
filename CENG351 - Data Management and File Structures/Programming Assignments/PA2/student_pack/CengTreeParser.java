import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CengTreeParser
{
    public static ArrayList<CengBook> parseBooksFromFile(String filename)
    {
        ArrayList<CengBook> bookList = new ArrayList<CengBook>();

        // You need to parse the input file in order to use GUI tables.
        // TODO: Parse the input file, and convert them into CengBooks
        Scanner s = null;;
        try
        {
            s = new Scanner(new File(filename));
        }
        catch (FileNotFoundException e1)
        {
            e1.printStackTrace();
        }

        String line = null;
        while (s.hasNextLine())
        {
            line = s.nextLine();
            String[] array = line.split("[|]");
            Integer bookID = Integer.parseInt(array[0]);
            String bookTitle = array[1];
            String author = array[2];
            String genre = array[3];

            bookList.add(new CengBook(bookID,bookTitle,author,genre));
        }
        return bookList;
    }

    public static void startParsingCommandLine() throws IOException
    {
        // TODO: Start listening and parsing command line -System.in-.
        @SuppressWarnings("resource")
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        boolean isRunning = true;
        String input = null;

        while(isRunning)
        {
            input = reader.readLine();
            String[] array = input.split("[|]");
            String command = array[0];

            if(command.equalsIgnoreCase("quit"))
            {
                isRunning = false;
            }
            else if(command.equalsIgnoreCase("add"))
            {
                Integer bookID = Integer.parseInt(array[1]);
                String bookTitle = array[2];
                String author = array[3];
                String genre = array[4];

                CengTree.addBook(new CengBook(bookID, bookTitle, author, genre));
            }
            else if(command.equalsIgnoreCase("search"))
            {
                Integer searchKey = Integer.parseInt(array[1]);
                CengTree.searchBook(searchKey);
            }
            else if(command.equalsIgnoreCase("print"))
            {
                CengTree.printTree();
            }
        }

        // There are 4 commands:
        // 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
        // 2) add : Parse and create the book, and call CengBookRunner.addBook(newlyCreatedBook).
        // 3) search : Parse the bookID, and call CengBookRunner.searchBook(bookID).
        // 4) print : Print the whole tree, call CengBookRunner.printTree().
        // Commands (quit, add, search, print) are case-insensitive.

    }
}
