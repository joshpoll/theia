from flask import Flask, request
from flask_restful import Resource, Api
import subprocess
import json

app = Flask(__name__)
api = Api(app)


class HelloWorld(Resource):
    def get(self):
        file_name = request.form['file_name']
        cmd = ["./hamlet/hamlet",
               "-p", f"../SML/examples/{file_name}.sml"]
        result = subprocess.run(cmd, capture_output=True)
        return json.loads(result.stdout)


api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)
