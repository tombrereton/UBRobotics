from Tkinter import *
from PIL import Image, ImageTk
import tkFont
#import RPi.GPIO as GPIO

win = Tk() #Create a Tkinter window object
win.title("Robot Simulator")
win.geometry('800x400')

myFont = tkFont.Font(family = 'Helvetica', size = 36, weight = 'bold')

image = Image.open("board.jpg") #import board image
photo = ImageTk.PhotoImage(image.rotate(90)) #convert for ImageTK format 90deg

board = Label(image=photo)
board.image = photo
board.pack()
board.place(x=0,y=0) #must come after pack()

def exitProgram():
    print("Exit")
    win.quit()

exitButton = Button(win, text = "Exit", font = myFont, command = exitProgram, height = 2, width = 8)
#exitButton.pack(side = BOTTOM)



mainloop()
