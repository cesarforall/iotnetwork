from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/")
def index():
	return "<p>Iot Server</p>"

# Ejemplo de datos json
#{
#	"temperature": "25.5",
# 	"humidity": "60",
#	"timestamp": "2024-08-28 12:34:56"
#}

# Este endpoint maneja el método POST para subir los datos
@app.post("/api/v1/upload")
def upload_post():
	# Recupera el json enviado por el body
	data = request.get_json()

	# Verifica que todos los campos estén presentes
	if data and "temperature" in data and "humidity" in data and "timestamp" in data:
		temperature = data["temperature"]
		humidity = data["humidity"]
		timestamp = data["timestamp"]

		# Imprime los valores recibidos
		print(f"Temperature: {temperature}")
		print(f"Humidity: {humidity}")
		print(f"Timestamp: {timestamp}")

        	# Retorna una respuesta de éxito
		return jsonify({
			"message": "Datos recibidos correctamente",
			"data": {
				"temperature": temperature,
				"humidity": humidity,
				"timestamp": timestamp
			}
		}), 200
	else:
		# Retorna una respuesta de error si faltan datos
		return jsonify({
			"error": "Datos no válidos o faltantes. Verifica que se envíen 'temperature', 'humidity' y 'timestamp'"
		}), 400

# data/latest -> GET envia el último dato subido
# data/all -> GET envia todos los datos

if __name__ == "__main__":
	app.run()
