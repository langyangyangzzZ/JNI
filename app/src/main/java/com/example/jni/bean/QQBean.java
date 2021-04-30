package com.example.jni.bean;

/**
 * author : Tiaw.
 * date   : 4/30/21
 * 博客：https://blog.csdn.net/weixin_44819566
 * desc   :
 */
public class QQBean {

    private int max;
    private int min;
    private int value;
    private String name;

    @Override
    public String toString() {
        return "QQBean{" +
                "max=" + max +
                ", min=" + min +
                ", value=" + value +
                ", name='" + name + '\'' +
                '}';
    }

    public int getMax() {
        return max;
    }

    public void setMax(int max) {
        this.max = max;
    }

    public int getMin() {
        return min;
    }

    public void setMin(int min) {
        this.min = min;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public QQBean(int max, int min, int value, String name) {
        this.max = max;
        this.min = min;
        this.value = value;
        this.name = name;
    }
}
