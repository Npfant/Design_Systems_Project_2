import PySimpleGUI as sg
import serial

x = 0
y = 0
s = ""
try:
    ser = serial.Serial('COM4', 115200)
except:
    ser = serial.Serial('COM5', 115200)
    print("On COM 5")

home = [[sg.Button("Start Display", button_color="green"), sg.Button("End Session", button_color="red")]]
dataDisplay = [
    [sg.Button("End Display", button_color="red")],
    [sg.Text("GPS", justification="center", font=('Arial Bold', 20))],
    [sg.Text("X Acceleration: ", justification="left"), sg.Text(x, key='accelX')],
    [sg.Text("Y Acceleration: ", justification="left"), sg.Text(y, key='accelY')]]
layout = [[sg.Column(home, key='-COL1-'), sg.Column(dataDisplay, visible=False, key='-COL2-')]]
window = sg.Window("Serial Display GUI", layout, margins=(200,100))
layout = 1
while True:
    event, values = window.read(timeout=500)
    #print(event, values)
    if event in (None, 'End Session'):
        break
    if event == 'Start Display':
        window[f'-COL{layout}-'].update(visible=False)
        layout = 2
        window[f'-COL{layout}-'].update(visible=True)
    if event == 'End Display':
        window[f'-COL{layout}-'].update(visible=False)
        layout = 1
        window[f'-COL{layout}-'].update(visible=True)
    if event == sg.TIMEOUT_EVENT:
        x = ser.readline()
        for b in x:
            print(b)
            if b == 10:
                break
            if b == 13:
                break
            else:
                s = s + str(chr(b))
        x = s
        print(x)
        window['accelX'].update(x)
        s = ""
        x = ser.readline()
        for b in x:
            if b == 10:
                break
            else:
                s = s + str(chr(b))
        x = s
        print(x)
        window['accelY'].update(y)
window.close()