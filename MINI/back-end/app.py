from flask import Flask, request, jsonify
from flask_cors import CORS  # Import CORS

app = Flask(__name__)
CORS(app)  # Initialize CORS

# In-memory data store for demonstration purposes
battery_data = {
    "batteryStatus": True,
    "voltage": 12.6,
    "current": 1.5,
    "temperature": 25.0
}

@app.route('/data', methods=['GET'])
def get_data():
    return jsonify(battery_data)

@app.route('/data', methods=['POST'])
def update_data():
    global battery_data
    battery_data = request.json
    return jsonify({"status": "success"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
