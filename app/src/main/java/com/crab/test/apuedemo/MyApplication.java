/*
 * Copyright (C) 2021 XieChaoJun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.crab.test.apuedemo;

import android.app.Application;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MyApplication extends Application {
    private static final String CP_EXE_FILE_NAME = "testcp";

    @Override
    public void onCreate() {
        super.onCreate();
        Log.e("mytag", "MyApplication onCreate=" + this);
        boolean result = copyAssetAndWrite(CP_EXE_FILE_NAME);
        Log.e("mytag", "copyAssetAndWrite result=" + result);
        if (result) {
            String cpExePath = getCacheDir() + "/" + CP_EXE_FILE_NAME;
            File file = new File(cpExePath);
            result = file.setExecutable(true);
            Log.e("mytag", "setExecutable result=" + result);
        }
    }

    @Override
    public void onTerminate() {
        super.onTerminate();
        Log.e("mytag", "MyApplication onTerminate=" + this);
    }

    /**
     * 将asset文件写入缓存
     */
    private boolean copyAssetAndWrite(String fileName) {
        try {
            File cacheDir = getCacheDir();
            Log.e("mytag", "cacheDir is " + cacheDir.getAbsolutePath());
            if (!cacheDir.exists()) {
                boolean result = cacheDir.mkdirs();
                Log.e("mytag", "mkdir " + cacheDir.getAbsolutePath() + " result=" + result);
            }
            File outFile = new File(cacheDir, fileName);
            if (!outFile.exists()) {
                boolean res = outFile.createNewFile();
                if (!res) {
                    return false;
                }
            } else {
                if (outFile.length() > 10) {//表示已经写入一次
                    return true;
                }
            }
            InputStream is = getAssets().open(fileName);
            FileOutputStream fos = new FileOutputStream(outFile);
            byte[] buffer = new byte[4096];
            int byteCount;
            while ((byteCount = is.read(buffer)) != -1) {
                fos.write(buffer, 0, byteCount);
            }
            fos.flush();
            is.close();
            fos.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }
}
