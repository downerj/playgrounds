import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.Cursor;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

/*********************************************************
 * JAVASCRIPT-CANVAS CLASS [MAIN]
 *********************************************************/
public class JSCanvas extends Application
{
   /******************************************************
    * 
    ******************************************************/
   @Override
   public void start(Stage stage)
   {
      // display debug message
      System.err.printf("Initializing GUI...");
      
      // initialize the canvas and window
      Canvas   canvas = new Canvas(500, 500);
      GridPane pane   = new GridPane();
      Scene    scene  = new Scene(pane);
      
      // initialize the scripting engine
      ScriptEngineManager mgr = new ScriptEngineManager(null);
      ScriptEngine        eng = mgr.getEngineByName("nashorn");
      GraphicsContext     ctx = canvas.getGraphicsContext2D();
      
      // finish up GUI
      pane.add(canvas, 0, 0);
      stage.setScene(scene);
      stage.sizeToScene();
      stage.setResizable(false);
      stage.setTitle("JSCanvas");
      
      // display debug message
      System.err.printf("Complete%n");
      
      // display debug message
      System.err.printf("Fetching command-line arguments...");
      
      // get command-line arguments
      Object[] objArgs = getParameters().getRaw().toArray();
      String[] args    = new String[objArgs.length];
      for (int i = 0; i < objArgs.length; i++)
         args[i] = (String) objArgs[i];
      
      // display debug message
      System.err.printf("Complete%n");
      
      // display debug message
      System.err.printf("Initializing JavaScript engine...");
      
      // add variables to the JavaScript engine
      eng.put("args", args);
      eng.put("canvas", canvas);
      eng.put("ctx", ctx);
      
      // display debug message
      System.err.printf("Complete%n");
      
      if (args.length > 0)
      {
         FileReader fin;
         try
         {
            // display debug message
            System.err.printf("Reading library source file...");
            
            // load and evaluate predefined functions
            fin = new FileReader("../lib/functions.js");
            eng.eval(fin);
            fin.close();
            
            // display debug message
            System.err.printf("Complete%n");
            
            // display debug message
            System.err.printf("Reading user source file...");
            
            // load and evaluate the file
            fin = new FileReader(args[0]);
            eng.eval(fin);
            fin.close();
            
            // run the user-defined initializer
            if (eng.get("init") != null)
               eng.eval("init();");
            else
            {
               System.err.printf("Function init() not defined%n");
               System.exit(1);
            }
            
            // attach the user-defined main loop to a timer
            if (eng.get("run") != null)
            {
               AnimationTimer timer = new AnimationTimer()
               {
                  public void handle(long now)
                  {
                     try
                     {
                        eng.eval("run();");
                     }
                     catch (ScriptException se)
                     {
                        System.err.println(se.getMessage());
                        System.exit(1);
                     }
                  }
               };
               
               timer.start();
               
               scene.setOnKeyPressed(new EventHandler<KeyEvent> ()
               {
                  public void handle(final KeyEvent event)
                  {
                     try
                     {
                        KeyCode key = event.getCode();
                        eng.eval(
                           "ui.setKey(\"" +
                           key.getName()  +
                           "\", true);"
                        );
                     }
                     catch (ScriptException se)
                     {
                        System.err.println(se.getMessage());
                     }
                  }
               });
               
               scene.setOnKeyReleased(new EventHandler<KeyEvent> ()
               {
                  public void handle(final KeyEvent event)
                  {
                     try
                     {
                        KeyCode key = event.getCode();
                        eng.eval(
                           "ui.setKey(\"" +
                           key.getName()  +
                           "\", false);"
                        );
                     }
                     catch (ScriptException se)
                     {
                        System.err.println(se.getMessage());
                     }
                  }
               });
               
               scene.setOnMouseMoved(new EventHandler<MouseEvent> ()
               {
                  public void handle(final MouseEvent event)
                  {
                     try
                     {
                        double x = event.getSceneX();
                        double y = event.getSceneY();
                        eng.eval(
                           "ui.setXY("  +
                           x + ", " + y +
                           ");"
                        );
                     }
                     catch (ScriptException se)
                     {
                        System.err.println(se.getMessage());
                     }
                  }
               });
               
               scene.setCursor(Cursor.NONE);
            }
            else
            {
               System.err.printf("Function run() not defined%n");
               System.err.printf("(Ignoring animation)...");
            }
            
            // display debug message
            System.err.printf("Complete%n");
            
            // display the GUI
            stage.show();
         }
         // parse any file errors
         catch (IOException ioe)
         {
            // get the user's source filename
            File   file = new File(args[0]);
            String message;
            
            // parse the error and set the message accordingly
            if (!file.exists())
               message = "Cannot find file \"" + args[0] + "\"";
            else if (file.isDirectory())
               message = "\"" + args[0] + "\" is a directory";
            else if (!file.canRead())
               message = "Cannot read file \"" + args[0] + "\"";
            else
               message = ioe.getMessage();
               
            System.out.println(message);
            
            System.exit(1);
         }
         // parse any script errors
         catch (ScriptException se)
         {
            String message = se.getMessage();
            
            System.out.println(message);
            
            System.exit(1);
         }
      }
      // if no filename was provided, then display a message
      else
      {
         System.out.println("No filename specified");
         System.exit(1);
      }
   }
   
   /******************************************************
    * 
    ******************************************************/
   public static void main(String[] args)
   {
      launch(args);
   }
}
