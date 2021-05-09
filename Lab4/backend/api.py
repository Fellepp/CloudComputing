import os
from flask import Flask, request, send_file
from flask_cors import CORS, cross_origin

app = Flask(__name__)
cors = CORS(app, resources={r"/images": {"origins" : "http://localhost:3000"}})

@app.route('/')
def index():
    return 'Server Works!'


@app.route('/images', methods=['POST', 'GET'])
@cross_origin(origin='localhost', headers=['Content-Type', 'Authorization'])
def upload():
    if request.method =='POST':
        image_id = request.args.get('id')
        with open('images/' + image_id + '.png', 'wb') as file:
            file.write(request.data)
            file.close()
        process(image_id)
        return "Image recieved"

    if request.method == 'GET':
        image_id = request.args.get('id')
        isProcessed(image_id)
        return send_file('images/p_' + image_id + '.png', mimetype="image/gif")

@app.route('/cleanup', methods=['GET'])
@cross_origin(origin='localhost', headers=['Content-Type', 'Authorization'])
def cleanData():
    image_id = request.args.get('id')
    return clearData(image_id)

def process(image_id):
    cmd = 'wsl.exe mpirun -n 8 ./lowpass_mpi.out images/' + image_id + '.png images/p_' + image_id + '.png'
    os.system(cmd)

def isProcessed(image_id):
    while True:
        try:
            with open('images/p_' + image_id + '.png', 'r') as file:
                file.close()
            break
        except Exception as e:
            continue
    return True

def clearData(image_id):
    if "/" in image_id or '/' in image_id or '.' in image_id or len(image_id) != 8:
        return "Bad request"
    cmd = "wsl.exe rm images/*"
    os.system(cmd)
    return "Job cleared"
