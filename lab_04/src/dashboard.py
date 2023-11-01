import serial
import requests
import json
import ssl, socket, time
import paho.mqtt.client as mqtt

# Configura el puerto serial/USB
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Reemplaza con el puerto correcto

# Configura la URL y el token de acceso de ThingsBoard
access_token = 'mtzd36o3ynydaptt4ywh'
url = f'https://iot.eie.ucr.ac.cr/api/v1/{access_token}/telemetry'

# Configuración de la comunicación serial (ajusta el puerto según tu sistema)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

# URL del servidor ThingsBoard (ajusta la URL y el token de acceso)
thingsboard_url = "https://iot.eie.ucr.ac.cr"

def send_data_to_thingsboard(data):
    headers = {'Content-Type': 'application/json'}
    payload = {"ts": int(time.time() * 1000), "values": data}
    url = f"{thingsboard_url}/api/v1/{access_token}/telemetry"
    response = requests.post(url, json=payload, headers=headers)
    
    if response.status_code == 200:
        print("Datos enviados exitosamente a ThingsBoard")
    else:
        print("Error al enviar datos a ThingsBoard")

try:
    while True:
        # Leer datos del puerto serial (ajusta según tu protocolo de comunicación)
        serial_data = ser.readline().decode().strip()
        
        # Procesar los datos del giroscopio y nivel de batería (ajusta según tus datos)
        gyro_data = {"gyro_x": 123, "gyro_y": 456, "gyro_z": 789}
        battery_data = {"battery_voltage": 5.46}

        # Combinar datos en un solo diccionario
        combined_data = {**gyro_data, **battery_data}

        # Enviar los datos a ThingsBoard
        send_data_to_thingsboard(combined_data)

except KeyboardInterrupt:
    ser.close()