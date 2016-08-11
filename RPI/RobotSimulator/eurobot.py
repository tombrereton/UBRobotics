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
            self.angle = angle #init heading of robot where 0 is NORTH and is positive counter-clockwise
            self.image = Image.open("robot.jpg") #import image
            self.image = self.image.resize((track, diameter), Image.ANTIALIAS) #resize image to match track and wheel diameter
            photo = ImageTk.PhotoImage(self.image.rotate(self.angle+180)) #convert for ImageTK format (180 deg such that the feet of the robot picture is the forward direction)
            self.robot = self.canvas.create_image(self.position[0],self.position[1],image = photo) #display the PhotoImage object

            print "Created primary robot - Track: %d, Diameter: %d, Heading: %d Position: [%d, %d]" % (self.track,self.diameter,self.angle,self.position[0],self.position[1])
            print
        else:
            tkMessageBox.showerror('Robot creation failed!','Invalid parameters detected!')

    def translate(self,distance): #move according to robot heading and distance 
        print "Robot at angle: %f" % self.angle
        x_vector = -math.sin(math.radians(self.angle)) #Work out X and Y displacement vectors according to heading
        y_vector = -math.cos(math.radians(self.angle))
        print "Vector: [%f, %f]" % (x_vector, y_vector)

        self.position[0] += distance * x_vector #add to current position
        self.position[1] += distance * y_vector
        print "Moving from: [%d, %d] to [%d, %d]" % (self.position[0] - distance * x_vector,self.position[1] - distance *y_vector,self.position[0],self.position[1]) #written like this as python doesn't have constants
     
        self.canvas.move(self.robot, distance * x_vector, distance * y_vector) #move by given vector

    def abstranslate(self,distance): #move regardless of heading
        self.position[0] += distance[0]
        self.position[1] += distance[1]
        self.canvas.move(self.robot, distance[0], distance[1]) #move by given vector
        print self.position
        
    def rotate(self,degrees):
        self.angle += degrees
        print "Rotated by %d to a heading of %d" % (degrees, self.angle) 
        photo = ImageTk.PhotoImage(self.image.rotate(self.angle))
        self.robot = self.canvas.create_image(self.position[0],self.position[1],image = photo)
        
