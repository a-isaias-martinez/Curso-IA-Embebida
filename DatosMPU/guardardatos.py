import serial
import time

# Configura el puerto serial y velocidad (ajusta según tu sistema)
PORT = '/dev/ttyUSB0'
BAUD_RATE = 115200
FILENAME = 'Pruebas/DatosMPU/hifive.csv'

# Parámetros del muestreo
FILAS_POR_MUESTREO = 225
NUM_MUESTREOS = 15
TOTAL_FILAS = FILAS_POR_MUESTREO * NUM_MUESTREOS

def es_linea_valida(line):
    partes = line.split(',')
    if len(partes) != 6:
        return False
    try:
        [float(p) for p in partes]
        return True
    except ValueError:
        return False

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Esperar a que la ESP32 reinicie

    with open(FILENAME, 'w') as file:
        print(f"Grabando datos en {FILENAME}... Recibiendo {TOTAL_FILAS} filas.")
        fila_count = 0

        while fila_count < TOTAL_FILAS:
            line = ser.readline().decode('utf-8').strip()
            if es_linea_valida(line):
                print(f"{fila_count+1}: {line}")
                file.write(line + '\n')
                fila_count += 1

        print(f"\nLectura finalizada. Se recibieron {fila_count} filas válidas.")

except KeyboardInterrupt:
    print("\nInterrupción detectada por el usuario.")
finally:
    if ser.is_open:
        ser.close()
        print("Puerto serial cerrado correctamente.")
