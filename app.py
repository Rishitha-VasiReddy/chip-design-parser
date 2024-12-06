from flask import Flask, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Enable CORS to allow front-end access

# Sample report endpoint
@app.route('/report', methods=['GET'])
def report():
    # Replace with actual database fetch logic
    data = [
        {"Type": "Module", "Name": "example"},
        {"Type": "Input", "Name": "clk"},
        {"Type": "Output", "Name": "reset"},
        {"Type": "Wire", "Name": "data"},
        {"Type": "Assign", "Name": "data = clk & reset"}
    ]
    return jsonify(data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)
