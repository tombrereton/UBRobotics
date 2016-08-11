#Python 2.7 compatible, do not use Python 3. Make sure host computer has tkinter and PIL libraries. On debian-based OSes use 'apt-get' to acquire libraries from the internet

from Tkinter import *
from PIL import Image, ImageTk
import tkFont
import ConfigParser #to save settings
import os.path #check file exists
import time
import numpy
from eurobot import *
global primaryRobot, datum, boundsize, firstPoint, measureLine, isRecording, angleLine, secondPoint #make global so all functions can access it

isRecording = False #Path recording is initially off

Config = ConfigParser.ConfigParser() #init object for storing .ini config files
filepath = "config.ini"
#import RPi.GPIO as GPIO

datum = [0,0] #Zero co-ordinate of the board (bottom right)
boundsize = [0,0] #Size of boundary
datumRadius = 10 #radius of datum marker (circle)
logoPadding = 20 #horizontal padding around controller logo
pixeltoCM = [0,0] #Used to calibrate pixels to actual distance in cm
firstPoint = [0,0] #Co-ordinate of first point of measuring line
secondPoint = [0,0]

win = Tk() #Create a Tkinter window object for ARENA
win.title("Robot Simulator")
win.geometry('800x600')

myFont = tkFont.Font(family = 'Helvetica', size = 12, weight = 'bold')
w = Canvas(win) #canvas module to hold images, shapes

#hbar=Scrollbar(win,orient=HORIZONTAL)
#hbar.pack(side=BOTTOM,fill=X)
#hbar.config(command=w.xview)
#vbar=Scrollbar(win,orient=VERTICAL)
#vbar.pack(side=RIGHT,fill=Y)
#vbar.config(command=w.yview)

#w.config(xscrollcommand=hbar.set,yscrollcommand=vbar.set)

w.pack(expand=YES,fill=BOTH)
measureLine = w.create_line(0,0,0,0)
angleLine = w.create_line(0,0,0,0)

image = Image.open("board.jpg") #import board image
photo = ImageTk.PhotoImage(image.rotate(90)) #convert for ImageTK format 90deg
height, width = image.size #inverted order of height width as the image is rotated 90deg
board = w.create_image(width/2,height/2,image = photo); #add image object to main canvas 'w'
win.geometry(str(width)+"x"+str(height))
#print(width)
#print(height)

datum = [width,height] #store datum and arena boundary sizes to variable
boundsize = [width,height]

def drawcircle(canv,x,y,rad): #use this to draw circles giving the CANVAS, X & Y of the centre and the radius
    global targetPoint
    targetPoint = canv.create_oval(x-rad,y-rad,x+rad,y+rad,width=0,fill='blue')
    
def drawcirclered(canv,x,y,rad): #use this to draw circles giving the CANVAS, X & Y of the centre and the radius
    global targetPoint2
    targetPoint2 = canv.create_oval(x-rad,y-rad,x+rad,y+rad,width=0,fill='red')

def drawcirclegreen(canv,x,y,rad): #use this to draw circles giving the CANVAS, X & Y of the centre and the radius
    global targetPoint3
    targetPoint3 = canv.create_oval(x-rad,y-rad,x+rad,y+rad,width=0,fill='green')


drawcirclered(w,0,0,0)
drawcirclegreen(w,0,0,0)

#Mark datum
datumPoint = drawcircle(w,width,height,datumRadius)
#mark boundary walls
boundary = w.create_rectangle(0,0,width,height,outline='red',width=3)

#Controller Window
win2 = Toplevel() #Create a Tkinter window object for controller TOPLEVEL when you have more than one
win2.title("Global Settings")
win2.geometry('500x400')
w2 = Canvas(win2,bg="white")
w2.pack(expand=YES,fill=BOTH) #let it fill the entire window

#Datum text label and input fields, load the input fields with .ini data if exists
t1 = Label(w2,text="Datum X: ").grid(row=0,column=0)
e1 = Entry(w2) #DatumX
e1.insert(0,datum[0]) #set input field
e1.grid(row=0,column=1) #grid allows for easy positioning of canvas elements
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
instructions = Label(w2,bg="white",text="LMB to place position marker, RMB to place distance marker.").grid(row=6,column=0,columnspan=2)
instructions = Label(w2,bg="white",text="Place a third point with MMB after placing the two markers to measure an angle.").grid(row=7,column=0,columnspan=2)

def saveSettings(thedatum,thebound): #autosave to .ini
    return
    
def setArena():
    global datum, boundsize, pixeltoCM
    datum = [eval(e1.get()),eval(e2.get())] #get datum and boundary size from text input fields above
    boundsize = [eval(e3.get()),eval(e4.get())]
    pixeltoCM[0] = float(e3.get()) / 300 #Horizontal length is 300 cm
    pixeltoCM[1] = float(e4.get()) / 200 #Vertical length is 200 cm
    print("Settings updated.")
    #print pixeltoCM
    #print datum
    #print boundsize
    #now redraw datum and boundary
    w.delete("all") #delete all images from previous setting
    height, width = image.size
    board = w.create_image(width/2,height/2,image = photo) #draw board picture
    datumPoint = drawcircle(w,datum[0],datum[1],datumRadius) #draw datum point as circle
    boundary = w.create_rectangle(datum[0]-boundsize[0],datum[1]-boundsize[1],datum[0],datum[1],outline='red',width=1) #draw arena boundaries
    saveSettings(datum,boundsize) #function above
    
setter = Button(w2, text="Set new datum and arena size", command=setArena) #button to set new arena sizes
setter.grid(row=5,column=0)

