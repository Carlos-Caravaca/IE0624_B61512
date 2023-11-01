import time
import requests
import random
import serial

# Configura la URL y el token de acceso de ThingsBoard
#ser = serial.Serial('COMX', 115200)  # Reemplaza 'COMX' con el puerto serie correcto y la velocidad correcta
access_token = 'mtzd36o3ynydaptt4ywh'
url = f'https://iot.eie.ucr.ac.cr/api/v1/{access_token}/telemetry'

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
        # Datos simulados para el giroscopio y el nivel de batería
        gyro_data = {
            "Eje X": random.uniform(-100, 100),
            "Eje Y": random.uniform(-100, 100),
            "Eje Z": random.uniform(-100, 100)
        }
        battery_data = {"Batería": round(random.uniform(4.5, 5.5), 2)}

        # Combinar datos en un solo diccionario
        combined_data = {**gyro_data, **battery_data}

        # Enviar los datos a ThingsBoard
        send_data_to_thingsboard(combined_data)

        # Espera un intervalo de tiempo (puedes ajustarlo)
        time.sleep(10)  # Espera 10 segundos

except KeyboardInterrupt:
    print("Terminado")
