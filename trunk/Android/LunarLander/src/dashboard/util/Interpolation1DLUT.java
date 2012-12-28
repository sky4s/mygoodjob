/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dashboard.util;

import java.util.Arrays;

/**
 *
 * @author SkyforceShen
 */
public final class Interpolation1DLUT {

    /**
     * 內插所採用的演算法
     */
    private double[] keyArray;
    private double[] valueArray;

    public double[] getKeyArray() {
        return keyArray;
    }

    public double[] getValueArray() {
        return valueArray;
    }

    public Interpolation1DLUT(double[] keys, double[] values) {
        if (keys.length != values.length) {
            throw new IllegalArgumentException("key.length != value.length");
        }
        this.keyArray = keys;
        this.valueArray = values;
    }

    /**
     *
     * @param key double
     * @param keys double[]
     * @param values double[]
     * @param type Algo
     * @param ensureTrendMode boolean 是否處於確保趨勢的模式下
     * @return double
     */
    protected final double interpolationValue(double key, double[] keys,
            double[] values) {
        if (key == -key) {
            key = 0;
        }
        int index = Searcher.leftNearBinarySearch(keys, key);
        int interpoStart = 0;
        boolean head = false;
        boolean tail = false;

        //==========================================================================
        // 內插位置點的判斷
        //==========================================================================
        if (index == 0) {
            interpoStart = index;
            head = true;
        } else if (index == (keys.length - 1)) {
            interpoStart = index - 3;
            tail = true;
        } else if (index == (keys.length - 2)) {
            interpoStart = index - 2;
            tail = true;
        } else if (index == -1) {
            throw new IndexOutOfBoundsException("key[" + key + "] out of keys["
                    + keys[0] + "~" + keys[keys.length - 1]
                    + "]");
        } else {
            interpoStart = index - 1;
        }
        //==========================================================================
        double result = Double.NaN;

        double[] xn = new double[4];
        double[] yn = new double[4];

        System.arraycopy(keys, interpoStart, xn, 0, 4);
        System.arraycopy(values, interpoStart, yn, 0, 4);


        if (tail) {
            xn = DoubleArray.getRangeCopy(xn, 2, 3);
            yn = DoubleArray.getRangeCopy(yn, 2, 3);
        } else if (head) {
            xn = DoubleArray.getRangeCopy(xn, 0, 1);
            yn = DoubleArray.getRangeCopy(yn, 0, 1);
        } else {
            xn = DoubleArray.getRangeCopy(xn, 1, 2);
            yn = DoubleArray.getRangeCopy(yn, 1, 2);
        }

        result = Interpolation.interpolate(xn, yn, key);


        return result;
    }

    public static void main(String[] args) {

        double[] value = new double[]{
            0.58, 0.63, 0.68, 0.689, 0.691, 0.74};
        double[] key = new double[]{
            70.0, 75.0, 85.0, 95.0, 98.0, 100.0};

        Interpolation1DLUT lut2 = new Interpolation1DLUT(key, value);
        System.out.println(lut2.getValue(71.9));

//    System.out.println(lut2.getValue(69.9));
    }

    public double getValue(double key) {
        int index = Arrays.binarySearch(keyArray, key);
        if (index >= 0) {
            return valueArray[index];
        } else {
            return interpolationValue(key, keyArray, valueArray);
        }
    }
}

class Searcher {

    /**
     * 以二元搜尋找到左邊最接近的索引值
     *
     * @param a double[]
     * @param key double
     * @return int
     */
    public final static int leftNearBinarySearch(double[] a, double key) {
        int result = Arrays.binarySearch(a, key);
        return leftNearBinarySearch0(a.length, result);
    }

    /**
     * 以二元搜尋找到左邊最接近的索引值
     *
     * @param arrayLength int
     * @param binarySearchResult int
     * @return int
     */
    public final static int leftNearBinarySearch0(int arrayLength,
            int binarySearchResult) {
        int result = binarySearchResult;
        if (result < -1) {
            //interstion的場合
            result = -result;
            if (result > arrayLength) {
//        return result - 1;
                return -1;
            } else {
                return result - 2;
            }
        } else if (result != 0 && result != -1) {
            //一般的場合
            return result - 1;
        } else {
            //為0 or -1的場合
            return result;
        }
    }
}


class DoubleArray {

    /**
     * Extract a section of an array. Example:<br>
     * <code>
     * double[] a = {00,11,22,33,44,55,66,77,88,99};<br>
     * double[] z = getRangeCopy(a, 2, 5);<br>
     * result is:<br>
     * 22  33  44  55<br>
     * </code>
     *
     * @param M Input array
     * @param j1 Index of first term to get
     * @param j2 Index of last term to get
     * @return An array with j2-j1+1 elements
     */
    public static double[] getRangeCopy(double[] M, int j1, int j2) {
        double[] array = new double[j2 - j1 + 1];
        System.arraycopy(M, j1, array, 0, j2 - j1 + 1);
        return array;
    }
}