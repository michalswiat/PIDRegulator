import serial
import re

import plotly
import plotly.graph_objs as go
from plotly.graph_objs import Layout

port = serial.Serial(
    port = '/dev/ttyACM0',
    baudrate = 9600,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS
)

port.isOpen()

out = ''
rpm = []
pwm = []
time = []
counter = 0
while counter < 100:
    sign = ''
    while port.inWaiting() > 0 and sign != '\n':
        sign = port.read(1)
        out += sign

    if sign == '\n':
        sign = ''
        print out
        value = int(re.search(r'\d+', out).group())
        if "RPM" in out:
            rpm.append(value)
        elif "PWM" in out:
            pwm.append(value)
            counter += 1
            time.append(counter)
        out = ''

trace0 = go.Scatter(x = time, y = rpm,
                    mode = 'lines', name = 'rpm')
trace1 = go.Scatter(x = time, y = pwm,
                    mode = 'lines', name = 'pwm')

plotly.offline.plot({
    "data": [trace0, trace1],
    "layout": Layout(title = "RPM chart")
})
