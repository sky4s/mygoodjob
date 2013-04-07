/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept;

/**
 *
 * @author Skyforce
 */
public class Tetrahedron {

    public static void main(String[] args) {
        int[] blocks = new int[]{4, 6, 8, 12, 16, 20, 24, 28, 30, 32, 36, 40, 48, 64};
//        int[] blocks = new int[]{6};
        //p000+c1*fx+c2*fy+c3*fz
        //fx = (x-x0)/(x1-x0)
        int errorcount = 0;
        int totalcount = 0;
        int jjbit = 21;

        for (int c1 = 1; c1 < 1024; c1++) {
//        for (int c1 = 511; c1 < 515; c1++) {
            for (int block : blocks) {
                for (int b = 0; b < block; b++) {
                    double f = c1 * (((double) b) / block);
                    double tempf = f * 4;
                    int ff = (int) tempf;

                    //c1 10bit, b 6bit
                    int my1 = (c1 * b) & 65535;
//                    int my = my1 / block;
//                    my = my << 2;
                    //18bit / 6bit
                    int my = (my1 << 2) / block;
                    my = my & 4095;

                    double jjf = ((double) b) / block;
//                    int jj1 = (int) Math.round((Math.pow(2, 20)) * jjf); //20bit
                    int jj1 = (int) ((Math.pow(2, jjbit)) * jjf); //20bit
                    long jj = c1 * jj1; //30bit
                    jj = jj >> (jjbit + 10 - 12);
//                        int jj1 = 

                    if (jj < 0) {
                        long q = c1 * jj1;
                        int a = 1;

                    }
//                    if (jj != my) {
//                        errorcount++;
//                        System.out.println(b + "/" + block + ": jj" + jj + " my" + my + " ff" + ff);
//                    }

                    if (ff != my) {
                        errorcount++;
                        System.out.println(b + "/" + block + ": " + c1 + " " + ff + " " + my);
                    }
                    totalcount++;

                }
            }
        }

        System.out.println(errorcount + "/" + totalcount);
//        for(int )
    }
}