def setRecord(): #Begin/Finish path recording
    global isRecording
    
    if isRecording == False:
        tkMessageBox.showinfo('Recording begin','Path recording activated, left click on arena to set path co-ordinates')
    else:
        isSave = tkMessageBox.askokcancel('Recording stop','Save path?')

    isRecording = not isRecording 

setRecord = Button(w2, text="Toggle Path Recording", command=setRecord) #button to draw robot path by clicking co-ordinates
setRecord.grid(row=5,column=1)
setArena() #auto-load config when program boots

#Tests
#test = Eurobot(60,50,[400,400],-90,w)
#dada = w.create_image(test.position[0],test.position[1], image = test.photo)
#test.rotate(45)
#test.translate(100)
#dada = w.create_image(test.position[0],test.position[1], image = test.photo)

win3 = Toplevel() #Create a Tkinter window object for controller TOPLEVEL when you have more than one
win3.title("Primary Robot Controller") #set all primary robot parameters
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

def setPrimary(): #function to 'build' primary robot according to text input
    global primaryRobot #make sure the instance of class is created at the global level for full access
    primaryRobot = Eurobot(int(e8.get()),int(e9.get()),[int(e5.get()),int(e6.get())],int(e7.get()),w) #set parameters according to input fields
    #primaryRobot.abstranslate([100,100])

Label(w3,text="", bg="white").grid(row=5,column=0) #blank space
activate1 = Button(w3, text="Build primary robot", command=setPrimary) #button to set primary robot parameters
activate1.grid(row=6,column=0)

def flipPrimary(): #flip primary robot to other side of arena
    global primaryRobot
    primaryRobot = Eurobot(primaryRobot.track,primaryRobot.diameter,primaryRobot.position,primaryRobot.angle,w) #must initialise again to retrieve the instance (needs fix)
    
    try:
        primaryRobot
    except NameError:
        tkMessageBox.showerror('Unable to flip robot!','Robot has not been built!')
    else:
        primaryRobot.rotate(180)
        print "Flipped primary robot"
        reflect = datum[0] - boundsize[0]/2 #X co-ordinate of line of reflection
        primaryRobot.abstranslate([2*(reflect - primaryRobot.position[0]),0])
    
flip1 = Button(w3, text="Flip sides", command=flipPrimary)
flip1.grid(row=6,column=1)
Label(w3,text="", bg="white").grid(row=7,column=0) #blank space

#Some reason unable to animate robot unless it is done in the same function that created it
moveButton = Button(w3, text="Move to co-ordinate")
moveButton.grid(row=8,column=0)

def printcoords(event):
    global targetPoint,pixeltoCM,datum,firstPoint,targetPoint2,measureLine,targetPoint3, reddot

    if isRecording == False:
        reddot = False
        firstPoint = [event.x,event.y]
        w.delete(targetPoint)
        w.delete(targetPoint2)
        w.delete(targetPoint3)
        w.delete(measureLine)
        w.delete(angleLine)
        print("Clicked co-ordinate (X,Y):")
        print(int(-(event.x - datum[0])/pixeltoCM[0]),int(-(event.y - datum[1])/pixeltoCM[1]))
        print;
        drawcircle(w,event.x,event.y,5)

def linecoords(event):
    global firstPoint,pixeltoCM,datum,targetPoint2,measureLine,isRecording,targetPoint3,secondPoint,reddot,linevector
    
    if isRecording == False:
        reddot = True
        secondPoint = [event.x,event.y]
        w.delete(targetPoint2)
        w.delete(targetPoint3)
        w.delete(measureLine)
        w.delete(angleLine)
        measureLine = w.create_line(event.x,event.y,firstPoint[0],firstPoint[1])
        linevector = [secondPoint[0]-firstPoint[0],secondPoint[1]-firstPoint[1]]
        print("Distance measurements [dX dY]:")
        distance = [int(-(firstPoint[0] - event.x)/pixeltoCM[0]),int((firstPoint[1] - event.y)/pixeltoCM[1])]
        magnitude =  numpy.array([round(-(firstPoint[0] - event.x)/pixeltoCM[0],0),round(-(firstPoint[1] - event.y)/pixeltoCM[1],0)])
        angle = round(math.degrees(math.atan2(distance[0],(distance[1] + 0.0001))),0)
        print "[" + str(distance[0]) + " " + str(distance[1]) + "]" + " heading: " + str(-angle) + "deg from N"
        #UNCOMMENT BELOW FOR DISTANCE MEASUREMENT MAGNITUDE
        print round(numpy.linalg.norm(magnitude),2)
        print;
        drawcirclered(w,event.x,event.y,5)

def anglemeasure(event):
    global targetPoint3, angleLine, secondPoint, isRecording, reddot, linevector

    if isRecording == False and reddot == True:
        w.delete(targetPoint3)
        w.delete(angleLine)
        drawcirclegreen(w,event.x,event.y,5)
        angleLine = w.create_line(event.x,event.y,secondPoint[0],secondPoint[1])
        secondvector = [event.x - secondPoint[0],event.y - secondPoint[1]]

        #Dot product of A&B = |A||B|cos(theta)
        dot = numpy.vdot(linevector,secondvector)
        costheta = dot/numpy.linalg.norm(linevector)/numpy.linalg.norm(secondvector)
        theta = math.acos(costheta)
        print "Angle BlueRedGreen:"
        print str(180-int(math.degrees(theta))) + "deg"
        print
        
w.bind("<Button 1>",printcoords)
w.bind("<Button 3>",linecoords)
w.bind("<Button 2>",anglemeasure)

mainloop()
