/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dashboard.test;

/**
 *
 * @author SkyforceShen
 */
import java.awt.*;
import javax.swing.JApplet;

import static java.lang.Math.*;

public class Firework extends JApplet implements Runnable {

    private final int MAX = 200;
    private FireworkParticle[] particles; // 煙火粒子
    private int xCenter, yCenter;
    private Image offScreen;
    private Graphics gOffScreen;

    public void init() {
        setSize(640, 480);
        setBackground(Color.black); // 背景為黑色
        particles = new FireworkParticle[MAX]; // 建立粒子

        // 煙火初始位置
        xCenter = (int) (getWidth() / 2 + random() * 150 - 150);
        yCenter = (int) (getHeight() / 2 + random() * 150 - 150);
        for (int i = 0; i < MAX; i++) {
            particles[i] = new FireworkParticle();
        }

        // 建立次畫面
        offScreen = createImage(getWidth(), getHeight());
        gOffScreen = offScreen.getGraphics();
    }

    public void start() {
        (new Thread(this)).start();
    }

    public void update(Graphics g) {
        paint(g);
    }

    public void paint(Graphics g) {
        g.drawImage(offScreen, 0, 0, this);
    }

    public void run() {
        while (true) {
            boolean replay = true;
            for (FireworkParticle particle : particles) {
                if (particle.isAlive()) {
                    replay = false;
                    break;
                }
            }
            // 是否重新施放
            if (replay) {
                for (FireworkParticle particle : particles) {
                    particle.resume(xCenter, yCenter, MAX);
                    particle.setLife((int) (random() * 20));
                }
            }
            gOffScreen.clearRect(0, 0, getWidth(), getHeight());
            for (FireworkParticle particle : particles) {
                if (particle.isAlive()) {
                    double x = particle.getPoint().getX();
                    double y = particle.getPoint().getY();
                    gOffScreen.setColor(particle.getColor());
                    gOffScreen.fillOval((int) x, (int) y, 3, 3);
                    particle.nextState();
                }
            }

            // 重繪畫面
            repaint();

            // 暫停執行緒 150 毫秒
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
                e.printStackTrace();
//                context.stroke();
            }
        }
    }
}

class FireworkParticle {

    private final static Color LIFE_LESS_5 = new Color(255, 0, 0);
    private final static Color LIFE_LESS_2 = new Color(0, 0, 255);
    private Point position = new Point();  // 粒子的位置
    private double vx, vy;   // 粒子的速度
    private int life;       // 粒子的生命值
    private Color color; // 粒子的顏色
    private int time;  // 粒子存活至今的時間

    void resume(int x, int y, int max) {
        position.setLocation(x, y);
        vx = random() * max - random() * max;
        vy = random() * max - random() * max;
        color = new Color((int) (random() * 255),
                (int) (random() * 255),
                (int) (random() * 255));
        time = 0;
    }

    void setLife(int life) {
        this.life = life;
    }

    boolean isAlive() {
        return life != 0;
    }

    Point getPoint() {
        return position;
    }

    Color getColor() {
        return color;
    }

    void nextState() {
        vy += 9.8 * time;
        position.setLocation(
                position.getX() + vx * 0.1,
                position.getY() + vy * 0.1);
        life--;
        time++;
        if (life < 2) {
            color = LIFE_LESS_2;
        } else if (life < 5) {
            color = LIFE_LESS_5;
        }
    }
}