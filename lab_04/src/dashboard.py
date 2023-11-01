import serial
import requests
import json
import ssl, socket
import paho.mqtt.client as mqtt

# Configura el puerto serial/USB
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Reemplaza con el puerto correcto

# Configura la URL y el token de acceso de ThingsBoard
access_token = 'mtzd36o3ynydaptt4ywh'
url = f'https://iot.eie.ucr.ac.cr/api/v1/{access_token}/telemetry'

try:
    while True:
        # Leer datos del giroscopio y nivel de batería desde el puerto serial
        data = ser.readline().decode().strip()
        gyro_data, battery_level = data.split(',')

        # Crear un diccionario con los datos
        telemetry_data = {
            'gyroscope': gyro_data,
            'battery_level': battery_level,
        }

        # Enviar datos a ThingsBoard
        headers = {'Content-Type': 'application/json'}
        response = requests.post(url, data=json.dumps(telemetry_data), headers=headers)

        if response.status_code == 200:
            print('Datos enviados correctamente a ThingsBoard.')
        else:
            print(f'Error al enviar datos a ThingsBoard. Código de estado: {response.status_code}')

except KeyboardInterrupt:
    ser.close()
    print('Conexión serial cerrada.')

except Exception as e:
    print(f'Error: {str(e)}')
    ser.close()