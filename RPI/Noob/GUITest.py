from Tkinter import *
from PIL import Image, ImageTk
import tkFont
#import RPi.GPIO as GPIO

datum = [0,0] #Zero co-ordinate of the board (bottom right)
datumRadius = 10
logoPadding = 20 #horizontal padding around controller logo

win = Tk() #Create a Tkinter window object for ARENA
win.title("Robot Simulator")
win.geometry('800x600')

myFont = tkFont.Font(family = 'Helvetica', size = 36, weight = 'bold')

w = Canvas(win) #canvas module to hold images, shapes
w.pack(expand=YES,fill=BOTH)

image = Image.open("board.jpg") #import board image
photo = ImageTk.PhotoImage(image.rotate(90)) #convert for ImageTK format 90deg

height, width = image.size #inverted order of height width as the image is rotated 90deg
print(width)
print(height)

board = w.create_image(width/2,height/2,image = photo);

def drawcircle(canv,x,y,rad):
    canv.create_oval(x-rad,y-rad,x+rad,y+rad,width=0,fill='blue')

#Mark datum
datumPoint = drawcircle(w,width,height,datumRadius)
#mark boundary walls
boundary = w.create_rectangle(0,0,width,height,outline='red',width=3)

def exitProgram():
    print("Exit")
    win.quit()

exitButton = Button(win, text = "Exit", font = myFont, command = exitProgram, height = 2, width = 8)
#exitButton.pack(side = BOTTOM)

#Controller Window
win2 = Toplevel() #Create a Tkinter window object for controller TOPLEVEL when you have more than one
win2.title("Controller")
win2.geometry('300x400')
w2 = Canvas(win2,bg="white")
w2.pack(expand=YES,fill=BOTH)

image = Image.open("logo.jpg") #import logo image
width,height = image.size
aspect = width/height
logophoto = ImageTk.PhotoImage(image = image.resize((300-logoPadding*2,(300-logoPadding*2)/aspect))) #convert for ImageTK format, resize proportionally
w2.create_image(150,50,image=logophoto)

mainloop()
