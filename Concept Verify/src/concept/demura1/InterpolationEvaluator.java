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
            (short) (x * y), //4+4=8
            (short) ((h - x) * y),
            (short) (x * (v - y)),
            (short) ((h - x) * (v - y))
        };
        return result;
    }

    static short getDeMuravalue(short[] S, short[] R, int vxh) {
        //s:8bit
        //8+8 - 6 = 10?
        return (short) ((S[3] * R[0] + S[2] * R[1] + S[1] * R[2] + S[0] * R[3]) / vxh);
//        short[] result = new short[2];
//        result [0]= S1234[3]*R[0]
//        return result;
    }

    static int getTetrahedral(byte fxbit, byte fybit, int fxyBitnum, int fz, int fzBitnum) {
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
//    static short[] c0c1 = new short[2];

    static boolean evaluate(short[] R0, short[] R1, short v, short h, short delta) {
        short coef = (short) Math.round(Math.pow(2, 16) / delta); //16-9 = 7
        int fzBit = 9;
        int fxyBit = 4;
        byte onexy = (byte) (Math.pow(2, fxyBit));
        int totalCount = 0;
        int errorTCount = 0;
        int errorValueCount = 0;

        short shortLevel = (short) (delta - 1);
//        short shortLevel = 1;
//        short shortLevel = 0;

//        int starty = v - 1;
//        int startx = h - 1;
        int starty = 0;
        int startx = 0;
//        
        int vxh = v * h;

        for (int y = starty; y < v; y++) {
            for (int x = startx; x < h; x++) {

//        for (int y = 0; y < 1; y++) {
//            for (int x = 0; x < 1; x++) {

                short[] S1234 = getS1234(h, v, x, y); //8bit  
//                System.out.println(Arrays.toString(S1234));
                short c0 = getDeMuravalue(S1234, R0, vxh); //8bit 
                short c1 = getDeMuravalue(S1234, R1, vxh);
//                System.out.println(c0 + " " + c1);
//                c0c1[0] = c0;
//                c0c1[1] = c1;

                byte fx = (byte) (x * onexy / h);
                byte fy = (byte) (y * onexy / v);

                for (short level = shortLevel; level <= delta; level++) {
//                for (short level = 1; level < delta; level++) {
                    //9+10  + 7+1 = 27 - 17 = 10??
                    // 9+8 +7+1 = 25 - 17 =8 (right?) 
 
                    short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
//                         short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2  ) / Math.pow(2, 17));


                    int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
                    int tInteger = getTetrahedral(fx, fy, fxyBit, fz, fzBit);

                    double dfz = ((double) level) / delta;
                    int tDouble = getTetradedral(fx, fy, fxyBit, dfz);
                    if (tInteger != tDouble) {
                        System.out.println("y: " + y + " x: " + x + " l: " + level + " => " + tInteger + " " + tDouble);
                        errorTCount++;
                    }

//                    short tetrahedralValue = tetrahedral(tInteger, R0, R1, fx, fy, fxyBit, (short) fz, fzBit);
                    short tetrahedralValue = tetrahedral(tInteger, R0, R1, fx, fy, fxyBit, level, coef);
//                    double dfx = ((double) x) / h;
//                    double dfy = ((double) y) / v;
//                    double dtetrahedralValue = tetrahedral(tInteger, R0, R1, dfx, dfy, dfz);
                    tetrahedralWithLinear(tInteger, R0, R1, fx, fy, fxyBit, level, coef, c0, c1, level, delta);
//                    System.out.println(level + " " + linearValue + " " + tetrahedralValue);
//                    System.out.println(linearValue);
                    if (tetrahedralValue != linearValue) {
//                        System.out.println(level + " " + linearValue + " " + tetrahedralValue);

                        errorValueCount++;
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

    static short tetrahedral(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fzbit, int fzBitnum) {
        //10 +8 + 16+1 -17
        //short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fxyone = (int) Math.pow(2, 8 - fxyBitnum);
        int fx = fxbit * fxyone;
        int fy = fybit * fxyone;

        int fzone = (fzBitnum < 8) ? (int) Math.pow(2, 8 - fzBitnum) : 1;
        int fz = fzbit * fzone;

        int z = (c[2] * fz) >> 8;
        short result = (short) (R0[0] + c[0] * fx + c[1] * fy + z);
        return result;
    }

    static short tetrahedral(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fz, short coef) {
        //10 +8 + 16+1 -17
        //short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
//        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
//        int fxyone = (int) Math.pow(2, 8 - fxyBitnum);
//        int fx = fxbit * fxyone;
//        int fy = fybit * fxyone;
//
//        int z = c[2] * fz * (coef * 2 + 1);// / ((int) Math.pow(2, 17));
//        z = (int) (z / Math.pow(2, 16));
//
//        int part1 = R0[0] + c[0] * fx + c[1] * fy;
//        part1 = part1 * 2;
//        int part2 = part1 + z;
//
//        short result = (short) (part2 / 2);
//        return result;


        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fxyone = (int) Math.pow(2, 8 - fxyBitnum);
        int fx = fxbit * fxyone;
        int fy = fybit * fxyone;

        //fz = level
        //c:8 fz:9 coef:7 = 24   ;   coef=16-9=7
        int z = c[2] * fz * (coef);// / ((int) Math.pow(2, 17));
        int z0 = (int) (z / Math.pow(2, 15)); //?-15=9 => 24

        int part1 = R0[0] + c[0] * fx + c[1] * fy;
        int part2 = part1 * 2; //8+1 = 9bit
        int part3 = part2 + z0;
        short tetrahedralValue = (short) (part3 / 2);
        return tetrahedralValue;
    }

    static short tetrahedralWithLinear(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fz, short coef, short c0, short c1, short level, short delta) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fxyone = (int) Math.pow(2, 8 - fxyBitnum);
        int fx = fxbit * fxyone;
        int fy = fybit * fxyone;

        //fz = level
        //c:8 fz:9 coef:7 = 24   ;   coef=16-9=7
        int z = c[2] * fz * (coef);// / ((int) Math.pow(2, 17));
        int z0 = (int) (z / Math.pow(2, 15)); //?-15=9 => 24

        int part1 = R0[0] + c[0] * fx + c[1] * fy;
        int part2 = part1 * 2; //8+1 = 9bit
        int part3 = part2 + z0; //9
        short tetrahedralValue = (short) (part3 / 2);


        int tpart1 = (R0[0] + c[0] * fx + c[1] * fy) * 2;
        int tpart2 = (int) (c[2] * fz * coef / Math.pow(2, 15));//24-15=9
        short tetrahedralValue0 = (short) ((tpart1 + tpart2) / 2);//9 9
//        short tetrahedralValue1 = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 * Math.pow(2, 15) + (c[2] * fz * (coef))) / 2 / Math.pow(2, 15));//
        short tetrahedralValue2_eq0 = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 + (int) (c[2] * fz * (coef) / Math.pow(2, 15))) / 2);//8bit
        short tetrahedralValue3_9bit = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 + (int) (c[2] * fz * (coef) / Math.pow(2, 15))));//9bit
        int tetrahedralValue4_25bit = (int) (((R0[0] + c[0] * fx + c[1] * fy) * Math.pow(2, 17) + (int) (c[2] * fz * (coef) * 2)));//25bit



        //25 - 17 =8; 24+1
//        short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
        //===========================================================================
        // linearValue=linearValue
        //===========================================================================
        short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17)); //8bit
        short linearValue1 = (short) ((c0 * delta + (c1 - c0) * level) * (coef * 2 + 1) / Math.pow(2, 17));//8bit
        int linearValue2_25bit = ((c0 * delta + (c1 - c0) * level) * (coef * 2 + 1)); //25bit
        int linearValue3_25bit = ((c0 * delta + (c1 - c0) * level) * (coef * 2)); //25bit
        //===========================================================================

        int d = (tetrahedralValue4_25bit - linearValue3_25bit);
