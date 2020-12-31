package com.crab.test.apuedemo.jni;

public class HelloJni {
    static {
        System.loadLibrary("hellojni");
    }
    public static native void sayHello();
}
