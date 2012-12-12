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
//        double[] polar = toPolarCoordinates(0, length);
        double[] polar=cartesian2polarCoordinatesValues(new double[]{0,length});
//        double[] xy = toCartesianCoordinates(polar[0], polar[1]);
        int a = 1;
    }

    public static final double[] cartesian2polarCoordinatesValues(final double[] cartesianValues) {
        double[] polarValues = new double[2];

//    polarValues[0] = cartesianValues[0];
        double t1 = cartesianValues[0];
        double t2 = cartesianValues[1];
        polarValues[0] = Math.sqrt(Math.pow(cartesianValues[0], 2)
                + Math.pow(cartesianValues[1], 2));
        if (t1 == 0 && t2 == 0) {
            polarValues[1] = 0;
        } else {
            polarValues[1] = Math.atan2(t2, t1);
        }
        polarValues[1] *= (180.0 / Math.PI);
        while (polarValues[1] >= 360.0) { // Not necessary, but included as a check.
            polarValues[1] -= 360.0;
        }
        while (polarValues[1] < 0) {
            polarValues[1] += 360.0;
        }
        return polarValues;
    }

    /**
     * 極座標=>笛卡兒座標
     *
     * @param polarValues double[]
     * @return double[]
     */
    public static final double[] polar2cartesianCoordinatesValues(final double[] polarValues) {
        double t = (polarValues[1] * Math.PI) / 180.0;

        double[] cartesianValues = new double[2];
        cartesianValues[0] = polarValues[0] * Math.cos(t);
        cartesianValues[1] = polarValues[0] * Math.sin(t);

        return cartesianValues;
    }

 
    public void update(Graphics g) {
        paint(g);
    }
}

class CoordinateSystemMapper {

    private double anglecount;
    private double anglepiece;

    public CoordinateSystemMapper(int anglecount) {
        this.anglecount = anglecount;
        anglepiece = 360. / anglecount;
    }
}