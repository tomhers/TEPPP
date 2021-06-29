import PySimpleGUI as sg
import os
import subprocess
import sys

file_list_column = [
    [
        sg.Text("Data Folder"),
        sg.In(size=(25, 1), enable_events=True, key="-FOLDER-"),
        sg.FolderBrowse(),
    ],
    [
        sg.Text("Select data file type:"),
        sg.Radio('.read_data', "FILETYPE", default=True, key="-FILETYPE1-"),
        sg.Radio('.dump (unsorted)', "FILETYPE", default=False, key="-FILETYPE2-"),
        sg.Radio('.dump (sorted)', "FILETYPE", default=False, key="-FILETYPE3-")
    ],
    [
        sg.Listbox(
            values=[], enable_events=True, size=(40, 20), key="-FILE LIST-"
        )
    ],
    [
        sg.Text("Are the chains open or closed?"),
        sg.Radio('open', "CHAINTYPE", default=True, key="-CHAINTYPE1-"),
        sg.Radio('closed', "CHAINTYPE", default=False, key="-CHAINTYPE2-")
    ],
    [
        sg.Text("Enter chain length:"),
        sg.In(size=(4, 1), enable_events=True, key="-CHAINLENGTH-")
    ],
    [
        sg.Text("Enter number of chains:"),
        sg.In(size=(4, 1), enable_events=True, key="-NUMCHAINS-")
    ],
    [sg.Text("Select the desired operation(s):")],
    [sg.Checkbox(
        'Calculate the Jones Polynomial of each chain', default=False, key="-JONES-"
    )],
    [sg.Checkbox(
        'Calculate the average length and position of the knot in each chain', default=False, key="-KNOT-"
    )],
    [sg.Checkbox(
        'Calculate the linking number of each chain', default=False, key="-LINKING-"
    )],
    [sg.Checkbox(
        'Calculate the writhe of each chain', default=False, key="-WRITHE-"
    )],
    [sg.Checkbox(
        'Calculate the periodic writhe of each chain', default=False, key="-PWRITHE-"
    )],
    [sg.Checkbox(
        'Calculate the periodic linking number of each chain', default=False, key="-PLINKING-"
    )],
    [sg.Button('Submit', key="-SUBMIT-")],
]

# For now will only show the name of the file that was chosen
image_viewer_column = [
    [sg.Output(size=(80, 20))],
]

# ----- Full layout -----
layout = [
    [
        sg.Column(file_list_column),
        sg.VSeperator(),
        sg.Column(image_viewer_column),
    ]
]

window = sg.Window("Topology User Package", layout)
while True:
    event, values = window.read()
    if event == "Exit" or event == sg.WIN_CLOSED:
        break

    # Folder name was filled in, make a list of files in the folder
    if event == "-FOLDER-":
        folder = values["-FOLDER-"]
        try:
            # Get list of files in folder
            file_list = os.listdir(folder)
        except:
            file_list = []

        fnames = [
            f
            for f in file_list
            if os.path.isfile(os.path.join(folder, f))
            and f.lower().endswith((".read_data", ".txt"))
        ]
        window["-FILE LIST-"].update(fnames)

    elif event == "-FILE LIST-":  # A file was chosen from the listbox
        try:
            filename = os.path.join(
                values["-FOLDER-"], values["-FILE LIST-"][0]
            )
        except:
            pass
    elif event == "-SUBMIT-":
        try:
            filename = os.path.join(
                values["-FOLDER-"], values["-FILE LIST-"][0]
            )
            filetype = 0

            if values["-FILETYPE1-"] == True:
                filetype = 1

            elif values["-FILETYPE2-"] == True:
                print("starting sort")
                f1 = open(filename, 'r')
                if (f1.closed):
                    print("did not open file")
                new = []
                for i, line in enumerate(f1):
                    print(i)
                    if i < 9:
                        continue
                    else:
                        s = line.split()
                        s[0] = int(s[0])
                        new.append(s)
                        print(s)
                new.sort()
                tmp = filename.split('.txt')
                newfname = tmp[0] + "sorted.txt"
                f2 = open(newfname, 'w')
                for x in new:
                    for y in x:
                        f2.write(str(y) + " ")
                    f2.write('\n')
                f1.close()
                f2.close()
                filename = newfname
                print("done sorting")
                filetype = 2

            else:
                filetype = 3

            if values["-JONES-"] == True:
                proc = subprocess.Popen(["./../main/jones", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"]), str(0)])
                proc.wait()
                f1 = open('jonesout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
            if values["-KNOT-"] == True:
                proc = subprocess.Popen(["./../main/jones", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"]), str(1)])
                proc.wait()
                f1 = open('knotout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
            if values["-LINKING-"] == True:
                proc = subprocess.Popen(["./../main/lk", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"])])
                proc.wait()
                f1 = open('lkout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
            if values["-WRITHE-"] == True:
                proc = subprocess.Popen(["./../main/wr", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"])])
                proc.wait()
                f1 = open('wrout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
            if values["-PWRITHE-"] == True:
                proc = subprocess.Popen(["./../main/periodic_wr", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"])])
                proc.wait()
                f1 = open('periodic_wrout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
            if values["-PLINKING-"] == True:
                proc = subprocess.Popen(["./../main/periodic_lk", filename, str(values["-CHAINLENGTH-"]),  str(values["-NUMCHAINS-"])])
                proc.wait()
                f1 = open('periodic_lkout.txt', 'r')
                lines = f1.readlines()
                for line in lines:
                    print(line)
                f1.close()
                print("Done!")
        except:
            pass

window.close()