//        System.out.println(level + " " + tetrahedralValue4_25bit + " " + linearValue3_25bit + " d:" + d + " " + (d / Math.pow(2, 17)));
//        System.out.println(tetrahedralValue2_eq0*2+" "+tetrahedralValue3_9bit);


//        System.out.println("level: " + level + " " + c[0] * fx + " " + c[1] * fy);
//        if(tetrahedralValue0!=tetrahedralValue){
//            System.out.println(tetrahedralValue0);
//        }

        return tetrahedralValue;
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

//        int a = -5 / 2;
//        int b = -5 >> 1;
//        int c = 5 >> 1;
//        short[] R = new short[]{1, 2, 3, 4};
//        getP(R, 0, 0);
//        getP(R, 1, 0);
//        getP(R, 0, 1);
//        getP(R, 1, 1);

//        short delta = 102;
//        short v = 4, h = 16;



//        short[][] vhs = {{4, 16}, {8, 8}, {16, 4}};
        short[][] vhs = {{4, 16}};
        short[] vhArray = {4, 8, 16};

//        int deltaStart = (int) Math.round(1023 * 0.05); //51
        int deltaStart = 510;
        int deltaEnd = 510;//(int) Math.round(1023 * 0.5);
//        int deltaEnd = deltaStart;

        for (short v : vhArray) {
            for (short h : vhArray) {
//        for (short[] vh : vhs) {
            for (int delta = deltaStart; delta <= deltaEnd; delta++) {

//                evaluate(R0, R1, vh[0], vh[1], (short) delta);
                    evaluate(R0, R1, v, h, (short) delta);


                }
            }
        }


    }
}
