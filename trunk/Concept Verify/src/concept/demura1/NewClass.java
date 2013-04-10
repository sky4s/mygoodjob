/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package concept.demura1;

/**
 *
 * @author Skyforce
 */
public class NewClass {

    public static void main(String[] args) {
        //p000+c1*fx+c2*fy+c3*fz
        //fx = (x-x0)/(x1-x0)
        int c = 100;//10bit
        int block = 15;//4
        int pos = 7;
        double result = ((double) pos) / block * c;
        System.out.println(result);

        int cpos = (c * pos) & (int) (Math.pow(2, 14) - 1);
        cpos <<= 1;
        int cposblock = cpos / block;
        cposblock = (cposblock & 1) != 0 ? cposblock + 1 : cposblock;
        cposblock /= 2;
        System.out.println(cposblock);

        for (int bit = 6; bit <= 12; bit++) {
//            int posblock=pos<<4/15;
            int max = (int) (Math.pow(2, bit) - 1);
            int posblock = (int) (((double) pos / block) * max);
            System.out.println(bit + ": " + (((double) posblock / max) * c) + " " + (posblock * c / (double) max) + " " + posblock);
        }
    }
}
