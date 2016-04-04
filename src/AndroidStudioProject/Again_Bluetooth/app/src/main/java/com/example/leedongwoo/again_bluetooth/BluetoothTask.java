package com.example.leedongwoo.again_bluetooth;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.os.AsyncTask;
import android.os.ParcelUuid;
import android.util.Log;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

public class BluetoothTask {
    private static final String TAG = "BluetoothTask";


    /* UUID는 서버와 일치할 필요가 있다*/

    private static final UUID APP_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private MainActivity activity;
    private BluetoothAdapter bluetoothAdapter;
    private BluetoothDevice bluetoothDevice = null;
    private BluetoothSocket bluetoothSocket;
    private InputStream btIn;
    private OutputStream btOut;

    public BluetoothTask(MainActivity activity) {
        this.activity = activity;
    }

    //블루투스의 초기화
    public void init() {
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            activity.errorDialog("This device is not implement Bluetooth.");
            return;
        }
        if (!bluetoothAdapter.isEnabled()) {
            // TODO: ユーザに許可を求める処理。
            activity.errorDialog("This device is disabled Bluetooth.");
            return;
        }
    }

    // 페어링 끝낸 데이터베이스 정보를 되돌린다. 디바이스 선택 다이얼로그용이다.
    public Set<BluetoothDevice> getPairedDevices() {
        return bluetoothAdapter.getBondedDevices();
    }


    /*비동기로 지정된 디바이스의 접속을 재개시한다.
      선택 다이얼로그 부터 선택된 디바이스를 설정한다.
     */
    public void doConnect(BluetoothDevice device) {
        bluetoothDevice = device;
        try {
            bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(APP_UUID);
            new ConnectTask().execute();
        } catch (IOException e) {
            Log.e(TAG, e.toString(), e);
            activity.errorDialog(e.toString());
        }
    }


    //비동기로 블루투스의 접촉을 끝낸다.
    public void doClose() {
        new CloseTask().execute();
    }

    //비동기로 블루투스의 접촉을 닫는다.
    public void doSend(String msg) {
        new SendTask().execute(msg);
    }

    /*
    블루투스와 접촉을 개시하는 비동기 Task
    시간이 걸리는 경우가 있기 때문에 process dialog를 표시한다
    쌍방향이 스트림을 열때까지
     */
    private class ConnectTask extends AsyncTask<Void, Void, Object> {
        @Override
        protected void onPreExecute() {
            activity.showWaitDialog("블루투스 연결 중 입니다");
        }

        @Override
        protected Object doInBackground(Void... params) {
            try {
                bluetoothSocket.connect();
                btIn = bluetoothSocket.getInputStream();
                btOut = bluetoothSocket.getOutputStream();
            } catch (Throwable t) {
                doClose();
                return t;

            }
            return null;
        }

        @Override
        protected void onPostExecute(Object result) {

            if (result instanceof Throwable) {
                Log.e(TAG, result.toString(), (Throwable) result);
                activity.errorDialog(result.toString());

            } else {
                activity.hideWaitDialog();
            }
        }
    }

    /*
    블루투스의 접속을 종료하는 비동기 테스크
     */
    private class CloseTask extends AsyncTask<Void, Void, Object> {
        @Override
        protected Object doInBackground(Void... params) {
            try {
                try{btOut.close();}catch(Throwable t){/*ignore*/}
                try{btIn.close();}catch(Throwable t){/*ignore*/}
                bluetoothSocket.close();
            } catch (Throwable t) {
                return t;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Object result) {
            if (result instanceof Throwable) {
                Log.e(TAG,result.toString(),(Throwable)result);
                activity.errorDialog(result.toString());
            }
        }
    }

    /*
    서버와 메시지 송수신을 실행하는 비동기 테스크
     */
    private class SendTask extends AsyncTask<String, Void, Object> {
        @Override
        protected Object doInBackground(String... params) {
            try {
                btOut.write(params[0].getBytes("UTF-8"));

                btOut.flush();

                byte[] buff = new byte[512];
                int len = btIn.read(buff); // TODO:ループして読み込み

                return new String(buff, 0, len);
            } catch (Throwable t) {
                doClose();
                return t;
            }
        }


        @Override
        protected void onPostExecute(Object result) {
            if (result instanceof Exception) {
                Log.e(TAG,result.toString(),(Throwable)result);
                activity.errorDialog(result.toString());
            } else {
                // 結果を画面に反映。
                //activity.doSetResultText(result.toString());
            }
        }
    }
}