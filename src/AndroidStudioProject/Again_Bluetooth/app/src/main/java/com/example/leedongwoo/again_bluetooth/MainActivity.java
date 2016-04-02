package com.example.leedongwoo.again_bluetooth;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.lang.reflect.GenericArrayType;
import java.util.ArrayList;
import java.util.Set;

import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothDevice;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.internal.widget.AdapterViewCompat;
import android.text.Editable;
import android.util.Log;
import android.util.Xml;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.text.TextWatcher;
import android.widget.Toast;
import android.widget.Spinner;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.io.BufferedReader;
import java.io.IOException;
import java.lang.StringBuilder;
import java.lang.CharSequence;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import android.widget.TextView;
import java.io.StringReader;
import android.widget.ArrayAdapter;
import org.xml.sax.InputSource;
import android.widget.AdapterView.OnItemClickListener;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathFactory;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ListView;

public class MainActivity extends Activity /*implements OnItemSelectedListener*/{
    private final static int DEVICES_DIALOG = 1;
    private final static int ERROR_DIALOG = 2;

    private BluetoothTask bluetoothTask = new BluetoothTask(this);

    private ProgressDialog waitDialog;
    private EditText editTextName;//editText1은 사용자의 이름
    private EditText editTextAge;//editAge는 사용자의 나이
    private EditText editTextGender;//editTextGender는 사용자의 성별
    private EditText editText2;
    private EditText editLocation;//위치를 editText에 나타내주기 위함
    private Button myLocation;//위치를 받아오는 버튼
    private EditText busLocation;
    private String errorMessage = "";
    private InputStream btIn;
    private OutputStream btOut;
    public static String select_item = "";
    ArrayList<String> arraylist;

    ListView m_ListView;
    ArrayAdapter<String> m_Adapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editTextName = (EditText) findViewById(R.id.editName);//editTextName이 사용자의 이름을 받는다.
        editTextAge = (EditText) findViewById(R.id.editAge);//editTextAge는 사용자의 나이를 받아온다
        editTextGender = (EditText) findViewById(R.id.editGender);//editTextGender는 사용자의 성별을 받아온다.
        editText2 = (EditText) findViewById(R.id.editText2);
        //editLocation = (EditText) findViewById(R.id.editLocation);// 사용자의 정보를 출력해준다
        myLocation = (Button) findViewById(R.id.locationAddress);//자기 위치정보 받아오기 위도 경도
        busLocation = (EditText) findViewById(R.id.editBus);

