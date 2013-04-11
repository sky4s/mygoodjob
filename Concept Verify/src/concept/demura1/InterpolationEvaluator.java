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
public class InterpolationEvaluator {

    static short[] getS1234(int h, int v, int x, int y) {
        short[] result = new short[]{
            (short) (x * y),
            (short) ((h - x) * y),
            (short) (x * (v - y)),
            (short) ((h - x) * (v - y))
        };
        return result;
    }

    static short getDeMuravalue(short[] S, short[] R) {
        return (short) ((S[3] * R[0] + S[2] * R[1] + S[1] * R[2] + S[0] * R[3]) / 64);
//        short[] result = new short[2];
//        result [0]= S1234[3]*R[0]
//        return result;
    }

    static int getTetradedral(byte fxbit, byte fybit, int fxyBitnum, int fz, int fzBitnum) {
        int gain = (int) Math.pow(2, fzBitnum - fxyBitnum);
        int fx = fxbit * gain;
        int fy = fybit * gain;
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

    static int getTetradedral(byte fxbit, byte fybit, int fxyBitnum, double fz) {
        double one = Math.pow(2, fxyBitnum);
        double fx = fxbit / one;
        double fy = fybit / one;
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

    static boolean evaluate(short[] R0, short[] R1, short v, short h, short delta) {
        short coef = (short) Math.round(Math.pow(2, 16) / delta);
        int fzBit = 4;
        int fxyBit = 4;
        byte onexy = (byte) (Math.pow(2, fxyBit));
        int totalCount = 0;
        int errorTCount = 0;
        int errorValueCount = 0;

//        short shortLevel = (short) (delta - 1);
        short shortLevel = 1;

        for (int y = 0; y < v; y++) {
            for (int x = 0; x < h; x++) {
                short[] S1234 = getS1234(h, v, x, y);
                short c0 = getDeMuravalue(S1234, R0);
                short c1 = getDeMuravalue(S1234, R1);

                byte fx = (byte) (x * onexy / h);
                byte fy = (byte) (y * onexy / v);

                for (short level = shortLevel; level < delta; level++) {
//                for (short level = 1; level < delta; level++) {
                    short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));

                    int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
//                    System.out.println(fx+" "+fy+" "+fz);
                    int tInteger = getTetradedral(fx, fy, fxyBit, fz, fzBit);
                    double dfz = ((double) level) / delta;
                    int tDouble = getTetradedral(fx, fy, fxyBit, dfz);
                    if (tInteger != tDouble) {
                        System.out.println("y: " + y + " x: " + x + " l: " + level + " => " + tInteger + " " + tDouble);
                        errorTCount++;
                    }
                    double dfx = ((double) x) / h;
                    double dfy = ((double) y) / v;
                    double dtetrahedralValue = tetrahedral(tInteger, R0, R1, dfx, dfy, dfz);
                    if (dtetrahedralValue != linearValue) {
//                        System.out.println(linearValue + " " + dtetrahedralValue);
                    }
                    totalCount++;
                }
            }
        }
        if (errorTCount != 0 || errorValueCount != 0) {
            System.out.println("v: " + v + " h:" + h + " delta:" + delta);
            System.out.println("errorT:" + errorTCount + " errorV:" + errorValueCount + " / " + totalCount);
            return false;
        }
        return true;
    }

    static double tetrahedral(int tetradedralIndex, short[] R0, short[] R1, double fx, double fy, double fz) {
        short[] c = getc123(tetradedralIndex, R0, R1);
//        System.out.println(Arrays.toString(c));
        double result = R0[0] + c[0] * fx + c[1] * fy + c[2] * fz;
        return result;
    }

    static short tetrahedral(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fz, int fzBitnum) {
        //short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
        short[] c123 = getc123(tetradedralIndex, R0, R1);//8bit
        return -1;
    }

    static short p(int x, int y, short[] R) {
        //00,10,01,11
        int index = ((x != 0) ? 1 : 0) + ((y != 0) ? 2 : 0);
        return R[index];
    }

    static short[] getc123(int tetradedralIndex, short[] R0, short[] R1) {
        //00,10,01,11
        switch (tetradedralIndex) {
            case 1:
                return new short[]{
                            (short) (p(1, 0, R0) - p(0, 0, R0)),
                            (short) (p(1, 1, R0) - p(1, 0, R0)),
                            (short) (p(1, 1, R1) - p(1, 1, R0))};
            case 2:
                return new short[]{
                            (short) (p(1, 0, R0) - p(0, 0, R0)),
                            (short) (p(1, 1, R1) - p(1, 0, R1)),
                            (short) (p(1, 0, R1) - p(1, 0, R0))};
            case 3:
                return new short[]{
                            (short) (p(1, 0, R1) - p(0, 0, R1)),
                            (short) (p(1, 1, R1) - p(1, 0, R1)),
                            (short) (p(0, 0, R1) - p(0, 0, R0))};
            case 4:
                return new short[]{
                            (short) (p(1, 1, R0) - p(0, 1, R0)),
                            (short) (p(0, 1, R0) - p(0, 0, R0)),
                            (short) (p(1, 1, R1) - p(1, 1, R0))};
            case 5:
                return new short[]{
                            (short) (p(1, 1, R1) - p(0, 1, R1)),
                            (short) (p(0, 1, R0) - p(0, 0, R0)),
                            (short) (p(0, 1, R1) - p(0, 1, R0))};
            case 6:
                return new short[]{
                            (short) (p(1, 1, R1) - p(0, 1, R1)),
                            (short) (p(0, 1, R1) - p(0, 0, R1)),
                            (short) (p(0, 0, R1) - p(0, 0, R0))};

        }
        return null;
    }

    public static void main(String[] args) {
        //00,10,01,11
        short[] R0 = new short[]{-128, -128, -128, -128};
        short[] R1 = new short[]{127, 127, 127, 127};

//        short[] R = new short[]{1, 2, 3, 4};
//        getP(R, 0, 0);
//        getP(R, 1, 0);
//        getP(R, 0, 1);
//        getP(R, 1, 1);

//        short delta = 102;
//        short v = 4, h = 16;



        short[][] vhs = {{4, 16}, {8, 8}, {16, 4}};
//        short[][] vhs = {{4, 16}};

        int deltaStart = (int) Math.round(1023 * 0.1);
        int deltaEnd = 511;//(int) Math.round(1023 * 0.5);
//        int deltaEnd = deltaStart;
        for (short[] vh : vhs) {
            for (int delta = deltaStart; delta <= deltaEnd; delta++) {

                if (!evaluate(R0, R1, vh[0], vh[1], (short) delta)) {
                    System.out.println("v:" + vh[0] + " h:" + vh[1] + " delta:" + delta);
                }
            }
        }


    }
}
