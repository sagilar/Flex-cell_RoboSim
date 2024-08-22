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

#pub = rospy.Publisher('/Input', Int32, queue_size=10)
#rospy.init_node('talker', anonymous=True)
#rate = rospy.Rate(10) # 10hz
number = 1

def talker(number):
    consoleMsg = "About to publish %d" % number
    #rospy.loginfo(consoleMsg)
    #pub.publish(number)
    #rate.sleep()

def publish():
#    channel.stop_consuming()
    dt=datetime.strptime('2019-01-04T16:41:24+0200', "%Y-%m-%dT%H:%M:%S%z")

    msg = {}
    msg['time']= dt.isoformat()
    #msg['controller_event'] = "moveDiscreteCommand"
    #msg['controller_event_args_0'] = 4.0
    #msg['controller_event_args_1'] = 18.0
    #msg['controller_event_args_2'] = 4.0
    #msg['controller_event_args_3'] = 0.0


    for i in range(int(max_time/timestep)):
            msg['time']= datetime.now(tz = datetime.now().astimezone().tzinfo).isoformat(timespec='milliseconds')
            print("i:" + str(i))
            if (i==2):
                msg['controller_event'] = "moveDiscreteCommand"
                msg['controller_event_args_0'] = 0.0
                msg['controller_event_args_1'] = 23.0
                msg['controller_event_args_2'] = 1.0

            elif (i==11):
                msg['controller_event'] = "moveDiscreteCommand"
                msg['controller_event_args_0'] = 3.0
                msg['controller_event_args_1'] = 20.0
                msg['controller_event_args_2'] = 2.0

            elif (i==16):
                msg['controller_event'] = "moveDiscreteCommand"
                msg['controller_event_args_0'] = 8.0
                msg['controller_event_args_1'] = 10.0
                msg['controller_event_args_2'] = 0.0

            elif (i==30):
                msg['controller_event'] = "moveDiscreteCommand"
                msg['controller_event_args_0'] = 1.0
                msg['controller_event_args_1'] = 13.0
                msg['controller_event_args_2'] = 0.0
            else:
                msg['controller_event'] = ""
                msg['controller_event_args_0'] = 0.0
                msg['controller_event_args_1'] = 0.0
                msg['controller_event_args_2'] = 0.0
                msg['controller_event_args_3'] = 0.0
                msg['controller_event_args_4'] = 0.0
                msg['controller_event_args_5'] = 0.0
                msg['controller_event_args_6'] = 0.0
                msg['controller_event_args_7'] = 0.0
                msg['controller_event_args_8'] = 0.0
                msg['controller_event_args_9'] = 0.0

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
        #ur5e_robot.stop_recording()
        pass
