/*********************************************************
 * JAVASCRIPT EVALUATION ENGINE
 * 
 * AUTHOR:      James D. Downer
 * DATE:        Sat 08/26/2017
 * DESCRIPTION: Evaluates external JavaScript files using a
 *              simple JavaScript engine.
 *********************************************************/

/*********************************************************
 * IMPORTS
 *********************************************************/
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import java.util.Scanner;

/*********************************************************
 * MAIN JAVASCRIPT ENGINE CLASS
 *********************************************************/
public class JSEngine
{
   final static String ANSI_CLEAR   = "\033c";
   final static String ANSI_RED     = "\033[1;31m";
   final static String ANSI_GREEN   = "\033[1;32m";
   final static String ANSI_YELLOW  = "\033[1;33m";
   final static String ANSI_BLUE    = "\033[1;34m";
   final static String ANSI_MAGENTA = "\033[1;35m";
   final static String ANSI_CYAN    = "\033[1;36m";
   final static String ANSI_WHITE   = "\033[1;37m";
   final static String ANSI_RESET   = "\033[0m";
               
   /******************************************************
    * MAIN
    ******************************************************/
   public static void main(String[] args) throws Exception
   {
      // get manager & engine
      ScriptEngineManager mgr = new ScriptEngineManager(null);
      ScriptEngine        eng = mgr.getEngineByName("nashorn");

      // prepare an exit status code
      int exitStatus;
      
      // give the engine some of our I/O objects
      eng.put("args", args);

      // evaluate predetermined JavaScript commands
      FileReader fin1 = new FileReader("../lib/functions.js");
      eng.eval(fin1);
      fin1.close();
      
      // evaluate external script if a filename was given
      if (args.length > 0)
      {
         FileReader fin2;
         // try opening the source file
         try
         {
            fin2 = new FileReader(args[0]);
            eng.eval(fin2);

            exitStatus = 0;
         }
         // parse any file errors
         catch (FileNotFoundException fnfe)
         {
            File file = new File(args[0]);
            String message;

            // parse the error and set the message accordingly
            if (!file.exists())
               message = "Cannot find file \"" + args[0] + "\"";
            else if (file.isDirectory())
               message = "\"" + args[0] + "\" is a directory";
            else if (!file.canRead())
               message = "Cannot read file \"" + args[0] + "\"";
            else
               message = "Cannot open file \"" + args[0] + "\"";

            // print the message
            System.out.print(ANSI_YELLOW);
            System.out.print(message);
            System.out.println(ANSI_RESET);
            
            exitStatus = 1;
         }
         // parse any script errors
         catch (ScriptException se)
         {
            String message = se.getMessage();
            
            System.out.println();

            if (message.contains("java.util.NoSuchElementException"))
               exitStatus = 0;
            else
            {
               System.out.print(ANSI_RED);
               System.out.print(se.getMessage());
               System.out.println(ANSI_RESET);
               
               exitStatus = 1;
            }
         }
         finally
         {
            fin1.close();
         }
      }
      // if no filename was provided, then display a message
      else
      {
         System.out.print(ANSI_YELLOW);
         System.out.print("No filename specified");
         System.out.println(ANSI_RESET);
         
         exitStatus = 1;
      }
      
      // exit back to the system
      System.exit(exitStatus);
   }
}
