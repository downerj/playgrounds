/*********************************************************
 * 
 *********************************************************/
var stdin   = java.lang.System['in'];
var stdscan = new java.util.Scanner(stdin);
var stdout  = java.lang.System['out'];

/*********************************************************
 * 
 *********************************************************/
function print(string)
{
   if (string === null || string === undefined)
      string = '';
   
   stdout.print(string);
}

/*********************************************************
 * 
 *********************************************************/
function println(string)
{
   if (string === null || string === undefined)
      string = '';

   stdout.println(string);
}

/*********************************************************
 * 
 *********************************************************/
function prompt(msg)
{
   print(msg);
   
   print(ANSI_GREEN);
   var input = read();
   print(ANSI_RESET);

   return input;
}

/*********************************************************
 * 
 *********************************************************/
function promptLine(msg)
{
   print(msg);
   
   print(ANSI_GREEN);
   var input = readline();
   print(ANSI_RESET);

   return input;
}

/*********************************************************
 * 
 *********************************************************/
function promptInt(msg)
{
   print(msg);
   
   print(ANSI_GREEN);
   var input = readint();
   print(ANSI_RESET);
   
   return input;
}

/*********************************************************
 * 
 *********************************************************/
function promptFloat(msg)
{
   print(msg);
   
   print(ANSI_GREEN);
   var input = readfloat();
   print(ANSI_RESET);
   
   return input;
}

/*********************************************************
 * 
 *********************************************************/
function clear()
{
   print(ANSI_CLEAR);
}

/*********************************************************
 * 
 *********************************************************/
function read()
{
   return stdscan.next();
}

/*********************************************************
 * 
 *********************************************************/
function readfloat()
{
   return parseFloat(stdscan.next());
}

/*********************************************************
 * 
 *********************************************************/
function readint()
{
   return parseInt(stdscan.next());
}

/*********************************************************
 * 
 *********************************************************/
function readline()
{
   return stdscan.nextLine();
}

/*********************************************************
 * 
 *********************************************************/
function color(string)
{
   return javafx.scene.paint.Color.web(string);
}

/*********************************************************
 * 
 *********************************************************/
ui =
{
   /******************************************************
    * 
    ******************************************************/
   keyUp:    0,
   keyDown:  0,
   keyLeft:  0,
   keyRight: 0,
   keyF3:    0,
   x:        0,
   y:        0,
   button:   0,
   
   /******************************************************
    * 
    ******************************************************/
   setKey: function(code, state)
   {
      switch (code)
      {
         case 'Up':
            this.keyUp = (state) ? ++this.keyUp : 0;
            break;
         
         case 'Down':
            this.keyDown = (state) ? ++this.keyDown : 0;
            break;
         
         case 'Left':
            this.keyLeft = (state) ? ++this.keyLeft : 0;
            break;
         
         case 'Right':
            this.keyRight = (state) ? ++this.keyRight : 0;
            break;
         
         case 'F3':
            this.keyF3 = (state) ? ++this.keyF3 : 0;
            break;
      }
   },
   
   /******************************************************
    * 
    ******************************************************/
   setXY: function(x, y)
   {
      this.x = x;
      this.y = y;
   },
};
