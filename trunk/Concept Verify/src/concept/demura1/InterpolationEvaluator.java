/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

import java.awt.Color;
import java.util.Arrays;
import shu.math.array.DoubleArray;
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
        //00,01,10,11
        //yagi-san: 00 10 01 11 (rg)
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

    static short[] processR(short[] R, short delta) {
        int size = R.length;
        short[] result = Arrays.copyOf(R, size);
        for (int x = 0; x < size; x++) {
            result[x] = (short) (R[x] + delta);
        }
        return result;
    }

    static Report evaluate12bit(short[] R0_, short[] R1_, short v, short h, short delta) {
        short coef = (short) Math.round(Math.pow(2, 16) / delta); //16-9 = 7 ~12bit ,delta >=17
        int fzBit = 9;
        int fxyBit = 4;
        byte onexy = (byte) (Math.pow(2, fxyBit));
        int totalCount = 0;
        int errorTCount = 0;
        int errorValueCount = 0;

        short shortLevel = 0;

        int starty = 0;
        int startx = 0;
        short[] R0 = processR(R0_, (short) 128);
        short[] R1 = processR(R1_, (short) (128 + delta));
        if (equal(R0) && equal(R1)) {
            starty = v - 1;
            startx = h - 1;
        }

        int vxh = v * h;
        int maxError = 0;


        for (int y = starty; y < v; y++) {
            for (int x = startx; x < h; x++) {

                short[] S1234 = getS1234(h, v, x, y); //8bit  
                short c0 = getDeMuravalue(S1234, R0_, vxh); //8bit 
                short c1 = getDeMuravalue(S1234, R1_, vxh);

                byte fx = (byte) (x * onexy / h);
                byte fy = (byte) (y * onexy / v);

                int maxValue = 0;
                int minValue = Integer.MAX_VALUE;

                for (short level = shortLevel; level <= delta; level++) {

                    int c0c1 = ((delta - level) * c0 + level * c1);
                    maxValue = Math.max(maxValue, c0c1);
                    minValue = Math.min(minValue, c0c1);


                    //8+17=25;  25-13 = 12
                    //9+8+12+1=30
                    short linearValue = (short) (c0c1 * (coef * 2 + 1) / Math.pow(2, 17));

                    int fz = (int) ((level * Math.pow(2, fzBit)) / delta);
                    int tInteger = getTetrahedral(fx, fy, fxyBit, fz, fzBit);

                    double dfz = ((double) level) / delta;
                    int tDouble = getTetradedral(fx, fy, fxyBit, dfz);
                    if (tInteger != tDouble) {
                        errorTCount++;
                    }

                    short tetrahedralStandard = tetrahedralStandard(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
//                    short tetrahedralTest = tetrahedralTest(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                    short temp = tetrahedralStandard;
                    if (process12Bit) {
//tetrahedralInterpolate()

                        tetrahedralStandard = (short) (tetrahedralStandard - level - 128);
                    }


                    short compareValue = tetrahedralStandard;

                    int error = Math.abs(compareValue - linearValue);
                    maxError = Math.max(maxError, error);
                    if (error > 127) {
                        if (2 == tInteger) {
                            double[] x_ = {((double) x) / h, ((double) y) / v, ((double) level) / delta};
                            double[][] xn = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {1, 1, 1}};
                            double[][] yn = {{p(0, 0, R0), p(0, 0, R0), p(0, 0, R0)},
                                {p(1, 0, R0), p(1, 0, R0), p(1, 0, R0)},
                                {p(1, 0, R1), p(1, 0, R1), p(1, 0, R1)},
                                {p(1, 1, R1), p(1, 1, R1), p(1, 1, R1)}};
                            double[] result = tetrahedralInterpolate(x_, xn, yn);
                            double r = result[0];
                            int a = 1;
                        }

                        tetrahedralStandard = tetrahedralStandard(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                        tetrahedralStandard = (short) (tetrahedralStandard - level - 128);
                    }
                    if (linearValue != compareValue) {
                        errorValueCount++;
                    } else {
                    }

                    totalCount++;
                }

            }
        }


        if (errorTCount != 0 || errorValueCount != 0) {
            double rate = ((double) errorValueCount) / totalCount;
//            System.out.println("==> errT:" + errorTCount + " errV:" + errorValueCount + " / " + totalCount + " (rate:" + rate + ") " + maxError);
            Report report = new Report();
            report.rate = rate;
            report.maxError = maxError;
            return report;
        } else {
            return new Report();
        }
    }

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
//                    int linearValue_25bit = (((delta - level) * c0 + level * c1) * (coef * 2 + 1)); //8bit

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
//                    short tetrahedralTest = tetrahedralTest(tInteger, R0, R1, fx, fy, fxyBit, level, delta);


                    short compareValue = tetrahedralStandard;

                    int error = Math.abs(compareValue - linearValue);
                    maxError = Math.max(maxError, error);
                    if (error > 127) {
////                        tetrahedralTest(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                        tetrahedralStandard = tetrahedralStandard(tInteger, R0, R1, fx, fy, fxyBit, level, delta);
                    }
//                    System.out.println(level + " " + linearValue + " " + tetrahedralStandard);
                    if (linearValue != compareValue) {
//                        System.out.println(level + " " + linearValue + " " + tetrahedralTest + "*");
                        errorValueCount++;
                    } else {
//                        System.out.println(level + " " + linearValue + " " + tetrahedralTest);
                    }

                    totalCount++;
                }

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

        short coef = (short) ((Math.pow(2, coefbit)) / delta + 1);
        int z = c[2] * level * (coef);//8+9+9=25

        minZ_S = Math.min(minZ_S, z);
        maxZ_S = Math.max(maxZ_S, z);
