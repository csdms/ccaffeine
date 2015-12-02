public class JavaTest {

  static {
    System.loadLibrary("AbstractFwk");
  }

  public final static void main(String[] args) {
    
    DefaultStringList l = new DefaultStringList();
    
    AbstractFramework fwk = new CcaffeineAbstractFramework(l);
    Services svc = fwk.getBootstrapServices("JavaTest0", "JavaTest", 0);
    PortInfo pi = svc.createPortInfo("myBS", "gov.cca.BuilderService", 0);
    Port p = svc.getPort("myBS");
    BuilderService bs = (BuilderService)p;
  }
}
