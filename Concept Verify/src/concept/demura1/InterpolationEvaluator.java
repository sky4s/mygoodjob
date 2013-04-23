/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

import java.awt.Color;
import java.util.Arrays;
//import shu.plot.*;

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

        //v,h: 4 8 16:  16 32 64 128 256 4~8bit
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

    static Report evaluate(short[] R0, short[] R1, short v, short h, short delta) {
        short coef = (short) Math.round(Math.pow(2, 16) / delta); //16-9 = 7 ~12bit ,delta >=17
        int fzBit = 9;
        int fxyBit = 4;
        byte onexy = (byte) (Math.pow(2, fxyBit));
        int totalCount = 0;
        int errorTCount = 0;
        int errorValueCount = 0;

//        short shortLevel = (short) (delta - 1);
//        short shortLevel = 1;
        short shortLevel = 0;
//        short shortLevel = 255;


//        int starty = v - 1;
//        int startx = h - 1;
        int starty = 0;
        int startx = 0;
        if (equal(R0) && equal(R1)) {
            starty = v - 1;
            startx = h - 1;
        }

//        
        int vxh = v * h;
        int maxError = 0;


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

//                if( c0 !=R0[0] || c1 !=R1[0]) {
//                    System.out.println("x");
//                }

                byte fx = (byte) (x * onexy / h);
                byte fy = (byte) (y * onexy / v);
//                Plot2D plot = Plot2D.getInstance();

                int maxValue = 0;
                int minValue = Integer.MAX_VALUE;
//                int maxc0Value = 0;
//                int minc0c1 = Integer.MAX_VALUE;
//                int maxc0c1 = 0;


                for (short level = shortLevel; level <= delta; level++) {
//                for (short level = 1; level < delta; level++) {
                    //9+10  + 7+1 = 27 - 17 = 10??
                    // 9+8 +7+1 = 25 - 17 =8 (right?) 


                    int c0c1 = ((delta - level) * c0 + level * c1);
                    maxValue = Math.max(maxValue, c0c1);
                    minValue = Math.min(minValue, c0c1);
//                    System.out.println((delta - level) * c0 + " " + level * c1);


                    //8+17=25;  25-13 = 12
                    //9+8+12+1=30
                    short linearValue = (short) (c0c1 * (coef * 2 + 1) / Math.pow(2, 17));
//                      short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
                    //17 17 17 17+13
//                    System.out.println(level + ": " + (delta - level) * c0 + " " + level * c1 + " " + c0c1 + " " + c0c1 * (coef * 2 + 1) + " " + linearValue + " " + coef);
//                    System.out.println(level + ": " + c0c1 + " " + c0c1 * (coef * 2 + 1) + " " + linearValue + " " + coef);
//                    minc0c1 = Math.min(minc0c1, c0c1);
//                    maxc0c1 = Math.max(maxc0c1, c0c1);

//                    short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2) / Math.pow(2, 17));
                    int linearValue_25bit = (((delta - level) * c0 + level * c1) * (coef * 2 + 1)); //8bit

                    int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
                    int tInteger = getTetrahedral(fx, fy, fxyBit, fz, fzBit);

                    double dfz = ((double) level) / delta;
                    int tDouble = getTetradedral(fx, fy, fxyBit, dfz);
                    if (tInteger != tDouble) {
//                        System.out.println("y: " + y + " x: " + x + " l: " + level + " => " + tInteger + " " + tDouble);
                        errorTCount++;
                    }

//                    short tetrahedralValue = tetrahedral(tInteger, R0, R1, fx, fy, fxyBit, (short) fz, fzBit);
//                    short tetrahedralValue = tetrahedral(tInteger, R0, R1, fx, fy, fxyBit, level, coef);
//                    int tetrahedral25bit = tetrahedral25bit(tInteger, R0, R1, fx, fy, fxyBit, level, coef);
                    short tetrahedralStandard = tetrahedralStandard(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                    short tetrahedralTest = tetrahedralTest(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
//                    short tetrahedralTest = tetrahedralStandard(tInteger, R0, R1, fx, fy, fxyBit, level, delta);

                    int error = Math.abs(tetrahedralTest - linearValue);
                    maxError = Math.max(maxError, error);
                    if (error > 1) {
                        tetrahedralTest(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                    }
//                    System.out.println(level + " " + linearValue + " " + tetrahedralStandard);
                    if (linearValue != tetrahedralTest) {
//                        System.out.println(level + " " + linearValue + " " + tetrahedralTest + "*");
                        errorValueCount++;
                    } else {
//                        System.out.println(level + " " + linearValue + " " + tetrahedralTest);
                    }
//                    plot.addCacheScatterLinePlot("linear", Color.red, level, linearValue_25bit);
//                    plot.addCacheScatterLinePlot("tetra", Color.green, level, tetrahedral25bit);
//                    double dfx = ((double) x) / h;
//                    double dfy = ((double) y) / v;
//                    double dtetrahedralValue = tetrahedral(tInteger, R0, R1, dfx, dfy, dfz);
//                    tetrahedralWithLinear(tInteger, R0, R1, fx, fy, fxyBit, level, coef, new short[]{c0, c1}, level, delta);
//                    System.out.println(level + " " + linearValue + " " + tetrahedralValue);
//                    System.out.println(linearValue);



//                    if (tetrahedralValue != linearValue) {
////                        System.out.println(level + " " + linearValue + " " + tetrahedralValue);
//
//                        errorValueCount++;
//                    }
                    totalCount++;
                }
//                System.out.println("minValue: " + minValue + " maxValue:" + maxValue);
//                System.out.println(delta + ": " + minc0c1 + " " + maxc0c1);
//                plot.setVisible();
            }
        }


        if (errorTCount != 0 || errorValueCount != 0) {
//            System.out.print("v: " + v + " h:" + h + " delta:" + delta);
            double rate = ((double) errorValueCount) / totalCount;
//            System.out.println("==> errT:" + errorTCount + " errV:" + errorValueCount + " / " + totalCount + " (rate:" + rate + ") " + maxError);
            Report report = new Report();
            report.rate = rate;
            report.maxError = maxError;
            return report;
        } else {
//            System.out.println("v: " + v + " h:" + h + " delta:" + delta);
            return new Report();
        }
//        return true;
    }

    static class Report {

        double rate;
        int maxError;
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

    static int tetrahedral25bit(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fz, short coef) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fx = fxbit;
        int fy = fybit;

        //fz=  int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
        int z = c[2] * fz * (coef);// 8+9+7 = 24


        int tetrahedralValue_24bit = (int) (((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy) * Math.pow(2, 12)) + z;
        int tetrahedralValue_25bit = tetrahedralValue_24bit * 2;
        return tetrahedralValue_25bit;
    }

    static short tetrahedralStandard(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short level, short delta) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fx = fxbit;
        int fy = fybit;

        int coefbit = 17;

//        short coef = (short) Math.round((Math.pow(2, coefbit) ) / delta); //17-9=8
        short coef = (short) ((Math.pow(2, coefbit)) / delta + 1); //17-9=8 X =>9bit
        int z = c[2] * level * (coef);//8+9+9=25
        z = z & 0x1FFFFFF; //25
        //255 511 257
        //8 9 9

        // (8+4)  +12+1
        int tetrahedralValue_25bit = (int) ((((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy) * Math.pow(2, 12)) * Math.pow(2, coefbit - 16)) + z;
//        int tetrahedralValue_25bit = tetrahedralValue_25bit * 2;
        return (short) (tetrahedralValue_25bit / Math.pow(2, coefbit));
    }
    static int testbit = 25;

    static short tetrahedralTest(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short level, short delta) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fx = fxbit;
        int fy = fybit;

        int coefbit = 17;

//        short coef = (short) Math.round((Math.pow(2, coefbit) ) / delta); //17-9=8
        short coef = (short) ((Math.pow(2, coefbit)) / delta + 1); //17-9=8 X =>9bit
        int z = c[2] * level * (coef);//8+9+9=25
        int z25bit = z & 0x1FFFFFF; //25
//        int z24bit = z25bit / 2;
//        int z23bit = z24bit / 2;
//        int z22bit = z23bit / 2;

        int invcoef = (int) Math.pow(2, coefbit - 16);  //1bit
//          int invcoef = 1;
        int tetrahedralValue_25bit = (int) ((((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy) * Math.pow(2, 12)) * invcoef) + z25bit;

        int part0_12 = ((int) (R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy);
        int z10 = (int) (z / Math.pow(2, 15));
        int z12 = (int) (z / Math.pow(2, 13));
        int R0_10bit = (int) (R0[0] * Math.pow(2, 2));
        int fxy_10bit = (int) ((c[0] * fx + c[1] * fy) / Math.pow(2, 2));
        int t0_10bit = (int) (z10 + R0_10bit + fxy_10bit);
        int t0_10bit_2 = (int) (z10 + fxy_10bit);

        //12+12+1 = 25
        int test = ((int) (part0_12 * Math.pow(2, 12))) * invcoef + z25bit;
//    
        int dividebit = testbit - 25 + coefbit;

        int z12bit = z25bit / ((int) Math.pow(2, 13));
        int partA = (int) (part0_12 * Math.pow(2, 12 - 25 + testbit));
        int partB = (int) (z25bit / Math.pow(2, 25 - testbit));
        int testbitvalue = (partA * invcoef + partB);

//        int result = (int) ((t0_10bit_2 + R0_10bit) / 4);
        return (short) (testbitvalue / Math.pow(2, dividebit));
//            return (short) (tetrahedralValue_25bit / Math.pow(2, coefbit));
    }

    static short tetrahedralWithLinear(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short fz, short coef, short[] linearc, short level, short delta) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fxyone = (int) Math.pow(2, 8 - fxyBitnum);
        int fx = fxbit;
        int fy = fybit;

        //c:8 fz:9 coef:7 = 24   ;   coef=16-9=7
        int z = c[2] * fz * (coef);// 8+9+7 = 24
        int z0 = (int) (z / Math.pow(2, 12)); //24-12=12
        int z0_13bit = (int) (z / Math.pow(2, 11)); //24-11=13

//        int z1 = (int) (z / Math.pow(2, 11)); //24-11=13


        int part10 = (int) (R0[0] * Math.pow(2, 4));//12
        int part11 = c[0] * fx;//12
        int part12 = c[1] * fy;//12
        int part112 = (part11 + part12);//12

        int part1 = part10 + part112;//12
//        int part2 = part1; //12
        int part3 = part1 + z0; //12
        //-4096 + 8160
        int part3_13bit = part1 * 2 + z0_13bit; //13
        short tetrahedralValue = (short) (part3 / Math.pow(2, 4));
        short tetrahedralValue_9bit = (short) (part3 / Math.pow(2, 3));
        int tetrahedralValue_24bit = (int) (((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy) * Math.pow(2, 12)) + z;
        int tetrahedralValue_25bit = tetrahedralValue_24bit * 2;

        if (level == 511) {
            System.out.println("");
        }
//        short newtetrahedralValue = (short) ((part3_13bit + 1) / Math.pow(2, 5));
//        int tetrahedralValue_24bit_2 = (int) (part1 * Math.pow(2, 12) + z);
//        int tetrahedralValue_24bit_2 = z;
//        int part4 = part2 * 2 + z1; //12
//   short newtetrahedralValue = (short) ((part3+1) / Math.pow(2, 4));


//        int tpart1 = (R0[0] + c[0] * fx + c[1] * fy) * 2;
//        int tpart2 = (int) (c[2] * fz * coef / Math.pow(2, 15));//24-15=9
//        short tetrahedralValue0 = (short) ((tpart1 + tpart2) / 2);//9 9
////        short tetrahedralValue1 = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 * Math.pow(2, 15) + (c[2] * fz * (coef))) / 2 / Math.pow(2, 15));//
//        short tetrahedralValue2_eq0 = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 + (int) (c[2] * fz * (coef) / Math.pow(2, 15))) / 2);//8bit
//        short tetrahedralValue3_9bit = (short) (((R0[0] + c[0] * fx + c[1] * fy) * 2 + (int) (c[2] * fz * (coef) / Math.pow(2, 15))));//9bit
//        int tetrahedralValue4_25bit = (int) (((R0[0] + c[0] * fx + c[1] * fy) * Math.pow(2, 17) + (int) (c[2] * fz * (coef) * 2)));//25bit



        short c0 = linearc[0];
        short c1 = linearc[1];
        //25 - 17 =8; 24+1
//        short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17));
        //===========================================================================
        // linearValue=linearValue
        //===========================================================================
        short linearValue = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 17)); //8bit
        short linearValue_modified = (short) ((c0 * delta + (c1 - c0) * level) * (coef * 2 + 1) / Math.pow(2, 17));//8bit

        int linearValue_25bit = (((delta - level) * c0 + level * c1) * (coef * 2 + 1)); //8bit
        short linearValue_9bit = (short) (((delta - level) * c0 + level * c1) * (coef * 2 + 1) / Math.pow(2, 16)); //8bit



        int linearValueWiki_part2 = (c1 - c0) * level * coef;
        int linearValueWiki_part2_minus16bit = (int) ((c1 - c0) * level * coef / Math.pow(2, 16));
        int linearValueWiki_part2_minus15bit = (int) ((c1 - c0) * level * coef / Math.pow(2, 15));
//          int linearValueWiki_part2_minus15bit = (int) ((c1 - c0) * level * coef >>16);
        int linearValueWiki = c0 + linearValueWiki_part2_minus16bit;
        int linearValueWiki_9bit = c0 * 2 + linearValueWiki_part2_minus15bit;

        short linearValue_noplus = (short) (((delta - level) * c0 + level * c1) * (coef * 2) / Math.pow(2, 17)); //8bit
        short linearValue_noplus_9bit = (short) (((delta - level) * c0 + level * c1) * (coef * 2) / Math.pow(2, 16)); //8bit


        //org 9+8+7=24
        //new 9+8+9 = 26
        int linearValue_noplus_24bit = (((delta - level) * c0 + level * c1) * (coef)); //24bit

        System.out.println(level + " " + linearValue + " " + tetrahedralValue + " " + linearValue_25bit + " " + tetrahedralValue_25bit);


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

    static boolean equal(short[] array) {
        boolean eq = true;
        for (int x = 0; x < array.length - 1; x++) {
            eq = eq && array[x] == array[x + 1];
        }
        return eq;
    }

    public static void main(String[] args) {
        //00,10,01,11
//        short[] R0 = new short[]{-128, -128, -128, -128};
//        short[] R0 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{-128, -128, -128, -128};

        short[] R0 = new short[]{-128, 127, -128, 127};
        short[] R1 = new short[]{127, -128, 127, -128};



//        short[] R0 = new short[]{-128, -126, -123, -119};
//        short[] R1 = new short[]{121, 124, 126, 127};





//        short[][] vhs = {{4, 16}, {8, 8}, {16, 4}};
        short[][] vhs = {{4, 16}};
        short[] vhArray = {4, 8, 16};

        int deltaStart = 17;
//        int deltaStart = (int) Math.round(1023 * 0.05); //51
//        int deltaStart = 511;
        int deltaEnd = 511;//(int) Math.round(1023 * 0.5);
//        int deltaEnd = (int) Math.round(1023 * 0.05); //51
//        int deltaEnd = deltaStart;

//        for (short v : vhArray) {
//            for (short h : vhArray) {
        for (int bit = 25; bit >= 8; bit--) {
//             for (int bit = 12; bit >= 12; bit--) {
            testbit = bit;
            int errorCount = 0;
            int totalCount = 0;
            double totalRate = 0;
            int totalMaxError = 0;

            for (short[] vh : vhs) {
                for (int delta = deltaStart; delta <= deltaEnd; delta++) {
                    Report report = evaluate(R0, R1, vh[0], vh[1], (short) delta);
                    double rate = report.rate;
                    int maxError = report.maxError;
                    totalMaxError = (int) Math.max(totalMaxError, maxError);
                    if (0 != rate) {
                        errorCount++;
                        totalRate += rate;
                        System.out.println(delta + " " + rate + " " + maxError);
                    } else {
//                        System.out.println(delta + " 0");
                    }
                    totalCount++;
//                    evaluate(R0, R1, v, h, (short) delta);


                }
            }
            System.out.println(bit + " errorCount: " + errorCount + " " + "ave rate: " + (totalRate / errorCount));
//            System.out.println("totalMaxError: "+totalMaxError);
//            System.out.println();
        }


//        }


    }
}
