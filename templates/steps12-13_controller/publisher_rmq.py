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
            # Update the logic based on the steps
            print("i:" + str(i))
            msg['someCommand'] = False
            msg['someArgument_1'] = 5
            msg['someArgument_2'] = "argument"
            msg['someArgument_3'] = 5.5

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
