from flask import Flask, request
from flask_restful import Resource, Api
import subprocess
import json
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
api = Api(app)


class HelloWorld(Resource):
    def post(self):
        file_name = request.form['file_name']
        program = request.form['program']
        with open(f"../../sml-files/{file_name}.sml", 'w') as f:
            f.write(program)
        cmd = ["./hamlet/hamlet",
               "-p", f"../../sml-files/{file_name}.sml"]
        result = subprocess.run(cmd, capture_output=True)
        return json.loads(result.stdout)


api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)
