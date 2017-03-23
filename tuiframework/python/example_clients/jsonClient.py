import json

input("Press ENTER when the Python Interface is ready")

while True:
    try:
        with open("../TUIdict.json") as json_file:
            jsonDict = json.load(json_file) 
        print(jsonDict)
    except:
        print("JSON file occupied")