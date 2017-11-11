package com.panjq.opencv.opencvdemo;

/**
 * Created by panjq1 on 2017/11/10.
 */

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;


import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
public class CopyFileTask extends AsyncTask<Void,Void,Void> {
    private final static String idPhotoPath = FileUtil.genAbsoluteFolderPath("Dlib");
    private  static String path1 = idPhotoPath+"/shape_predictor_68_face_landmarks.dat";
    public   static String path2 = idPhotoPath+"/landmark_model.dat";


    private Context context;

    public void setData(Context context) {
        this.context = context.getApplicationContext();
    }

    @Override
    protected Void doInBackground(Void... params) {
//        FileUtil.genAbsoluteFolderPath("ID_Photo");\
        if(taskLiteneter != null){
            taskLiteneter.onTaskStart();
        }
        List<File> list = new ArrayList<>();
        list.add(new File(path1));
        list.add(new File(path2));
        for(int i = 0; i< list.size();i++) {
            File file = list.get(i);
            if (!file.getParentFile().exists()) {
//                System.out.println("//不存在" + file.getParentFile());
                file.getParentFile().mkdirs();
            } else {
                System.out.println("//目录存在");
            }
//            if (!file.exists()) {
//            file2.mkdir();
            try {
                copyBigDataToSD(context, file.getName(), file.getAbsolutePath());

            } catch (Exception e) {
                e.printStackTrace();
            }
            //           }
        }
        Log.i(" CopyFileTask", "模型数据拷贝完成...");
        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        if(taskLiteneter != null){
            taskLiteneter.onTaskDone();
        }
    }


    private void copyBigDataToSD(Context context, String fileName, String strOutFileName) throws Exception {
        InputStream myInput;
        OutputStream myOutput = new FileOutputStream(strOutFileName);
        myInput = context.getAssets().open(fileName);

        byte[] buffer = new byte[1024];
        int length = myInput.read(buffer);
        while (length > 0) {
            myOutput.write(buffer, 0, length);
            length = myInput.read(buffer);
        }

        myOutput.flush();
        myInput.close();
        myOutput.close();
    }

    private TaskLiteneter taskLiteneter;

    public void setTaskDoneLiteneter(TaskLiteneter taskLiteneter) {
        this.taskLiteneter = taskLiteneter;
    }
    public interface TaskLiteneter{
        void onTaskStart();
        void onTaskDone();
    }
}
