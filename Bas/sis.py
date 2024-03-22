import os #leer varaibles de entorno
from dotenv import load_dotenv
import schedule

load_dotenv() #cagar variables de entorno 

intervalo = os.getenv("INTERVAL")
mensaje = os.getenv("MESSAGE")

def funcion_print():
    print(mensaje)

schedule.every(intervalo).seconds.do(funcion_print)

while True:
    schedule.run_pending()