import java.io.*;

class RunTst {
  static {
    System.loadLibrary("tst");
  }

  public final static void main(String[] arg) {
    tst t = new tst();
    System.out.println("Here is the string: "+tst.getString());
  }
}
