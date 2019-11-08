# from flask import Flask, request
# from flask_restful import Resource, Api
# import subprocess
# import json

# app = Flask(__name__)
# api = Api(app)


# class HelloWorld(Resource):
#     def get(self):
#         # file_name: string = request.form['file_name']
#         file_name = "TODO"
#         # program: string = request.form['program']
#         program = "val x = 5;"
#         with open(f'{file_name}.sml', 'w') as file:
#             file.write(program)

#         cmd = ["/Users/jmp/hamlet-theia/hamlet",
#                "-p", f"/Users/jmp/theia/server/{file_name}.sml"]
#         result = subprocess.run(cmd, capture_output=True)
#         return json.loads(result.stdout)


# api.add_resource(HelloWorld, '/')

# if __name__ == '__main__':
#     app.run(debug=True)


# from flask import Flask
# from flask_restful import Resource, Api
# import subprocess
# import json

# app = Flask(__name__)
# api = Api(app)


# class HelloWorld(Resource):
#     def get(self, file_name):
#         cmd = ["/Users/jmp/hamlet-theia/hamlet",
#                "-p", f"/Users/jmp/theia/src/SML/examples/{file_name}.sml"]
#         result = subprocess.run(cmd, capture_output=True)
#         return json.loads(result.stdout)


# api.add_resource(HelloWorld, '/<string:file_name>')

# if __name__ == '__main__':
#     app.run(debug=True)


from flask import Flask, request
from flask_restful import Resource, Api
import subprocess
import json

app = Flask(__name__)
api = Api(app)


class HelloWorld(Resource):
    def get(self):
        file_name = request.form['file_name']
        cmd = ["/Users/jmp/hamlet-theia/hamlet",
               "-p", f"../SML/examples/{file_name}.sml"]
        result = subprocess.run(cmd, capture_output=True)
        return json.loads(result.stdout)


api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)
