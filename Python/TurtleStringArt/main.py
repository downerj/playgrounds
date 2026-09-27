#!/usr/bin/env python3

import itertools
import sys
from tkinter import TclError
import turtle
from turtle import Screen, Turtle

s = Screen()
w = s.getcanvas().winfo_toplevel()
t = Turtle()
screen_width = 400
screen_height = 400


def setup() -> None:
    s.bgcolor("black")
    s.title("String Art")
    s.setup(width=screen_width, height=screen_height)
    s.setworldcoordinates(llx=0, lly=0, urx=screen_width, ury=screen_height)

    w.resizable(width=False, height=False)
    w.attributes("-alpha", 0.85)

    t.speed("fastest")
    t.pensize(3)
    t.hideturtle()


def draw() -> None:
    colors = [
        "#ff0000", "#ff7700", "#ffff00", "#77ff00",
        "#00ff00", "#00ff77", "#00ffff", "#0077ff",
        "#0000ff", "#7700ff", "#ff00ff", "#ff0077"
    ]
    num_nodes = len(colors) * 3
    delta_x = screen_width / num_nodes
    delta_y = screen_height / num_nodes

    color_iter = itertools.cycle(colors)
    for n in range(num_nodes + 1):
        x0 = 0
        y0 = delta_y * n
        x1 = delta_x * n
        y1 = screen_height
        t.pencolor(next(color_iter))
        t.goto(x0, y0)
        t.pendown()
        t.goto(x1, y1)
        t.penup()

    color_iter = itertools.cycle(colors)
    for n in range(num_nodes + 1):
        x0 = delta_x * n
        y0 = 0
        x1 = screen_height
        y1 = delta_y * n
        t.pencolor(next(color_iter))
        t.goto(x0, y0)
        t.pendown()
        t.goto(x1, y1)
        t.penup()


def main() -> None:
    setup()
    draw()
    print("Done")
    if sys.flags.interactive != 1 and sys.flags.inspect != 1:
        turtle.done()


if __name__ == "__main__":
    sys.tracebacklimit = 0
    try:
        main()
    except TclError as e:
        print(f"Operation aborted: {e}", file=sys.stderr)
