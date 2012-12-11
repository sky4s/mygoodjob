/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dashboard.test;

import javax.swing.JApplet;
import java.awt.*;

// 立方體類別
class Point {

    public final double x, y, z;

    public Point(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
}

class Cubic {

    public final static int NFC = 6;        // 平面數量
    public final static int NVT = 8;        // 頂點的數量
    public final static int NVT_F = 4;        // 1個平面的頂點數
    public Point[] vt;   // 頂點的座標
    public int[][] ord;    // 頂點索引

    public Cubic(int r) {
        vt = new Point[NVT];
        double sq3 = Math.sqrt(3.0);
        vt[0] = new Point(r / sq3, r / sq3, r / sq3);
        vt[1] = new Point(r / sq3, r / sq3, -r / sq3);
        vt[2] = new Point(-r / sq3, r / sq3, -r / sq3);
        vt[3] = new Point(-r / sq3, r / sq3, r / sq3);

        for (int i = 0; i < NVT / 2; i++) {
            vt[NVT / 2 + i] = new Point(-vt[i].x, -vt[i].y, -vt[i].z);
        }

        int[][] initOrd = {{0, 1, 2, 3}, {0, 3, 5, 6}, {0, 6, 7, 1},
            {4, 7, 6, 5}, {4, 2, 1, 7}, {4, 5, 3, 2}};

        ord = new int[NFC][NVT_F];
        for (int i = 0; i < NFC; i++) {
            for (int j = 0; j < NVT_F; j++) {
                ord[i][j] = initOrd[i][j];
            }
        }
    }
}

public class DoubleBuffer extends JApplet implements Runnable {

    private Image offScreen;
    private Graphics gOffScreen;
    private int orgX, orgY;
    private Cubic cubic = new Cubic(100);

    public void init() {
        setBackground(Color.black);
        orgX = getWidth() / 2;
        orgY = getHeight() / 2;
        offScreen = createImage(getWidth(), getHeight());
        gOffScreen = offScreen.getGraphics();
        gOffScreen.setColor(Color.yellow);
    }

    public void start() {
        (new Thread(this)).start();
    }

    public void run() {
        // 旋轉以斜角繪製圖形
        double sinAx = Math.sin(Math.toRadians(30));
        double cosAx = Math.cos(Math.toRadians(30));

        double[] cosAys = new double[360];
        double[] sinAys = new double[360];
        for (int i = 0; i < 360; i++) {
            cosAys[i] = Math.cos(Math.toRadians(i));
            sinAys[i] = Math.sin(Math.toRadians(i));
        }

        int angle = 330;
        double sinAy = sinAys[angle];
        double cosAy = cosAys[angle];

        Point[] tp = new Point[4];
        int[] px = new int[4];
        int[] py = new int[4];
        // 動畫迴圈
        while (true) {
            gOffScreen.clearRect(0, 0, getWidth(), getHeight());
            for (int i = 0; i < Cubic.NFC; i++) {
                for (int j = 0; j < Cubic.NVT_F; j++) {
                    // 利用索引array取出正確的頂點
                    tp[j] = cubic.vt[cubic.ord[i][j]];

                    // 旋轉以斜角繪製圖形
                    px[j] = (int) (tp[j].x * cosAy + tp[j].z * sinAy);
                    py[j] = (int) (tp[j].y * cosAx
                            - (-tp[j].x * sinAy + tp[j].z * cosAy) * sinAx);
                    px[j] = px[j] + orgX;
                    py[j] = -py[j] + orgY;
                }

                // 在緩衝區上縮圖
                gOffScreen.drawPolyline(px, py, 4);
            }
            repaint();  // 重繪畫面
            // 暫停 20 毫秒
            try {
                Thread.sleep(20);
//                Thread.sleep(8);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // 繞 y 軸轉動
            angle = (angle + 1) % 360;
            sinAy = sinAys[angle];
            cosAy = cosAys[angle];
        }
    }

    // 重新定義update()
    public void update(Graphics g) {
        paint(g);
    }

    public void paint(Graphics g) {
        // 將緩衝區畫面繪到前景
        g.drawImage(offScreen, 0, 0, this);
    }
}