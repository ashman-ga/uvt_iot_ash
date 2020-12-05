import paho.mqtt.client as mqtt
import json
import time
from datetime import datetime

orgid='xxxx'
host=orgid+'.messaging.internetofthings.ibmcloud.com'
clientid='d:'+ orgid +':xxxx:xxxx'
username='use-token-auth'
password='xxxx'
topic='iot-2/cmd/xxxx/fmt/json'#iot-2/cmd/cmd_name/fmt/json

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    
def on_message(client, userdata, msg):
    button= json.loads(msg.payload)["state"]
    print(button);

client = mqtt.Client(clientid)
client.username_pw_set(username, password)
client.connect(host, 1883)
client.subscribe(topic)
client.on_connect = on_connect
client.on_message = on_message
client.loop_forever()