//        z = z & 0x1FFFFFF; //25
        //255 511 257
        //8 9 9

        // (8+4)  +12+1
        int part00 = (int) ((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy);
        minPart00_S = Math.min(minPart00_S, part00);
        maxPart00_S = Math.max(maxPart00_S, part00);

        int part0 = (int) ((part00 * Math.pow(2, 12)) * Math.pow(2, coefbit - 16));
        minPart_S = Math.min(minPart_S, part0);
        maxPart_S = Math.max(maxPart_S, part0);
//        if (-48111616 == part0) {
//            int a = 1;
//        }

        int tetrahedralValue_25bit = (int) part0 + z;
        maxT_S = Math.max(maxT_S, tetrahedralValue_25bit);
        minT_S = Math.min(minT_S, tetrahedralValue_25bit);
//        int tetrahedralValue_25bit = tetrahedralValue_25bit * 2;
        short result = (short) (tetrahedralValue_25bit / Math.pow(2, coefbit));;
        short result_part0 = (short) (part0 / Math.pow(2, coefbit));
        short result_z = (short) (z / Math.pow(2, coefbit));
        maxR_S = Math.max(maxR_S, result);
        minR_S = Math.min(minR_S, result);
        return result;
    }
    static int minPart00_S = 0;
    static int maxPart00_S = 0;
    static int minPart_S = 0;
    static int maxPart_S = 0;
    static int maxZ_S = 0;
    static int minZ_S = 0;
    static int maxT_S = 0;
    static int minT_S = 0;
    static int maxR_S = 0;
    static int minR_S = 0;
    static int testbit = 25;
    static int maxZ = 0;
    static int minZ = 0;
    static int maxc0fx = 0;
    static int minc0fx = 0;
    static int maxc0fxc1fy = 0;
    static int minc0fxc1fy = 0;
    static int maxPart0 = 0;
    static int minPart0 = 0;

    static short tetrahedralTest(int tetradedralIndex, short[] R0, short[] R1, byte fxbit, byte fybit, int fxyBitnum, short level, short delta) {
        short[] c = getc123(tetradedralIndex, R0, R1);//8bit
        int fx = fxbit;
        int fy = fybit;

        int coefbit = 17;

//        short coef = (short) Math.round((Math.pow(2, coefbit) ) / delta); //17-9=8
        short coef = (short) ((Math.pow(2, coefbit)) / delta + 1); //17-9=8 X =>9bit
        int z = c[2] * level * (coef);//8+9+9=25
        int z25bit = z;
        maxZ = Math.max(z, maxZ);
        minZ = Math.min(z, minZ);
//        if(z >0) {
//            z25bit= z>16777215?16777215:z;
//        }else {
//            z25bit= z<(-16777215)?-16777215:z;
//        }
//        if( z25bit!=z) {
//            int x=1;
//        }
//        int z25bit = z & 0x1FFFFFF; //25

        //33554431

        int invcoef = (int) Math.pow(2, coefbit - 16);  //1bit
//          int invcoef = 1;
//        int tetrahedralValue_25bit = (int) ((((R0[0] * Math.pow(2, 4)) + c[0] * fx + c[1] * fy) * Math.pow(2, 12)) * invcoef) + z25bit;

        int c0fx = c[0] * fx;
        int c1fy = c[1] * fy;
        int c0fx_c1fy = c0fx + c1fy;

        maxc0fx = Math.max(maxc0fx, c0fx);
        minc0fx = Math.min(minc0fx, c0fx);

        maxc0fxc1fy = Math.max(maxc0fxc1fy, c0fx_c1fy);
        minc0fxc1fy = Math.min(minc0fxc1fy, c0fx_c1fy);

        int part0_12 = ((int) (R0[0] * Math.pow(2, 4)) + c0fx_c1fy);

        maxPart0 = Math.max(part0_12, maxPart0);
        minPart0 = Math.min(part0_12, minPart0);

        int z10 = (int) (z / Math.pow(2, 15));
        int z12 = (int) (z / Math.pow(2, 13));
        int R0_10bit = (int) (R0[0] * Math.pow(2, 2));
        int fxy_10bit = (int) ((c[0] * fx + c[1] * fy) / Math.pow(2, 2));
        int t0_10bit = (int) (z10 + R0_10bit + fxy_10bit);
        int t0_10bit_2 = (int) (z10 + fxy_10bit);

        //12+12+1 = 25
//        int test = ((int) (part0_12 * Math.pow(2, 12))) * invcoef + z25bit;
//    
        int dividebit = testbit - 25 + coefbit;

        int z12bit = z25bit / ((int) Math.pow(2, 13));
        int partA = (int) (part0_12 * Math.pow(2, 12 - 25 + testbit)); //+8
        int partB = (int) (z25bit / Math.pow(2, 25 - testbit));
        int testbitvalue = (partA * invcoef + partB);

        int testbitvalueA = partA * invcoef;
        short resultA = (short) (testbitvalueA / Math.pow(2, dividebit));

//        int result = (int) ((t0_10bit_2 + R0_10bit) / 4);
        short result = (short) (testbitvalue / Math.pow(2, dividebit));
        return result;
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
//        00,01,10,11
        //yagi-san: 00 10 01 11 (rg)
        int index = ((x != 0) ? 1 : 0) + ((y != 0) ? 2 : 0);
//        int index = ((x != 0) ? 2 : 0) + ((y != 0) ? 1: 0);
        return R[index];
    }

    static short[] getc123(int tetradedralIndex, short[] R0, short[] R1) {
        //00,01,10,11
        //yagi-san: 00 10 01 11 (rg)
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
//        short[] R0 = new short[]{-128, -128, -128, -128};
//        short[] R0 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{-128, -128, -128, -128};
        //00,01,10,11
        short[] R0 = new short[]{-128, 127, -128, 127};
        short[] R1 = new short[]{127, -128, 127, -128};

//        short[] R0 = new short[]{-121, -4, 99, 115};
//        short[] R1 = new short[]{128, 77, 61, -106};

        process(R0, R1);


//        short[] R0 = new short[]{-128, -126, -123, -119};
//        short[] R1 = new short[]{121, 124, 126, 127};

//        process(R0, R1);
//        short[] R = new short[8];
//
//        for (int test = 0; test < 0; test++) {
//
//            for (int x = 0; x < 8; x++) {
//                double d = Math.random() * 256 - 128;
//                int i = (int) Math.round(d);
//                R[x] = (short) i;
//            }
//            for (int x = 0; x < 4; x++) {
//                R0[x] = R[x];
//
//                R1[x] = R[x + 4];
//            }
//            int error = process(R0, R1);
//            if (error > 127) {
//                System.out.println(Arrays.toString(R0));
//                System.out.println(Arrays.toString(R1) + " error: " + error);
//            }
//        }
    }
    static boolean process12Bit = true;

    public static int process(short[] R0, short[] R1) {
        //00,01,10,11
//        short[] R0 = new short[]{-128, -128, -128, -128};
//        short[] R0 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{127, 127, 127, 127};
//        short[] R1 = new short[]{-128, -128, -128, -128};

//        short[] R0 = new short[]{-128, 127, -128, 127};
//        short[] R1 = new short[]{127, -128, 127, -128};



//        short[] R0 = new short[]{-128, -126, -123, -119};
//        short[] R1 = new short[]{121, 124, 126, 127};





//        short[][] vhs = {{4, 16}, {8, 8}, {16, 4}};
        short[][] vhs = {{4, 16}};
        short[] vhArray = {4, 8, 16};


        int deltaStart = 17;

        if (process12Bit) {
            deltaStart = 256;
        }
//        int deltaStart = 510;
//        int deltaStart = (int) Math.round(1023 * 0.05); //51
//        int deltaStart = 511;
        int deltaEnd = 511;//(int) Math.round(1023 * 0.5);
//        int deltaEnd = (int) Math.round(1023 * 0.05); //51
//        int deltaEnd = deltaStart;

//        int coefbit =17;
//        for(int delta = deltaStart;delta<=deltaEnd;delta++){
//             short coef = (short) ((Math.pow(2, coefbit)) / delta + 1); //13bit
//             System.out.println(coef);
//        }
        int totalMaxError = 0;
//        for (short v : vhArray) {
//            for (short h : vhArray) {
        for (int bit = 11; bit >= 11; bit--) {
//             for (int bit = 12; bit >= 12; bit--) {
            testbit = bit;
            int errorCount = 0;
            int totalCount = 0;
            double totalRate = 0;


            for (short[] vh : vhs) {
                for (int delta = deltaStart; delta <= deltaEnd; delta++) {
                    Report report = null;
                    if (process12Bit) {
                        report = evaluate12bit(R0, R1, vh[0], vh[1], (short) delta);
                    } else {
                        report = evaluate(R0, R1, vh[0], vh[1], (short) delta);
                    }
                    double rate = report.rate;
                    int maxError = report.maxError;
                    totalMaxError = (int) Math.max(totalMaxError, maxError);
                    if (0 != rate) {
                        errorCount++;
                        totalRate += rate;
//                        System.out.println(delta + " " + rate + " " + maxError);
                    } else {
//                        System.out.println(delta + " 0");
                    }
                    totalCount++;
//                    evaluate(R0, R1, v, h, (short) delta);


                }
            }
            System.out.println(bit + " errorCount: " + errorCount + " " + "ave rate: " + (totalRate / errorCount));
            System.out.println("totalMaxError: " + totalMaxError);


        }


//        }
        boolean showStep = false;
        if (showStep) {
            System.out.println("Z: " + minZ + " " + maxZ); //-31447620 33552900 26bit
            System.out.println("cofx: " + minc0fx + " " + maxc0fx); //-3825 3825 13bit
            System.out.println("cofx*c1fy: " + minc0fxc1fy + " " + maxc0fxc1fy);//-3825 3825 13bit
            System.out.println("part0: " + minPart0 + " " + maxPart0);//-5873 1777 14bit

            System.out.println("Part00_S: " + minPart00_S + " " + maxPart00_S); //-a 1777  14bit
            System.out.println("Part_S: " + minPart_S + " " + maxPart_S); //-48111616 14557184 27bit 25bit
            System.out.println("Z_S: " + minZ_S + " " + maxZ_S); //-31447620 33552900 26bit
            System.out.println("T_S: " + minT_S + " " + maxT_S); //-16890436 16775684 26bit
            System.out.println("maxR_S: " + minR_S + " " + maxR_S); //-128 127 8bit
        }

        return totalMaxError;
    }

    /**
     * 以任意四點為基礎的四面體內插法
     *
     * @param x double[]
     * @param xn double[][]
     * @param yn double[][]
     * @return double[]
     */
    public static double[] tetrahedralInterpolate(double[] x, double[][] xn,
            double[][] yn) {
        if (xn.length != 4 || yn.length != 4) {
            throw new IllegalArgumentException(" xn.length or yn.length != 4");
        }
        double[] abr = calculateAlphaBetaGamma(x, xn[0], xn[1], xn[2], xn[3]);
        if (!isInsideTetrahedron(abr[0], abr[1], abr[2])) {
            throw new IllegalArgumentException("x is not in xn");
        }

        double[][] delta = new double[][]{
            {
                yn[1][0] - yn[0][0], yn[2][0] - yn[0][0], yn[3][0] - yn[0][0]}, {
                yn[1][1] - yn[0][1], yn[2][1] - yn[0][1], yn[3][1] - yn[0][1]}, {
                yn[1][2] - yn[0][2], yn[2][2] - yn[0][2], yn[3][2] - yn[0][2]}
        };
        double[] timesResult = DoubleArray.timesFast(delta, abr);
        //yn[0][0]~[2]是原點
        timesResult[0] += yn[0][0];
        timesResult[1] += yn[0][1];
        timesResult[2] += yn[0][2];

        return timesResult;
    }

    /**
     * 測試p是否在p0~p3所組成的四面體內
     *
     * @param alpha double
     * @param beta double
     * @param gamma double
     * @return boolean
     */
    protected static boolean isInsideTetrahedron(double alpha, double beta,
            double gamma) {
        if (alpha >= 0 && beta >= 0 && gamma >= 0
                && (alpha + beta + gamma) <= 1) {
            return true;
        } else {
            return false;
        }
    }

    protected static double[] calculateAlphaBetaGamma(double[] p, double[] p0,
            double[] p1,
            double[] p2, double[] p3) {
        double[][] delta = new double[][]{
            {
                p1[0] - p0[0], p2[0] - p0[0], p3[0] - p0[0]}, {
                p1[1] - p0[1], p2[1] - p0[1], p3[1] - p0[1]}, {
                p1[2] - p0[2], p2[2] - p0[2], p3[2] - p0[2]}
        };
//        if (!DoubleArray.isNonsingular(delta)) {
//            return null;
//        }
        double[][] deltaInv = DoubleArray.inverse(delta);
        double[] deltaP = new double[]{
            p[0] - p0[0], p[1] - p0[1], p[2] - p0[2]};
        double[] abr = DoubleArray.times(deltaInv, deltaP);
        return abr;
    }
}
