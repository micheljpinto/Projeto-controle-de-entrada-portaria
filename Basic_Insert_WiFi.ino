/*********************************************************************************************************************************
  Basic_Insert_WiFi.ino

  Library for communicating with a MySQL or MariaDB Server

  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.

  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
  MySQL Connector/Arduino Example : basic insert

  This example demonstrates how to issue an INSERT query to store data in a
  table. For this, we will create a special database and table for testing.
  The following are the SQL commands you will need to run in order to setup
  your database for running this sketch.

  CREATE DATABASE test_arduino;
  CREATE TABLE test_arduino.hello_arduino (
    num integer primary key auto_increment,
    message char(40),
    recorded timestamp
  );

  Here we see one database and a table with three fields; a primary key that
  is an auto_increment, a string, and a timestamp. This will demonstrate how
  to save a date and time of when the row was inserted, which can help you
  determine when data was recorded or updated.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Create the database and table as shown above.
  2) Change the address of the server to the IP address of the MySQL server
  3) Change the user and password to a valid MySQL user and password
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe
  8) After the sketch has run for some time, open a mysql client and issue
     the command: "SELECT * FROM test_arduino.hello_arduino" to see the data
     recorded. Note the field values and how the database handles both the
     auto_increment and timestamp fields for us. You can clear the data with
     "DELETE FROM test_arduino.hello_arduino".

  Note: The MAC address can be anything so long as it is unique on your network.

  Created by: Dr. Charles A. Bell
*/

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