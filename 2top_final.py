import nidaqmx
from nidaqmx.constants import AcquisitionType
import serial
import time

port = "com9"  
ser = serial.Serial(port, 9600, timeout=1)
time.sleep(1)
# 創建任務
with nidaqmx.Task() as task:
    # 添加模擬輸入通道（使用正確的設備和通道名稱）
    task.ai_channels.add_ai_voltage_chan("cDAQ1Mod1/ai0")

    # 設置樣本時鐘速率和連續采集模式
    task.timing.cfg_samp_clk_timing(rate=1000, sample_mode=AcquisitionType.CONTINUOUS, samps_per_chan=1000)

    # 開始任務
    task.start()

    # 讀取數據
    print("Reading voltage values... Press Ctrl+C to stop.")
    try:
        robot_status = 1
        while True:
            if robot_status == 1:
                data = task.read(number_of_samples_per_channel=1)
                # 提取列表中的單個數值並進行格式化
                voltage = data[0]
                print(f"Voltage: {voltage:.2f} V")
                # 停止任務條件
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