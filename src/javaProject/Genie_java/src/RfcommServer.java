import java.io.IOException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.io.PrintWriter;

import javax.bluetooth.LocalDevice;
import javax.bluetooth.ServiceRecord;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;
import javax.microedition.io.StreamConnectionNotifier;
public class RfcommServer {
    static final String serverUUID = "0000110100001000800000805F9B34FB";

    private StreamConnectionNotifier server = null;

    public RfcommServer() throws IOException {
        server = (StreamConnectionNotifier) Connector.open(
                "btspp://localhost:" + serverUUID,
                Connector.READ_WRITE, true
        );
        ServiceRecord record = LocalDevice.getLocalDevice().getRecord(server);
        LocalDevice.getLocalDevice().updateRecord(record);
    }

    public Session accept() throws IOException {
        log("Accept");
        StreamConnection channel = server.acceptAndOpen();
        log("Connect");
        return new Session(channel);
    }
    public void dispose() {
        log("Dispose");
        if (server  != null) try {server.close();} catch (Exception e) {/*ignore*/}
    }

    static class Session implements Runnable {
        private StreamConnection channel = null;
        private InputStream btIn = null;
        private OutputStream btOut = null;

        public Session(StreamConnection channel) throws IOException {
            this.channel = channel;
            this.btIn = channel.openInputStream();
            this.btOut = channel.openOutputStream();
        }

        public void run() {
            try {
                byte[] buff = new byte[512];
                int n = 0;
                int cnt=0;
                while ((n = btIn.read(buff)) > 0) {
                	FileOutputStream output = new FileOutputStream("/Users/leedongwoo/Desktop/UserInfo/input.txt");
                	
                	String data = new String(buff, 0, n);
                	log("Receive:"+data);
                	output.write(data.getBytes());
                	
                    btOut.write(data.toUpperCase().getBytes());
                	btOut.flush();
                }
            } catch (Throwable t) {
                t.printStackTrace();
            } finally {
                close();
            }
        }
        public void close() {
            log("Session Close");
            if (btIn    != null) try {btIn.close();} catch (Exception e) {/*ignore*/}
            if (btOut   != null) try {btOut.close();} catch (Exception e) {/*ignore*/}
            if (channel != null) try {channel.close();} catch (Exception e) {/*ignore*/}
        }
    }

    public static void main(String[] args) throws Exception {
    	
        RfcommServer server = new RfcommServer();
        while (true) {
            Session session = server.accept();
            new Thread(session).start();
        }
    }
    private static void log(String msg) {
        System.out.println("["+(new Date()) + "] " + msg);
    }
}