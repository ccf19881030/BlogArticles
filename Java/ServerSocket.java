```java
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

    public static void main(String[] args) {
        try {
            ServerSocket serverSock = new ServerSocket(9996);
            Socket socket = serverSock.accept();
            System.out.println(serverSock.getLocalPort());

            String line;
            BufferedReader is = new BufferedReader(new
                    InputStreamReader(socket.getInputStream()));
            PrintWriter os = new PrintWriter(socket.getOutputStream());
            
            BufferedReader sin = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("客户端：" + is.readLine());
            line = sin.readLine();
            while(!line.equals("bye")){
                os.println(line);
                os.flush();
                System.out.println("服务器：" + line);
                System.out.println("客户端：" + is.readLine());
                line = sin.readLine();
            }

            os.close();
            is.close();
            socket.close();
            serverSock.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}

```
