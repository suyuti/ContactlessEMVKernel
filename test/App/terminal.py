#!/usr/bin/env python
import scardreadermodule
import emvclessmodule
from Tkinter import *

print scardreadermodule.SelectReader(-1)

       
def call(num):
    if num == 'RST':
        scardreadermodule.ResetCard()
    else:
        content = display.get() + num
        display.set(content)

def calculate():
    try:
        content = display.get()
        result = eval(content)
        display.set(content + '=\n' + str(result))
    except:
        display.set('Error')
        clear()

def clear():
    display.set('')

def backspace():
    display.set(str(display.get()[:-1]))
   
def main():
    root = Tk()
    root.title('Terminal')
    root.geometry('210x200+300+400')
    global display
    display = StringVar()   
    label = Label(root, relief = 'sunken', borderwidth = 3, anchor = SE)
    label.config(bg = 'grey', width = 25, height = 3)
    label['textvariable'] = display
    label.grid(row = 0, column = 0, columnspan = 4)
   
    #Button(root, text = 'C', fg = '#EF7321', width = 3, command = lambda: clear()).grid(row = 1, column = 0)
    #Button(root, text = 'DEL', width = 3, command = lambda:backspace()).grid(row = 1, column = 1)
       
    #Button(root, text = '/', width = 3, command = lambda:call('/')).grid(row = 1, column = 2)
    #Button(root, text = '*', width = 3, command = lambda:call('*')).grid(row = 1, column = 3)
    Button(root, text = '7', width = 3, command = lambda:call('7')).grid(row = 2, column = 0)
    Button(root, text = '8', width = 3, command = lambda:call('8')).grid(row = 2, column = 1)
    Button(root, text = '9', width = 3, command = lambda:call('9')).grid(row = 2, column = 2)
    Button(root, text = 'RST', width = 3, command = lambda:call('RST')).grid(row = 2, column = 3)
    Button(root, text = '4', width = 3, command = lambda:call('4')).grid(row = 3, column = 0)
    Button(root, text = '5', width = 3, command = lambda:call('5')).grid(row = 3, column = 1)
    Button(root, text = '6', width = 3, command = lambda:call('6')).grid(row = 3, column = 2)
    #Button(root, text = '+', width = 3, command = lambda:call('+')).grid(row = 3, column = 3)
    Button(root, text = '1', width = 3, command = lambda:call('1')).grid(row = 4, column = 0)
    Button(root, text = '2', width = 3, command = lambda:call('2')).grid(row = 4, column = 1)
    Button(root, text = '3', width = 3, command = lambda:call('3')).grid(row = 4, column = 2)
    #Button(root, text = '=', width = 3, bg = '#EF7321', height = 3,command = lambda:calculate()).grid(row = 4, column = 3, rowspan = 2)
    Button(root, text = 'CLR', width = 3, command = lambda:call('0')).grid(row = 5, column = 0)
    Button(root, text = '0', width = 3, command = lambda:call('0')).grid(row = 5, column = 1)
    Button(root, text = 'ENT', width = 3, command = lambda:call('.')).grid(row = 5, column = 2) 
   
    root.mainloop()

if __name__ == '__main__':
    main()

'''


from Tkinter import *



print scardreadermodule.SelectReader(-1)
scardreadermodule.ResetCard()
print scardreadermodule.Transmit("00A40402010200")
scardreadermodule.Disconnect()
'''