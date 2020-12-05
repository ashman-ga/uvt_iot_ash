#in the last lecture we used wtiop 
import paho.mqtt.client as mqtt
import json#an object format used to transfer data on a network
import time
from datetime import datetime

orgid='xxxx'#your organization id
host=orgid+'.messaging.internetofthings.ibmcloud.com'#host
clientid='d:'+ orgid +':xxxx:xxxx'#d:orgid:device_type:device_id
username='use-token-auth'
password='xxxx'#device authentication token
topic='iot-2/evt/xxxx/fmt/json'#iot-2/evt/event_name/fmt/json

client = mqtt.Client(clientid)
client.username_pw_set(username, password)
client.connect(host, 1883)#we conncet to the server without using TSL 

if client.is_connected:
    print("connected!!!")
    
bulb_cmd={"xxxx":"xxxx"}
client.publish(topic,json.dumps(bulb_cmd))

client.disconnect()
