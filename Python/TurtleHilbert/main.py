#!/usr/bin/env python3

import itertools
import sys
import turtle
from turtle import Screen, Turtle
from typing import Iterator

s = Screen()
w = s.getcanvas().winfo_toplevel()
t = Turtle()
dist = 0


def setup() -> None:
    screen_width = 400
    screen_height = 400
    global dist
    dist = min(screen_width, screen_height) / 15.0

    s.bgcolor("black")
    s.title("Hilbert Curve")
    s.setup(width=screen_width, height=screen_height)
    s.setworldcoordinates(llx=0, lly=0, urx=screen_width, ury=screen_height)

    w.resizable(width=False, height=False)
    w.attributes("-alpha", 0.92)

    t.speed("fastest")
    t.pensize(3)


# This algorithm is adapted from:
# https://craftofcoding.wordpress.com/2024/02/20/recursive-patterns-the-hilbert-curve/
def hilbert(level: int, angle: float, color_iter: Iterator[str]) -> None:
    if level <= 0:
        return

    t.left(angle)
    hilbert(level - 1, -angle, color_iter)
    t.pencolor(next(color_iter))
    t.forward(dist)
    t.right(angle)
    hilbert(level - 1, angle, color_iter)
    t.pencolor(next(color_iter))
    t.forward(dist)
    hilbert(level - 1, angle, color_iter)
    t.right(angle)
    t.pencolor(next(color_iter))
    t.forward(dist)
    hilbert(level - 1, -angle, color_iter)
    t.left(angle)


def main() -> None:
    setup()
    colors = ["red", "orange", "yellow", "lime", "cyan", "blue", "purple", "magenta"]
    t.pendown()
    hilbert(level=4, angle=90, color_iter=itertools.cycle(colors))
    t.hideturtle()
    if sys.flags.interactive != 1 and sys.flags.inspect != 1:
        turtle.done()


if __name__ == "__main__":
    main()
