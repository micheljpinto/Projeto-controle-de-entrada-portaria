#include <MySQL_Generic.h>
#include <WiFi.h>


char ssid[]           = "default0";         // your network SSID (name)
char pass[]           = "@hfj0601";         // your network password
char user[]           = "sql10521606";      // MySQL user login username
char password[]       = "YPeQmnMEeL";       // MySQL user login password
char dbTable[]        = "michel_teste_db";
#define dbserver      "sql10.freemysqlhosting.net"

uint16_t server_port    = 3306;   
char default_database[] = "sql10521606";           
char default_table[]    = "entrada";  


#define USING_HOST_NAME     true //caso use dns deixar como true, se usar ip defina false

#if USING_HOST_NAME
  // Optional using hostname, and Ethernet built-in DNS lookup
  char server[] =dbserver ; // change to your server's hostname/URL
#else
  IPAddress server(dbserver);
#endif

//Constantes do mysql  
MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

//WiFiClient client;// definido na library generic

String insertSensores(float valor) 
{
  // Função pode ser replicada para desenvolver a operação requerida pelo banco, insert, update e etc.

  //String INSERT_DATA = String("INSERT INTO ")+dbTable +".sensores VALUES (CURRENT_DATE(),CURRENT_TIME,'sensor'," + String(valor)+")";
  //Serial.print(INSERT_DATA);
  //return INSERT_DATA;

/*   char INSERT_DATA[] = "INSERT INTO sql10521606.sensores VALUES (CURRENT_TIMESTAMP(),CURRENT_TIME,'sensor', %f)"; */

  char INSERT_DATA[] =  "INSERT INTO sql10521606.Entrada ( `Data`, `Tag`, `Nome`) VALUES ( NOW(), '55555555', 'Michel de Jesus Pinto')";

  char query[100]; 
  sprintf(query, INSERT_DATA, valor );
  Serial.print(query);
  return query;
}

void runInsert(String value)
{
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected())
  {
    MYSQL_DISPLAY(value);
    
    // Execute the query
    // KH, check if valid before fetching
    if ( !query_mem.execute(value.c_str()) )
    {
      MYSQL_DISPLAY("Insert error");
    }
    else
    {
      MYSQL_DISPLAY("Data Inserted.");
    }
  }
  else
  {
    MYSQL_DISPLAY("Disconnected from Server. Can't insert.");
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000); // wait for serial port to connect

  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    MYSQL_DISPLAY0(".");
  }

  // print out info about the connection:
  MYSQL_DISPLAY1("Connected to network. My IP address is:", WiFi.localIP());

  MYSQL_DISPLAY3("Connecting to SQL Server @", server, ", Port =", server_port);
  MYSQL_DISPLAY5("User =", user, ", PW =", password, ", DB =", default_database);
}

void loop()
{
  MYSQL_DISPLAY("Connecting...");
  
  if (conn.connect(server, server_port, user, password))
  {
    delay(500);
    runInsert(insertSensores(55.88));
    conn.close();                     // close the connection
  } 
  else 
  {
    MYSQL_DISPLAY("\nConnect failed. Trying again on next iteration.");
  }

  delay(60000);
}
