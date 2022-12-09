import os
import PySimpleGUI as sg
import visualize
import subprocess
from time import sleep
import threading


def saveToFile(settings, inputPath, outputPath, vAmount, vMax):
    # transform paths from absolute to relative paths
    inputPath = os.path.relpath(inputPath)
    outputPath = os.path.relpath(outputPath)

    with open(settings, "w") as settingsFile:
        settingsFile.write(inputPath + "\n")
        settingsFile.write(str(vAmount) + "\n")
        settingsFile.write(str(vMax) + "\n")
        settingsFile.write(outputPath + "\n")


def RunSimulation(inputFile, outputFile):
    runTSP = '.\\x64\\Release\\tsp.exe ' + '\"' + inputFile + \
        '\"' + ' 2 ' + '> ' + '\"' + outputFile + '\"'
    # print(runTSP)
    print("Running simulation...")
    #t1 = threading.Thread(target=subprocess.call, args=(runTSP,))
    # t1.start()
    subprocess.call(runTSP, shell=True)
    print("Done")
    sleep(1)


def createLayout(precisionOptions, inputPath, outputPath):
    settings = [[sg.Text("Choose a input data file: "), sg.Input(expand_x=True,
                                                                 key="-inputFile-", default_text=inputPath), sg.FileBrowse()],
                [sg.Text("Choose an output data file: "), sg.Input(expand_x=True,
                                                                   key="-outputFile-", default_text=outputPath), sg.FileBrowse()],
                [sg.Text("Choose precision:"), sg.Combo(
                    precisionOptions, default_value=2, key="-precision-", size=(10, None)), sg.Text(" (higher = slower but better result, lower = faster but worse result)")]]
    settingsFrame = [[sg.Frame("Settings", settings, expand_x=True)]]

    controls = [[sg.Button("Save"), sg.Button("Cancel")], [sg.HSeparator(pad=(10, 10))], [sg.Button(
        "Run"), sg.Button("Save & Run"), sg.Button("Only Visualize")], [sg.HSeparator(pad=(10, 10))], [sg.Button("Exit")]]
    controlsFrame = [
        [sg.Frame("Controls", controls, expand_x=False, expand_y=True)]]

    results = [[sg.Output(size=(50, 10), expand_x=True,
                          expand_y=True, key="-output-")]]
    resultsFrame = [
        [sg.Frame("Results", results, expand_x=True, expand_y=True)]]
    layout = [[sg.Column(settingsFrame, expand_x=True, expand_y=False, element_justification='c')], [sg.Column(controlsFrame, expand_x=True,
                                                                                                               expand_y=True, element_justification='l'), sg.Column(resultsFrame, expand_x=True, expand_y=True, element_justification='r')]]
    return layout


def RunGUI(settingsPath, ThemeName, windowSize=(850, 330), precisionOptions=[1, 2, 3]):

    # open file settings.in
    settingsFile = open(settingsPath, "r")
    inputPath = settingsFile.readline().strip()
    vAmount = int(settingsFile.readline())
    vMax = int(settingsFile.readline())
    outputPath = settingsFile.readline().strip()
    settingsFile.close()

    # inputPath from relative to absolute path
    inputPath = os.path.abspath(inputPath)
    outputPath = os.path.abspath(outputPath)

    sg.theme(ThemeName)
    layout = createLayout(precisionOptions, inputPath, outputPath)

    # Building Window
    window = sg.Window('TSPGUI', layout, size=windowSize, auto_size_text=True,
                       auto_size_buttons=True, resizable=True, grab_anywhere=False, border_depth=5,
                       default_element_size=(15, 1), finalize=True)

    while True:
        event, values = window.read()
        if event == sg.WIN_CLOSED or event == "Exit":
            break

        # When button Save is pressed, save settings to file
        elif event == "Save":
            saveToFile("settings.in", values["-inputFile-"],
                       values["-outputFile-"], vAmount, vMax)
            inputPath = values["-inputFile-"]
            outputPath = values["-outputFile-"]

        # When button Cancel is pressed, reset input and output paths to the ones from file
        elif event == "Cancel":
            window["-inputFile-"].update(inputPath)
            window["-outputFile-"].update(outputPath)

        elif event == "Only Visualize":
            visualize.visualizeResults(
                values["-inputFile-"], values["-outputFile-"])

        elif event == "Save & Run":

            saveToFile("settings.in", values["-inputFile-"],
                       values["-outputFile-"], vAmount, vMax)
            inputPath = values["-inputFile-"]
            outputPath = values["-outputFile-"]

            RunSimulation(inputPath, outputPath)
            visualize.visualizeResults(inputPath, outputPath)

        elif event == "Run":
            RunSimulation(values["-inputFile-"], values["-outputFile-"])
            # visualize.visualizeResults(
            #    values["-inputFile-"], values["-outputFile-"])


if __name__ == '__main__':
    # Settings file path
    settingsPath = "settings.in"
    defaultTheme = "DarkAmber"
    # available Themes: https://media.geeksforgeeks.org/wp-content/uploads/20200511200254/f19.jpg
    RunGUI(settingsPath, defaultTheme)
