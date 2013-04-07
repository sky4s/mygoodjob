/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept;

import java.util.Arrays;

/**
 *
 * @author Skyforce
 */
public class Divider {

    static int[] divide(int a, int b) {
        int x = 0;
        for (; (b * x) < a; x++) {
        }
        x--;
        int r = a - x * b;
        return new int[]{x, r};
    }

    static short[] divide(int a, int b, int precision) {
//        int ab = a / b;
//        int r = a % b;

        int[] abr = divide(a, b);
        int ab = abr[0];
        int r = abr[1];

        short[] result = new short[1 + precision];
        result[0] = (short) ab;
        for (int x = 0; x < precision; x++) {
            r *= 10;
//            result[x + 1] = (short) (r / b);
//            r = r % b;

            abr = divide(r, b);
            result[x + 1] = (short) abr[0];
            r = abr[1];
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println(Arrays.toString(divide(9, 4)));
        System.out.println(Arrays.toString(divide(9, 7, 30)));

    }
}
