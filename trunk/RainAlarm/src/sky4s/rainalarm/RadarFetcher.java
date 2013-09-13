/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sky4s.rainalarm;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.MalformedURLException;
import java.net.Proxy;
import java.net.URL;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
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
                if (nowfis.available() == prefis.available()) {
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
