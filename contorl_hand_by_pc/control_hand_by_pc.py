import nidaqmx
from nidaqmx.constants import AcquisitionType
import serial
import time

port = "com9"  
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
                data = task.read(number_of_samples_per_channel=1)
                # Extract a single value from the list and format it
                voltage = data[0]
                print(f"Voltage: {voltage:.2f} V")
                # Stop the task and send a signal to Arduino if voltage exceeds 2.1
                if voltage > 2.1:
                    print("Voltage exceeded 2.1, stopping task, sending signal to Arduino.")
                    ser.write("ON".encode('utf-8'))
                    task.stop()
                    robot_status = 0
                else:
                    pass
            else:
                robot_status = int(input("Type Robot Status (0/1): "))
    except KeyboardInterrupt:
        pass
    finally:
        ser.close()
