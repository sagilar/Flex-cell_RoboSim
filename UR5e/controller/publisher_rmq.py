### Author: Santiago Gil
#!/usr/bin/env python3
import pika
import json
from datetime import datetime
import time

## Co-sim properties
timestep=0.5
max_time = 20.0

rabbitmq_host = "localhost"
rabbitmq_port = 5672
rabbitmq_username = "guest"
rabbitmq_password = "guest"

#### RabbitMQ ####
credentials = pika.PlainCredentials(rabbitmq_username, rabbitmq_password)
connection = pika.BlockingConnection(pika.ConnectionParameters(rabbitmq_host, rabbitmq_port, credentials=credentials))
channel = connection.channel()
print("Declaring exchange")
channel.exchange_declare(exchange='fmi_digital_twin', exchange_type='direct')

print("Creating queue")
result = channel.queue_declare(queue='', exclusive=True)
queue_name = result.method.queue

channel.queue_bind(exchange='fmi_digital_twin', queue=queue_name,
                   routing_key='data.from_cosim')

number = 1

def talker(number):
    consoleMsg = "About to publish %d" % number

def publish():
    dt=datetime.strptime('2019-01-04T16:41:24+0200', "%Y-%m-%dT%H:%M:%S%z")

    msg = {}
    msg['time']= dt.isoformat()


    for i in range(int(max_time/timestep)):
            msg['time']= datetime.now(tz = datetime.now().astimezone().tzinfo).isoformat(timespec='milliseconds')
            print("i:" + str(i))
            if (i==2):
                msg['moveDiscreteCommand'] = True
                msg['MovementArgs_target_X'] = 0
                msg['MovementArgs_target_Y'] = 23
                msg['MovementArgs_target_Z'] = 1

            elif (i==11):
                msg['moveDiscreteCommand'] = True
                msg['MovementArgs_target_X'] = 3
                msg['MovementArgs_target_Y'] = 20
                msg['MovementArgs_target_Z'] = 2

            elif (i==16):
                msg['moveDiscreteCommand'] = True
                msg['MovementArgs_target_X'] = 8
                msg['MovementArgs_target_Y'] = 10
                msg['MovementArgs_target_Z'] = 0

            elif (i==30):
                msg['moveDiscreteCommand'] = True
                msg['MovementArgs_target_X'] = 1
                msg['MovementArgs_target_Y'] = 13
                msg['MovementArgs_target_Z'] = 0
            else:
                msg['moveDiscreteCommand'] = False
                msg['MovementArgs_target_X'] = 0
                msg['MovementArgs_target_Y'] = 0
                msg['MovementArgs_target_Z'] = 0
                msg['closeGripperCommand'] = False
                msg['openGripperCommand'] = False


            channel.basic_publish(exchange='fmi_digital_twin',
                          routing_key='data.to_cosim',
                          body=json.dumps(msg))
            print(" [x] Sent %s" % json.dumps(msg))


            time.sleep(timestep)

def callback(ch, method, properties, body):
    print(" [x] %r" % body)
    if "waiting for input data for simulation" in str(body):
      publish()
    else:
        print("Received: %s", str(body))
        number = 1
        talker(number)

if __name__ == '__main__':
    try:
        channel.basic_consume(
                    queue=queue_name, on_message_callback=callback, auto_ack=True)

        channel.start_consuming()

        connection.close()
    except KeyboardInterrupt:
        pass
