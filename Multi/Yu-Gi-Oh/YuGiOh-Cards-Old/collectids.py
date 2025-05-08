import json

with open("cardinfo.json") as file:
    text = file.read()
data = json.loads(text)["data"]
ids = [datum["id"] for datum in data]
ids.sort()
with open("ids.txt", "w+") as file:
    for id in ids:
        file.write(f"{id}\n")
