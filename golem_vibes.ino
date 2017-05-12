

#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

int status = WL_IDLE_STATUS;
char ssid[] = "Fat Coloc";      // your network SSID (name)
char pass[] = "V0apqmwnzoskxneidjcn!";

unsigned int localPort = 8888;      // local port to listen for UDP packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

void routeTone(OSCMessage &msg, int addrOffset ){
	Serial.println("Tone received");

}

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	// check for the presence of the shield:
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present");
		// don't continue:
		while (true);
	}

	String fv = WiFi.firmwareVersion();
	if (fv != "1.1.0") {
		Serial.println("Please upgrade the firmware");
	}

	// attempt to connect to Wifi network:
	while (status != WL_CONNECTED) {
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		status = WiFi.begin(ssid, pass);

		// wait 10 seconds for connection:
		delay(10000);
	}

	Serial.println("Connected to wifi");
	printWifiStatus();
	Serial.println("Waiting for OSC");

	Udp.begin(localPort);
}

void loop() {
	// wait to see if a reply is available
	OSCBundle bundleIN;
	int size;
	if((size = Udp.parsePacket())>0)	{

		while(size--) {
			bundleIN.fill(Udp.read());
		}

		if(!bundleIN.hasError()) {
			OSCMessage osc = bundleIN.getOSCMessage(0);
			Serial.println("Received OSC" + osc.getType(0));
			bundleIN.route("/tone", routeTone);
		}
		else {
			OSCErrorCode errorCode = bundleIN.getError();
			Serial.println(errorCode);
		}
	}
}



void printWifiStatus() {
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
}










