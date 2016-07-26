from Tkinter import *
from PIL import Image, ImageTk
import tkFont
import ConfigParser #to save settings
import os.path #check file exists
import time
from eurobot import *

Config = ConfigParser.ConfigParser()
filepath = "config.ini"
#import RPi.GPIO as GPIO

#Init config file
if not os.path.exists(filepath):
    print("Config file does not exist, making new one")
    cfgfile = open(filepath,'w')
    Config.add_section('Controller')
else:
    print("Reading config file")
    Config.read(filepath)

datum = [0,0] #Zero co-ordinate of the board (bottom right)
boundsize = [0,0] #Size of boundary
datumRadius = 10
logoPadding = 20 #horizontal padding around controller logo

win = Tk() #Create a Tkinter window object for ARENA
win.title("Robot Simulator")
win.geometry('800x600')

myFont = tkFont.Font(family = 'Helvetica', size = 12, weight = 'bold')
w = Canvas(win) #canvas module to hold images, shapes
w.pack(expand=YES,fill=BOTH)

image = Image.open("board.jpg") #import board image
photo = ImageTk.PhotoImage(image.rotate(90)) #convert for ImageTK format 90deg
height, width = image.size #inverted order of height width as the image is rotated 90deg
board = w.create_image(width/2,height/2,image = photo);
print(width)
print(height)

datum = [width,height]
boundsize = [width,height]

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
win2.title("Global Settings")
win2.geometry('300x400')
w2 = Canvas(win2,bg="white")
w2.pack(expand=YES,fill=BOTH)

#image = Image.open("logo.jpg") #import logo image
#width,height = image.size
#aspect = width/height
#logophoto = ImageTk.PhotoImage(image = image.resize((300-logoPadding*2,(300-logoPadding*2)/aspect))) #convert for ImageTK format, resize proportionally
#w2.create_image(150,50,image=logophoto)

#load .ini data
if os.path.exists(filepath):
    print("Loading")
    datum = eval(Config.get('Controller','datum'),{},{})
    arenadimension = eval(Config.get('Controller','boundsize'),{},{}) #Parse to a new array
    width = arenadimension[0]
    height = arenadimension[1]

#Datum
t1 = Label(w2,text="Datum X: ").grid(row=0,column=0)
e1 = Entry(w2) #DatumX
e1.insert(0,datum[0])
e1.grid(row=0,column=1)
t2 = Label(w2,text="Datum Y: ").grid(row=1,column=0)
e2 = Entry(w2) #DatumY
e2.insert(0,datum[1])
e2.grid(row=1,column=1)
#Arena size
t3 = Label(w2,text="Arena length: ").grid(row=3,column=0)
e3 = Entry(w2) #DatumX
e3.insert(0,width)
e3.grid(row=3,column=1)
t4 = Label(w2,text="Arena width: ").grid(row=4,column=0)
e4 = Entry(w2) #DatumY
e4.insert(0,height)
e4.grid(row=4,column=1)

def saveSettings(thedatum,thebound):
    cfgfile = open(filepath,'w')
    Config.set('Controller','datum',thedatum)
    Config.set('Controller','boundsize',thebound)
    Config.write(cfgfile)
    cfgfile.close()
    
def setArena():
    datum = [int(e1.get()),int(e2.get())]
    boundsize = [int(e3.get()),int(e4.get())]
    print("Settings updated.")
    print datum
    print boundsize
    #now redraw datum and boundary
    w.delete("all") #delete all images from previous setting
    height, width = image.size
    board = w.create_image(width/2,height/2,image = photo)
    datumPoint = drawcircle(w,datum[0],datum[1],datumRadius)
    boundary = w.create_rectangle(datum[0]-boundsize[0],datum[1]-boundsize[1],datum[0],datum[1],outline='red',width=3)
    saveSettings(datum,boundsize)
    
setter = Button(w2, text="Set new datum and arena size", command=setArena)
setter.grid(row=5,column=0)
setArena() #load config

#Tests
#test = Eurobot(60,50,[400,400],-90,w)
#dada = w.create_image(test.position[0],test.position[1], image = test.photo)
#test.rotate(45)
#test.translate(100)
#dada = w.create_image(test.position[0],test.position[1], image = test.photo)

win3 = Toplevel() #Create a Tkinter window object for controller TOPLEVEL when you have more than one
win3.title("Primary Robot Controller")
win3.geometry('300x400')
w3 = Canvas(win3,bg="white")
w3.pack(expand=YES,fill=BOTH)
#Starting vector
t5 = Label(w3,text="Starting X: ").grid(row=0,column=0)
e5 = Entry(w3) 
e5.insert(0,0)
e5.grid(row=0,column=1)
t6 = Label(w3,text="Starting Y: ").grid(row=1,column=0)
e6 = Entry(w3)
e6.insert(0,0)
e6.grid(row=1,column=1)
t7 = Label(w3,text="Starting Heading (degrees): ").grid(row=2,column=0)
e7 = Entry(w3)
e7.insert(0,0)
e7.grid(row=2,column=1)
t8 = Label(w3,text="Track: ").grid(row=3,column=0)
e8 = Entry(w3)
e8.insert(0,0)
e8.grid(row=3,column=1)
t9 = Label(w3,text="Wheel diameter: ").grid(row=4,column=0)
e9 = Entry(w3)
e9.insert(0,0)
e9.grid(row=4,column=1)

def setPrimary():
    primaryRobot = Eurobot(int(e8.get()),int(e9.get()),[int(e5.get()),int(e6.get())],int(e7.get()),w)
    primaryRobot.translate(100)
    
activate1 = Button(w3, text="Build primary robot", command=lambda: setPrimary())
activate1.grid(row=5,column=0)

mainloop()
