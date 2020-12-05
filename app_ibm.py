#import wiotp.sdk.application as app
import ibmiotf.application as app
import time
import json

options = {
"org": "xxxx",
"id": "xxxx",
"auth-method": "apikey",
"auth-key": "xxxx", # Replace this with your auth key
"auth-token": "xxxx", # Replace this with your auth token
"clean-session": True
}

sourceDeviceType="xxxx"
sourceDeviceId="xxxx"
sourceEvent="xxxx"

targetDeviceType="xxxx"
targetDeviceId="xxxx"

def ButtonCallback(event):
	print("Got event " + json.dumps(event.data))
	xxxx= event.data['xxxx']
	commandData={'xxxx' : xxxx }
	client.publishCommand(targetDeviceType, targetDeviceId, "xxxx", "json", commandData)


#client = app.ApplicationClient(options)
client =app.Client(options)
client.connect()
client.deviceEventCallback = ButtonCallback
client.subscribeToDeviceEvents(deviceType=sourceDeviceType,deviceId=sourceDeviceId,event=sourceEvent)

while True:
	time.sleep(1)