/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

/**
 *
 * @author Skyforce
 */
public class Tetrahedron {

    public static void main(String[] args) {
//        int[] blocks = new int[]{4, 6, 8, 12, 16, 20, 24, 28, 30, 32, 36, 40, 48, 64};
//        int[] blocks = new int[]{4, 8, 12, 16, 20, 24, 28, 30, 32, 48, 54, 64};
        int[] blocks = new int[]{20};
        int[] blockError = new int[blocks.length];
//        int[] blocks = new int[]{6};
        //p000+c1*fx+c2*fy+c3*fz
        //fx = (x-x0)/(x1-x0)
        int errorcount = 0;
        int totalcount = 0;
//        int jjbit = 21;
//        boolean round = true;
        boolean round = false;
        boolean jjfix = true;
        boolean jjfix2 = true;
        int jjbit = 16;

        for (int c1 = 1; c1 < 4096; c1++) {
//  for (int c1 = 4095; c1 < 4096; c1++) {
//        for (int c1 = 1; c1 < 1024; c1++) {
//        for (int c1 = 511; c1 < 515; c1++) {
            int blockIndex = 0;
            for (int block : blocks) {
                for (int b = 0; b < block; b++) {
//                    double part = ((double) b) / (block - 1);
                    double part = ((double) b) / (block);
                    double ff1 = c1 * part;
//                    double ff2 = ff1 * 4;


                    //c1 12bit, b 6bit
                    int my1 = (c1 * b) & 262143;
                    //18bit / 6bit
//                    int my2 = (my1 << 3) / block;
                    // 18+1/6 = 13
                    int my2 = my1 << 1;
                    int my3 = (my2) / block;
                    if (round) {
                        my3 += 1;
                    }
                    //12
                    int my4 = my3 >> 1;

                    //21/20
                    int b10 = jjfix ? b << jjbit : b << 10;
                    // 21/10 11,  20/10 =10
                    int jj1 = b10 / block;
//                    if (jjfix) {
//                        jj1 += 1;
//                        jj1 = jj1 >> 1;
//                    }
                    //10bit
//                    int jj2 = jj1 & 1023;
                    int jj2 = jj1;
                    //12bit x 10bit =22bit
                    //12bit x 11bit =23bit
                    int jj3 = c1 * jj2;
                    if (jjfix2) {
                        jj3 += 1;
                    }


//                    int ff = (int) ff2;
                    int ff = (int) (round ? Math.round(ff1) : ff1);
//                    int ff = (int) Math.round(ff1);

                    int my = my4 & 4095;
                    //22bit-10=12
//                      int jj = jj3 >> 10;
                    int jj = jjfix ? jj3 >> jjbit : jj3 >> 10;

//                      if (ff != jj || ff != my) {
//                    if (ff != jj && ff != my) {
                    if (ff != jj) {
//                    if (ff != my) {
                        errorcount++;
                        blockError[blockIndex]++;
                        System.out.println(b + "/" + block + ": c1 " + c1 + " ff" + ff + " my" + my + " jj" + jj);
                    }
//                    System.out.println(c1+" "+ff);
//                    System.out.println(b + "/" + block + ": c1" + c1 + " ff" + ff + " my" + my + " jj" + jj);
                    totalcount++;

                }
                blockIndex++;
            }
        }

        System.out.println(errorcount + "/" + totalcount);
        for (int x = 0; x < blocks.length; x++) {
            System.out.println(blocks[x] + " " + blockError[x]);
        }
//        for(int )
    }
}
