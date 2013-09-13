/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sky4s.rainalarm;

import java.awt.image.BufferedImage;
import java.awt.image.DataBuffer;
import java.awt.image.DataBufferByte;
import java.awt.image.DataBufferInt;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import javax.net.ssl.*;

class DateTask extends TimerTask {

    private String prefilename;

    @Override
    public void run() {
        try {
            System.out.println("任務時間：" + new Date());

            URL website = new URL("https://alerts.ncdr.nat.gov.tw/data/data.ashx%5C8");
            String filename = System.currentTimeMillis() + ".png";
            try (ReadableByteChannel rbc = Channels.newChannel(website.openStream()); FileOutputStream fos = new FileOutputStream(filename)) {
                fos.getChannel().transferFrom(rbc, 0, Long.MAX_VALUE);
            }

            if (null != prefilename) {
                File nowfile = new File(filename);
                FileInputStream nowfis = new FileInputStream(nowfile);
                FileInputStream prefis = new FileInputStream(new File(prefilename));
                BufferedImage nowimage = ImageUtils.loadImage(filename);
                BufferedImage preimage = ImageUtils.loadImage(prefilename);

                if (nowfis.available() == prefis.available() || ImageUtils.compare(nowimage, preimage)) {
                    nowfis.close();
                    nowfile.delete();
                    System.out.println("delete " + filename);
                } else {
                    prefilename = filename;
                }
            } else {
                prefilename = filename;
            }

        } catch (MalformedURLException ex) {
            Logger.getLogger(DateTask.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(DateTask.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

/**
 *
 * @author SkyforceShen
 */
public class RadarFetcher {

    static TrustManager[] trustAllCerts = new TrustManager[]{new X509TrustManager() {
            @Override
            public java.security.cert.X509Certificate[] getAcceptedIssuers() {

                return null;

            }

            @Override
            public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) {
            }

            @Override
            public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) {
            }
        }};

    public static void main(String[] args) throws NoSuchAlgorithmException, KeyManagementException {
        SSLContext sc = SSLContext.getInstance("SSL");

        sc.init(null, trustAllCerts, new java.security.SecureRandom());

        HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
//        Properties systemProperties = System.getProperties();
//        systemProperties.setProperty("http.proxyHost", "localhost");
//        systemProperties.setProperty("http.proxyPort", "8080");
//        systemProperties.setProperty("https.proxyHost", "localhost");
//        systemProperties.setProperty("https.proxyPort", "8080");

        Timer timer = new Timer();
        long period = 240000;
        timer.schedule(new DateTask(), 0, period);
        System.out.println("現在時間：" + new Date());

//        try {
//            Thread.sleep(20000);
//        } catch (InterruptedException e) {
//        }
//
//        timer.cancel();
    }
}

final class ImageUtils {

    public static boolean compare(BufferedImage imagea, BufferedImage imageb) {
        DataBuffer dbActual = imagea.getRaster().getDataBuffer();
        DataBuffer dbExpected = imageb.getRaster().getDataBuffer();
        DataBufferByte actualDBAsDBInt = (DataBufferByte) dbActual;
        DataBufferByte expectedDBAsDBInt = (DataBufferByte) dbExpected;

        for (int bank = 0; bank < actualDBAsDBInt.getNumBanks(); bank++) {
//            int[] actual = actualDBAsDBInt.getData(bank);
//            int[] expected = expectedDBAsDBInt.getData(bank);
            byte[] actual = actualDBAsDBInt.getData(bank);
            byte[] expected = expectedDBAsDBInt.getData(bank);

            // this line may vary depending on your test framework
//   assertTrue(Arrays.equals(actual, expected));
            if (!Arrays.equals(actual, expected)) {
                return false;
            }
        }
        return true;
    }

    public static BufferedImage loadImage(String filename) throws
            IOException {
//    PlanarImage planar = JAI.create("FileLoad", filename);
//    return planar.getAsBufferedImage();
        BufferedImage image = ImageIO.read(new File(filename));
        return image;
    }
}