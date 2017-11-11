package com.panjq.opencv.opencvdemo;

/**
 * Created by panjq1 on 2017/11/10.
 */

import android.os.Environment;

import java.io.File;
public class FileUtil {
    public static String genAbsoluteFolderPath(String subDir) {
        String sdPath = getSDPath();
        if (sdPath == null) {
            return null;
        } else {
            String folderPath = sdPath + "/" + subDir;
            File destDir = new File(folderPath);
            if (!destDir.exists()) {
                destDir.mkdirs();
            }
            return folderPath;
        }
    }
    public static String getSDPath() {
        File sdDir = null;
        boolean sdCardExist = Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED);
        if (sdCardExist) {
            sdDir = Environment.getExternalStorageDirectory();
        }
        return sdDir.toString();
    }

    /**
     * 删除根目录下的所有文件
     * @param root
     */
    public static void deleteAllFiles(File root) {
        File files[] = root.listFiles();
        if (files != null)
            for (File f : files) {
                if (f.isDirectory()) { // 判断是否为文件夹
                    deleteAllFiles(f);
                    try {
                        f.delete();
                    } catch (Exception e) {
                    }
                } else {
                    if (f.exists()) { // 判断是否存在
                        deleteAllFiles(f);
                        try {
                            f.delete();
                        } catch (Exception e) {
                        }
                    }
                }
            }
    }
}
