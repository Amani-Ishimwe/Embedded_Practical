import serial
import paho.mqtt.client as mqtt

# ================= SERIAL =================
SERIAL_PORT = "COM6"   # CHANGE if needed
BAUD_RATE = 9600

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

# ================= MQTT =================
BROKER = "broker.benax.rw"
TOPIC = "rwanda/arduino/dht11/temperature"

client = mqtt.Client()
client.connect(BROKER, 1883, 60)

print("Monitoring temperature...\n")

# ================= LOOP =================
while True:
    line = ser.readline().decode().strip()

    if not line:
        continue

    # Ignore any bad text (extra safety)
    if "Sensor" in line:
        continue

    try:
        temp = float(line)

        print("Temperature:", temp)

        client.publish(TOPIC, temp)

    except:
        continue