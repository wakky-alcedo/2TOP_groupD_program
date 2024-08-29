import nidaqmx
from nidaqmx.constants import AcquisitionType
import serial
import time

target_value:float = 2.1 # (constant)
time_coefficient:float = 150.0 # (t.c.) (constant)
proportional_gain:float = 150.0 # (p.g.) (constant)
sensore_value:float = 0.0

pomp_speed:int = 0
is_valve_open:bool = False
start_time = time.perf_counter()
time_valve_open = 0.0

is_feedback:bool = False

port = "com4"  
ser = serial.Serial(port, 9600, timeout=1)
time.sleep(1)
# Create a task
with nidaqmx.Task() as task:
    # Add an analog input channel (replace with the correct device and channel name)
    task.ai_channels.add_ai_voltage_chan("cDAQ1Mod1/ai0")

    # Set the sample clock rate and configure for continuous acquisition mode
    task.timing.cfg_samp_clk_timing(rate=1000, sample_mode=AcquisitionType.CONTINUOUS, samps_per_chan=1000)

    # Start the task
    task.start()

    # Read data
    print("Reading voltage values... Press Ctrl+C to stop.")
    try:
        robot_status = 1
        while True:
            if robot_status == 1:
                
                # 計測 get voltage
                data = task.read(number_of_samples_per_channel=1)
                # Extract a single value from the list and format it
                voltage = data[0]
                print(f"Voltage: {voltage:.2f} V")
                diff = target_value - voltage
                
                # 演算 control
                if(diff > 0):
                    pomp_speed = int(abs(diff) * proportional_gain)
                    if pomp_speed > 255:
                        pomp_speed = 255
                    elif pomp_speed < 127:
                        pomp_speed = 0
                    is_valve_open = False
                else:
                    pomp_speed = 0
                    if is_valve_open == True:
                        if(start_time + time_valve_open < time.perf_counter()):
                            is_valve_open = False
                    else:
                        # わんち閉じてから何秒間は開けないとかしたほうがいいかも
                        time_valve_open = abs(diff) * time_coefficient
                        start_time = time.perf_counter()
                        is_valve_open = True

                # 送信 send signal to Arduino
                send_data = pomp_speed | int(is_valve_open)<<8
                print(bin(send_data))
                ser.write(chr(send_data).encode('utf-8'))

                # 受信 get feedback from Arduino
                print(ser.readline().decode('utf-8'))
            else:
                robot_status = int(input("Type Robot Status (0/1): "))
    except KeyboardInterrupt:
        pass
    finally:
        ser.close()
