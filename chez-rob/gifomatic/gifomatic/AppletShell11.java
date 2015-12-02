package gov.sandia.gifomatic;

import java.applet.Applet;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.PrintStream;
import java.net.URL;


class FreqMonitor implements ActionListener {
  private int freq;
  private TextField tf;
  private GifGrabber11 g;
  private boolean debug = true;

  FreqMonitor(TextField tf, GifGrabber11 g) {
    this.tf = tf;
    this.g = g;
  }
  public void actionPerformed(ActionEvent e) {
    int interval = 1;

    String s = tf.getText();
    trace("paramString ="+s);
    try {
    interval = Integer.parseInt(s);
    } catch(Exception ee) {
      return;
    }
    g.setInterval(interval);
  }
  public void trace(String message)
  {
    if(debug)
      System.out.println(message);
  }
}

public class AppletShell11 extends Applet {
  private Image img;
  private boolean debug;
  private GifGrabber11 grabber;
  private int tSliceImg;
  private URL ImgURL;

  public AppletShell11(){}
  public void init()
  {
    debug = true;
    if(getParameterString("Trace") != null)
      debug = true;
    trace("Init called");
    try {
      String urlImgStr = getParameterString("ImageURL");
      if(urlImgStr == null)
	{
	  showStatus("No URL for image supplied");
	  trace("No URL for image supplied");
	  return;
	}
      showStatus("Img URL: "+ urlImgStr);
      ImgURL = new URL(urlImgStr);
    } catch(Exception e) {
      showStatus("Problem with the image URL");
      e.printStackTrace(System.err);
      trace(e.toString());
      return;
    }
    try {
	tSliceImg = Integer.parseInt(getParameterString("ImgInterval"));
	trace("Img time Interval =" + tSliceImg);
      } catch(Exception e) {
	showStatus("No time interval for HTML or Image");
	e.printStackTrace(System.err);
	trace(e.toString());
	return;
      }
    try {
	trace("Target Image URL=" + ImgURL.toString());
	img = getImage(ImgURL);
	MediaTracker mediaTracker_track = new MediaTracker(this);
	mediaTracker_track.addImage(img, 1);
	mediaTracker_track.waitForID(1);
      } catch(Exception e) {
	showStatus("Problem getting initial image: " + e.toString());
	e.printStackTrace(System.err);
	trace("Image get exception:" + e.toString());
	return;
      }
    GifGrabber11 g = new GifGrabber11(img, tSliceImg, debug);
    add(g);
    Label l = new Label("update freq. (sec)");
    TextField tf = new TextField(5);
    tf.addActionListener(new FreqMonitor(tf, g));
    add(l);
    add(tf);
    Thread t = new Thread(g);
    t.start();
  }

  /** Get a parameter necessary for configuring the Grabber.  This
      insulates us from needing to know whether we are a plug-in
      applet or a garden variety applet. */
  public String getParameterString(String key) {
    return this.getParameter(key);
  }
  public void trace(String message)
  {
    if(debug)
      System.out.println(message);
  }
}