        myLocation.setOnClickListener(new View.OnClickListener() {//버스정보 위치정보 받아오는 버튼
            @Override
            public void onClick(View view) {
                try {
                    new Bus().getBusInformation();
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        });

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        Button sendBtn = (Button) findViewById(R.id.sendBtn);
        sendBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                String msg = editTextName.getText().toString();
                String msgAge = editTextAge.getText().toString();
                String msgGender = editTextGender.getText().toString();
                String msgBus = busLocation.getText().toString();
                String newL = msg + "\n" + msgAge + "\n" + msgGender;
                bluetoothTask.doSend(newL+"\n"+msgBus);
            }
        });

        Button resetBtn = (Button) findViewById(R.id.resetBtn);
        resetBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                restart();
            }
        });
    }

    @SuppressWarnings("deprecation")
    @Override
    protected void onResume() {
        super.onResume();
        // Bluetooth初期化
        bluetoothTask.init();
        // ペアリング済みデバイスの一覧を表示してユーザに選ばせる。
        showDialog(DEVICES_DIALOG);
    }

    @Override
    protected void onDestroy() {
        bluetoothTask.doClose();
        super.onDestroy();
    }

    public void doSetResultText(String text) {
        editText2.setText(text);
    }

    protected void restart() {
        Intent intent = this.getIntent();
        this.finish();
        this.startActivity(intent);
    }

    //----------------------------------------------------------------
    // 以下、ダイアログ関連
    @Override
    protected Dialog onCreateDialog(int id) {
        if (id == DEVICES_DIALOG) return createDevicesDialog();
        if (id == ERROR_DIALOG) return createErrorDialog();
        return null;
    }

    @SuppressWarnings("deprecation")
    @Override
    protected void onPrepareDialog(int id, Dialog dialog) {
        if (id == ERROR_DIALOG) {
            ((AlertDialog) dialog).setMessage(errorMessage);
        }
        super.onPrepareDialog(id, dialog);
    }

    public Dialog createDevicesDialog() {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);
        alertDialogBuilder.setTitle("Select device");

        // ペアリング済みデバイスをダイアログのリストに設定する。
        Set<BluetoothDevice> pairedDevices = bluetoothTask.getPairedDevices();
        final BluetoothDevice[] devices = pairedDevices.toArray(new BluetoothDevice[0]);
        String[] items = new String[devices.length];
        for (int i = 0; i < devices.length; i++) {
            items[i] = devices[i].getName();
        }

        alertDialogBuilder.setItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                // 選択されたデバイスを通知する。そのまま接続開始。
                bluetoothTask.doConnect(devices[which]);
            }
        });
        alertDialogBuilder.setCancelable(false);
        return alertDialogBuilder.create();
    }

    @SuppressWarnings("deprecation")
    public void errorDialog(String msg) {
        if (this.isFinishing()) return;
        this.errorMessage = msg;
        this.showDialog(ERROR_DIALOG);
    }

    public Dialog createErrorDialog() {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);
        alertDialogBuilder.setTitle("Error");
        alertDialogBuilder.setMessage("");
        alertDialogBuilder.setPositiveButton("Exit", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                finish();
            }
        });
        return alertDialogBuilder.create();
    }

    public void showWaitDialog(String msg) {
        if (waitDialog == null) {
            waitDialog = new ProgressDialog(this);
        }
        waitDialog.setMessage(msg);
        waitDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        waitDialog.show();
    }

    public void hideWaitDialog() {
        waitDialog.dismiss();
    }

    //GPS로 나의 정보 받아오기
    public void startLocationService() {
        LocationManager manager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);

        GPSListener gpsListener = new GPSListener();
        long minTime = 1000;
        float minDistance = 30;

        //GPS를 이용한 위치 요청
        //manager.requestLocationUpdates(LocationManager.GPS_PROVIDER,minTime,minDistance,gpsListener);
        manager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, minTime, minDistance, gpsListener);

        //Location lastLocation = manager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

        //manager.requestLocationUpdates(LocationManager.GPS_PROVIDER,minTime,minDistance,gpsListener);
        Toast.makeText(getApplicationContext(), "위치를 받아오기 시작합니다.\n잠시만 기다려주세요.", Toast.LENGTH_SHORT).show();
    }

    private class GPSListener implements LocationListener {

        public void onLocationChanged(Location location) {
            //capture location data sent by current provider
            Double latitude = location.getLatitude();
            Double longitude = location.getLongitude();

            String msg = "위도 : " + latitude + "\n경도:" + longitude;
            Log.i("GPSLocationService", msg);
            Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();
            editLocation.setText(msg);

        }

        public void onProviderDisabled(String provider) {
        }

        public void onProviderEnabled(String provider) {
        }

        public void onStatusChanged(String provider, int status, Bundle extras) {
        }

    }

    private class Bus {
        public void getBusInformation() throws Exception {
            String temp[] = new String[9];
            StringBuilder urlBuilder = new StringBuilder("http://ws.bus.go.kr/api/rest/stationinfo/getStationByPos");
            urlBuilder.append("?" + URLEncoder.encode("ServiceKey", "UTF-8") + "=" + "wZJqvet7sRGoIz0NXp7XRzJtGN69oSsQ15DG0ZFD352NgAa%2Bbx7LMJg24Ly9ZXifmlh%2FYaFczztGz9CY9%2FHX6w%3D%3D");
            urlBuilder.append("&" + URLEncoder.encode("tmX", "UTF-8") + "=" + URLEncoder.encode("126.9972045", "UTF-8")); /*기준위치 X(WGS84)*/
            urlBuilder.append("&" + URLEncoder.encode("tmY", "UTF-8") + "=" + URLEncoder.encode("37.6105214", "UTF-8")); /*기준위치 Y(WGS84)*/
            urlBuilder.append("&" + URLEncoder.encode("radius", "UTF-8") + "=" + URLEncoder.encode("300", "UTF-8")); /*검색반경(0~1500m)*/
            urlBuilder.append("&" + URLEncoder.encode("numOfRows", "UTF-8") + "=" + URLEncoder.encode("3", "UTF-8")); /*검색건수*/
            urlBuilder.append("&" + URLEncoder.encode("pageNo", "UTF-8") + "=" + URLEncoder.encode("1", "UTF-8")); /*페이지 번호*/
            URL url = new URL(urlBuilder.toString());

            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.setRequestProperty("Content-type", "application/json");

            //System.out.println("Response code : " + conn.getResponseCode());
            BufferedReader rd;
            if (conn.getResponseCode() >= 200 && conn.getResponseCode() <= 300) {
                rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            } else {
                rd = new BufferedReader(new InputStreamReader(conn.getErrorStream()));
            }

            StringBuilder sb = new StringBuilder();
            String line;

            while ((line = rd.readLine()) != null) {
                sb.append(line);
                //rd.close();
            }

            conn.disconnect();
            //busLocationNum1.setText(sb.toString());
            String xml = sb.toString();
            InputSource is = new InputSource(new StringReader(xml));
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(is);

            XPath xpath = XPathFactory.newInstance().newXPath();

            NodeList busId = (NodeList)xpath.evaluate("//itemList/arsId",document, XPathConstants.NODESET);
            NodeList busName = (NodeList)xpath.evaluate("//itemList/stationNm",document,XPathConstants.NODESET);

            temp[0]=(busId.item(0).getTextContent()+" - "+busName.item(0).getTextContent());
            temp[1]=(busId.item(1).getTextContent()+" - "+busName.item(1).getTextContent());
            temp[2]=(busId.item(2).getTextContent()+" - "+busName.item(2).getTextContent());
            temp[3]=(busId.item(3).getTextContent()+" - "+busName.item(3).getTextContent());
            temp[4]=(busId.item(4).getTextContent()+" - "+busName.item(4).getTextContent());
            temp[5]=(busId.item(5).getTextContent()+" - "+busName.item(5).getTextContent());
            temp[6]=(busId.item(6).getTextContent()+" - "+busName.item(6).getTextContent());
            temp[7]=(busId.item(7).getTextContent()+" - "+busName.item(7).getTextContent());
            temp[8]=(busId.item(8).getTextContent()+" - "+busName.item(8).getTextContent());

            m_Adapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.simpleitem);

            // Xml에서 추가한 ListView 연결
            m_ListView = (ListView) findViewById(R.id.busList);

            // ListView에 어댑터 연결
            m_ListView.setAdapter(m_Adapter);
            m_ListView.setOnItemClickListener(onClickListItem);
            m_Adapter.add(temp[0]);
            m_Adapter.add(temp[1]);
            m_Adapter.add(temp[2]);
            m_Adapter.add(temp[3]);
            m_Adapter.add(temp[4]);

        }
    }

    private OnItemClickListener onClickListItem = new OnItemClickListener() {

        @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
            // 이벤트 발생 시 해당 아이템 위치의 텍스트를 출력
            Toast.makeText(getApplicationContext(), m_Adapter.getItem(arg2), Toast.LENGTH_SHORT).show();
            busLocation.setText(m_Adapter.getItem(arg2));
            //bluetoothTask.doSend(m_Adapter.getItem(arg2));
        }
    };



}








