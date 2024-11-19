import PySimpleGUI as sg
import serial

x = 0
count = 1
s = ""
try:
    ser = serial.Serial('COM4', 115200)
except:
    ser = serial.Serial('COM5', 9600)
    print("Bluetooth")

home = [[sg.Button("Start Display", button_color="green"), sg.Button("End Session", button_color="red")]]
dataDisplay = [
    [sg.Button("End Display", button_color="red")],
    [sg.Text("Location Data", justification="center", font=('Arial Bold', 20))],
    [sg.Text("X Acceleration (m/s²): ", justification="left"), sg.Text(x, key='accelX'), sg.Text("Y Acceleration (m/s²): ", justification="center"), sg.Text(x, key='accelY'), sg.Text("Z Acceleration (m/s²): ", justification="right"), sg.Text(x, key='accelZ')],
    #[sg.Text("Y Acceleration: ", justification="left"), sg.Text(x, key='accelY')],
    #[sg.Text("Z Acceleration: ", justification="left"), sg.Text(x, key='accelZ')],
    [sg.Text("X Angular Velocity (rad/s): ", justification="left"), sg.Text(x, key='gyroX'), sg.Text("Y Angular Velocity (rad/s): ", justification="left"), sg.Text(x, key='gyroY'), sg.Text("Z Angular Force (rad/s): ", justification="left"), sg.Text(x, key='gyroZ')],
    #[sg.Text("Y Rotation: ", justification="left"), sg.Text(x, key='gyroY')],
    #[sg.Text("Z Rotation: ", justification="left"), sg.Text(x, key='gyroZ')],
    [sg.Text("X Magnetic Field (µT): ", justification="left"), sg.Text(x, key='magX'), sg.Text("Y Magnetic Field (µT): ", justification="left"), sg.Text(x, key='magY'), sg.Text("Z Magnetic Field (µT): ", justification="left"), sg.Text(x, key='magZ')],
    #[sg.Text("Y Magnetic Field: ", justification="left"), sg.Text(x, key='magY')],
    #[sg.Text("Z Magnetic Field: ", justification="left"), sg.Text(x, key='magZ')],
    [sg.Text("Latitude: ", justification="left"), sg.Text(x, key='lat'), sg.Text("Longitude: ", justification="left"), sg.Text(x, key='lng')]]
    #[sg.Text("Longitude: ", justification="left"), sg.Text(x, key='lng')]]
layout = [[sg.Column(home, key='-COL1-'), sg.Column(dataDisplay, visible=False, key='-COL2-')]]
window = sg.Window("Serial Display GUI", layout, margins=(200,100))
layout = 1
while True:
    event, values = window.read(timeout=1)
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
            #print(b)
            if b == 10:
                break
            if b == 83:
                count = 0
            else:
                s = s + str(chr(b))
        x = s
        #print(x)
        if count == 1:
            window['accelX'].update(x)
        elif count == 2:
            window['accelY'].update(x)
        elif count == 3:
            window['accelZ'].update(x)
        elif count == 4:
            window['gyroX'].update(x)
        elif count == 5:
            window['gyroY'].update(x)
        elif count == 6:
            window['gyroZ'].update(x)
        elif count == 7:
            window['magX'].update(x)
        elif count == 8:
            window['magY'].update(x)
        elif count == 9:
            window['magZ'].update(x)
        elif count == 10:
            window['lat'].update(x)
        elif count == 11:
            window['lng'].update(x)

        s = ""
        count += 1

window.close()