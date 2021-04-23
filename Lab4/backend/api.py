import os
from flask import Flask, request
from flask_cors import CORS, cross_origin

app = Flask(__name__)
cors = CORS(app, resources={r"/images": {"origins" : "http://localhost:3000"}})

@app.route('/')
def index():
    return 'Server Works!'


@app.route('/images', methods=['POST'])
@cross_origin(origin='localhost', headers=['Content-Type', 'Authorization'])
def upload():
    f = request.files['image']
    f.save('images/unprocessed.png')

    process()

    return "Diddely done"


def process():
    cmd = 'lowpass_sequencial.out images/unprocessed.png images/processed.png'
    print(cmd)
    os.system(cmd)