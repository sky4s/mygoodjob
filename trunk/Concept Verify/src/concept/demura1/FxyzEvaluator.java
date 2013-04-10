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
public class FxyzEvaluator {

    static int search(int[] array, int value) {
        int index = Arrays.binarySearch(array, value);
        if (index < -1) {
            return -index - 2;
        } else {
            return index;
        }
    }

    static int getTetradedral(double fx, double fy, double fz) {
        if (fx >= fy && fy > fz) {
            return 1;
        } else if (fx > fz && fz >= fy) {
            return 2;
        } else if (fz >= fx && fx >= fy) {
            return 3;
        } else if (fy > fx && fx > fz) {
            return 4;
        } else if (fy > fz && fz >= fx) {
            return 5;
        } else if (fz >= fy && fy > fx) {
            return 6;
        } else {
            return -1;
        }
    }

    public static void main(String[] args) {
        int[] layers = new int[]{0, 102, 307, 716, 1023};
        int[] blocks = new int[]{4, 8, 12, 16, 20, 24, 28, 30, 32, 48, 54, 64};
        int RBitshift = 15;
        int blockBitshift = 15;
        int blockDeltaShift = RBitshift - blockBitshift;
        int RDeltaShift = -blockDeltaShift;
          blockDeltaShift = (blockDeltaShift < 0) ? 0 : blockDeltaShift;
        RDeltaShift = (RDeltaShift < 0) ? 0 : RDeltaShift;
//        int RBitshift = 10;

        int casecount = 0;
        int errorcount = 0;


        for (int h1 : blocks) {
            for (int v1 : blocks) {
                for (int h = 1; h < h1; h++) {
                    for (int v = 1; v < v1; v++) {
                        for (int r = 1; r < 1023; r++) {
//                        for (int r = 101; r < 102; r++) {
                            int r0index = search(layers, r);
                            int r1_r0 = layers[r0index + 1] - layers[r0index];
                            int r_r0 = r - layers[r0index];
                            int r_r0_10 = r_r0 << RBitshift; //10+15=25 測試 
                            int fr = r_r0_10 / r1_r0; //25-10=15
                            fr = fr << RDeltaShift;

                            int h_10 = h << blockBitshift;
                            int fh1 = h_10 / h1;
                            int fh = fh1 << blockDeltaShift;


                            int v_10 = v << blockBitshift;
                            int fv1 = v_10 / v1;
                            int fv = fv1 << blockDeltaShift;

                            double dfr = ((double) r_r0) / r1_r0;
                            double dfh = ((double) h) / h1;
                            double dfv = ((double) v) / v1;

                            int t0 = getTetradedral(fh, fv, fr);
                            int t1 = getTetradedral(dfh, dfv, dfr);
                            casecount++;

                            if (t0 != t1) {
                                int a = 1;
                                errorcount++;
//System.out.println(t1 + "->" + t0);
                                int dt = t1 - t0;
                                if (dt > 1) {
//                                    System.out.println(t1 + "->" + t0);
                                }
                            }
                        }
                    }
                }
            }
        }
        System.out.println("errorcount:\t" + errorcount);
        System.out.println("casecount:\t" + casecount);
    }
}
