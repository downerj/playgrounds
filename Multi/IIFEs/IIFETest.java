// Compile: javac IIFETest.java
// Run: java IIFETest
// Package: jar cfm IIFETest.jar MANIFEST.MF IIFETest.class
// Run package: java -jar IIFETest.jar

import java.util.function.Supplier;

class IIFETest {
  public static void main(String... _args) {
    final String s0 = "Bye.";
    System.out.println(((Supplier<String>) () -> {
      final String s1 = "Hello!";
      return s1;
    }).get());
    System.out.println(s0);
  }
}

