/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

import java.util.Arrays;

/**
 *
 * @author SkyforceShen
 */
public class REvaluator {

    static int search(int[] array, int value) {
        int index = Arrays.binarySearch(array, value);
        if (index < -1) {
            return -index - 2;
        } else {
            return index;
        }
    }

    public static void main(String[] args) {
        int[] layers = new int[]{0, 102, 307, 716, 1023};
//        int index = search(layers, 308);
        int myErrorCount = 0;
        int iiErrorCount = 0;
        int totalCount = 0;

        int[] myErrorArray = new int[25];
        int[] iiErrorArray = new int[25];
//        int[] grayLevelCount = new int[1024];
        int compareBit = 12;

        for (int r = 1; r < 1023; r++) {
            int R0Index = search(layers, r);
            for (int c1 = 1; c1 < 4096; c1++) {

                //=========================================================================
                // my
                //=========================================================================
                //10
                int R_R0 = r - layers[R0Index];
                //10 x 12 = 22
                int my1 = R_R0 * c1;
                //10
                int R1_R0 = layers[R0Index + 1] - layers[R0Index];
                //23
                int my2 = my1 << (compareBit - 12);
                //23-10=13
                int my3 = my2 / R1_R0;
                //13
                int my = my3;
                //=========================================================================

                //=========================================================================
                //float
                //=========================================================================
                double ff1 = ((double) R_R0) / R1_R0;
                double ff2 = c1 * ff1;
                double ff3 = ff2 * Math.pow(2, compareBit - 12);
                int ff = (int) ff3;
                //=========================================================================


                //=========================================================================
                //ii
                //=========================================================================
                //20
//                int R_R0_10 = R_R0 << 10;
//                //20-10=10
//                int ii1 = R_R0_10 / R1_R0;
//                //12*10=22
//                int ii2 = c1 * ii1;
//                int ii = ii2 >> 10;

                //21
                int shift = 22;
                //10+22=32
                long R_R0_10 = R_R0 << shift;
                //32-10=22
                long ii1 = R_R0_10 / R1_R0;
                //12*22=34
                long ii2 = c1 * ii1;
                //34-22=12
                long ii = ii2 >> (shift - (compareBit - 12));
                //=========================================================================

                totalCount++;
                if (ff != my) {
                    myErrorCount++;
                    int error = Math.abs(ff - my);
                    myErrorArray[error]++;

//                    System.out.println("r:" + r + " c1 " + c1 + " ff " + ff + " my" + my);
                }
                if (ff != ii) {
                    iiErrorCount++;
                    int error = (int) Math.abs(ff - ii);
                    iiErrorArray[error]++;
                    if (error > 5 && c1 < 3000) {
                        int a = 1;
                    }
//                    System.out.println("r:" + r + " c1 " + c1 + " ff " + ff + " my" + my + " ii" + ii);
                }
                int index = my >> 3;
//                grayLevelCount[index]++;
            }

        }
        System.out.println("myErrorCount:\t" + myErrorCount);
        System.out.println("iiErrorCount:\t" + iiErrorCount);
        System.out.println("totalCount:\t" + totalCount);

        System.out.println("my: " + Arrays.toString(myErrorArray));
        System.out.println("ii: " + Arrays.toString(iiErrorArray));

//        System.out.println(Arrays.toString(grayLevelCount));
    }
}
