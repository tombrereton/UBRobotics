from Tkinter import *
import tkFont
#import RPi.GPIO as GPIO

win = Tk() #Create a Tkinter window object
win.title("Robot Simulator")
win.geometry('800x400')

myFont = tkFont.Font(family = 'Helvetica', size = 36, weight = 'bold')

def exitProgram():
    print("Exit")
    win.quit()

exitButton = Button(win, text = "Exit", font = myFont, command = exitProgram, height = 2, width = 8)
exitButton.pack(side = BOTTOM)

mainloop()
