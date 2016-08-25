from Tkinter import *
from ScrolledText import *

class pathPrint(object):

    def __init__(self,title,textinit):
         
        self.wind = Toplevel() #TOPLEVEL when you have more than one
        self.wind.title(title) 
        self.wind.geometry("400x300")
        self.wi = Canvas(self.wind,bg="white")
        self.wi.pack(expand=YES,fill=BOTH)
        self.text = ScrolledText(master=self.wi, height=30, wrap=WORD)
        self.text.insert(INSERT,textinit)
        self.text.pack()
