// Example derived from: https://eclipsesource.com/blogs/2015/06/06/registering-java-callbacks-with-j2v8/
// J2V8 is available at Maven Central: https://search.maven.org/search?q=g:com.eclipsesource.j2v8

// Compile:
// javac -cp j2v8_linux_x86_64-4.8.0.jar V8Example.java

// Run:
// java -cp ".:j2v8_linux_x86_64-4.8.0.jar" V8Example

import com.eclipsesource.v8.JavaVoidCallback;
import com.eclipsesource.v8.V8;
import com.eclipsesource.v8.V8Array;
import com.eclipsesource.v8.V8Object;

public class V8Example {
  public V8Example() {
    // Instantiate the runtime.
    V8 v8 = V8.createV8Runtime();
    
    // Register custom bindings to the Java API.
    v8.registerJavaMethod(new PrintLineCallback(), "println");
    
    // Execute JavaScript code.
    v8.executeScript("println('Hello, there!');");
    
    // Finish.
    v8.release();
  }
  
  public static void main(String[] args) {
    V8Example example = new V8Example();
  }
}

class PrintLineCallback implements JavaVoidCallback {
  // Define the behavior of this custom callback.
  @Override
  public void invoke(final V8Object receiver, final V8Array parameters) {
    // If no parameters are given, then simply print a newline character.
    if (parameters.length() == 0) {
      System.out.println();
      return;
    }
    
    // Get the first parameter and print it.
    Object arg1 = parameters.get(0);
    System.out.println(arg1);
  }
}