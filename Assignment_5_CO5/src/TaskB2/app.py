from flask import Flask, jsonify
import socket

app = Flask(__name__)

@app.route("/")
def index():
    return jsonify({
        "service": "SIMATS University Result Portal",
        "student": "Kavya Sree T",
        "register_number": "192524444",
        "course": "CSA0404 Operating Systems",
        "host_pod": socket.gethostname(),
        "status": "PUBLISHED"
    })

@app.route("/health")
def health():
    return jsonify({"status": "healthy"}), 200
