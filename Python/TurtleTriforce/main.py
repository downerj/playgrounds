#!/usr/bin/env python3

import turtle
from turtle import Screen, Turtle

scr_width = 400
scr_height = 400
s = Screen()
s.bgcolor("black")
s.title("Triforce")
w = s.getcanvas().winfo_toplevel()
s.setup(width=scr_width, height=scr_height)
w.resizable(width=False, height=False)
s.setworldcoordinates(llx=0, lly=0, urx=scr_width, ury=scr_height)
w.attributes("-alpha", 0.9)

dist = min(scr_width, scr_height)/2
t = Turtle()
t.penup()
t.pensize(3)
t.color("yellow")
# t.pencolor("white")
# t.fillcolor("yellow")

# First triangle

t.setheading(0)
t.pendown()
t.begin_fill()
for _ in range(3):
    t.forward(dist)
    t.left(120)
t.end_fill()
t.penup()

# Second triangle

t.forward(dist)

t.setheading(0)
t.pendown()
t.begin_fill()
for _ in range(3):
    t.forward(dist)
    t.left(120)
t.end_fill()
t.penup()

# Third triangle

t.left(120)
t.forward(dist)

t.setheading(0)
t.pendown()
t.begin_fill()
for _ in range(3):
    t.forward(dist)
    t.left(120)
t.end_fill()
t.penup()

t.hideturtle()

turtle.done()
