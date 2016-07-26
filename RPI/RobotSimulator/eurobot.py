from Tkinter import *
import tkMessageBox
from PIL import Image, ImageTk
import math
import time

class Eurobot(object):
    def __init__(self,track,diameter,position,angle,canvas): #Constructor where canvas is current tkinter-canvas object
        if track > 0 and diameter > 0:
            global photo #IMPORTANT BUT WHY
            self.canvas = canvas #init to current canvas
            self.track = track #Distance between wheels
            self.diameter = diameter #Diameter of wheels
            self.position = position #init position
            self.angle = angle
            self.image = Image.open("robot.jpg") #import image
            self.image = self.image.resize((track, diameter), Image.ANTIALIAS)
            photo = ImageTk.PhotoImage(self.image.rotate(self.angle)) #convert for ImageTK format        
            self.robot = self.canvas.create_image(self.position[0],self.position[1],image = photo)

            print "Created primary robot - Track: %d, Diameter: %d, Heading: %d Position: [%d, %d]" % (self.track,self.diameter,self.angle,self.position[0],self.position[1])
        else:
            tkMessageBox.showerror('Robot creation failed!','Invalid parameters detected!')

    def translate(self,distance):
        print "Robot at angle: %f" % self.angle
        x_vector = -math.sin(math.radians(self.angle))
        y_vector = math.cos(math.radians(self.angle))
        print "Vector: [%f, %f]" % (x_vector, y_vector)

        self.position[0] += distance * x_vector
        self.position[1] -= distance * y_vector
        print "Moving from: [%d, %d] to [%d, %d]" % (self.position[0] - distance * x_vector,self.position[1] + distance *y_vector,self.position[0],self.position[1])
        time.sleep(1)
        self.canvas.move(self.robot,x_vector,y_vector)
        
    def rotate(self,degrees):
        self.angle += degrees
        self.photo = ImageTk.PhotoImage(self.image.rotate(self.angle))
