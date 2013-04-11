/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

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

    static int getTetradedral(byte fx6bit, byte fy6bit, int fz, int fzBit) {
        int gain = (int) Math.pow(2, fzBit - 6);
        int fx = fx6bit * gain;
        int fy = fy6bit * gain;
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

    static int getTetradedral(byte fx6bit, byte fy6bit, double fz) {
        double one = Math.pow(2, 6);
        double fx = fx6bit / one;
        double fy = fy6bit / one;
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
        int fzBit = 6;
        byte one6bit = (byte) (Math.pow(2, 6));
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

                byte fx = (byte) (x * one6bit / h);
                byte fy = (byte) (y * one6bit / v);

                for (short level = shortLevel; level < delta; level++) {
//                for (short level = 1; level < delta; level++) {
                    short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));

                    int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
//                    System.out.println(fx+" "+fy+" "+fz);
                    int tInteger = getTetradedral(fx, fy, fz, fzBit);
                    double dfz = ((double) level) / delta;
                    int tDouble = getTetradedral(fx, fy, dfz);
                    if (tInteger != tDouble) {
                        System.out.println("y: " + y + " x: " + x + " l: " + level + " => " + tInteger + " " + tDouble);
                        errorTCount++;
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

    public static void main(String[] args) {
        //00,10,01,11
        short[] R0 = new short[]{-128, -128, -128, -128};
        short[] R1 = new short[]{127, 127, 127, 127};

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
