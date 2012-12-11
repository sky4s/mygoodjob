/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dashboard;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.Stroke;
import javax.swing.JComponent;

/**
 *
 * @author SkyforceShen
 */
public class DashboardCanvas
        extends JComponent implements Runnable {

    public void run() {
        while (true) {
            if (initGraphics2D) {
                gOffScreen.drawImage(baseScreen, 0, 0, this);
                drawDashboard((Graphics2D) gOffScreen);

                repaint();  // 重繪畫面
            }
            try {
                Thread.sleep(16);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private void drawDashboard(Graphics2D g) {
    }

    DashboardCanvas() {
        (new Thread(this)).start();
    }
//    private BufferedImage img;
    private boolean initGraphics2D = false;
    private Image offScreen;
    private Graphics gOffScreen;
    private Image baseScreen;

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (!initGraphics2D) {
            baseScreen = createImage(getWidth(), getHeight());
            drawBase(baseScreen.getGraphics());
            offScreen = createImage(getWidth(), getHeight());
            gOffScreen = offScreen.getGraphics();
            initGraphics2D = true;
        }
        g.drawImage(offScreen, 0, 0, this);
    }
//    private Dimension size;

    private void initGraphics2D(Graphics2D g2d) {
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, // Anti-alias!
                RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHint(RenderingHints.KEY_COLOR_RENDERING, // Anti-alias!
                RenderingHints.VALUE_COLOR_RENDER_QUALITY);
        g2d.setRenderingHint(RenderingHints.KEY_RENDERING, // Anti-alias!
                RenderingHints.VALUE_RENDER_QUALITY);
    }

    private void drawBase(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        initGraphics2D(g2d);

        Dimension size = this.getSize();
        int w = size.width;
        int h = size.height;
        g.setColor(Color.black);
        g.fillRect(0, 0, w, h);

        g.setColor(Color.lightGray);
        int strokeWidth = 10;
        int length = Math.min(w, h);
        length -= strokeWidth;
        int y = strokeWidth / 2;
        Stroke stroke = new BasicStroke(strokeWidth);
        g2d.setStroke(stroke);
        g.drawOval(w / 2 - length / 2, y, length, length);
    }

    static double[] toPolarCoordinates(int x, int y) {
        double r = Math.sqrt(x * x + y * y);
        double theta = Math.atan2(y, x);
        return new double[]{r, theta};
    }

    static double[] toCartesianCoordinates(double r, double theta) {
        double x = r * Math.cos(theta);
        double y = r * Math.sin(theta);
        return new double[]{x, y};
    }

    public void update(Graphics g) {
        paint(g);
    }
}

class CoordinateSystemMapper {
    private double anglecount;
    private double anglepiece;
    
    public CoordinateSystemMapper(int anglecount){
        this.anglecount=anglecount;
        anglepiece=360/anglecount;
    }
}