#!/usr/bin/env python3

import math
from queue import Queue
# import random
import sys
from tkinter import TclError
import turtle
from turtle import Screen, Turtle

s = Screen()
w = s.getcanvas().winfo_toplevel()
t = Turtle()


def setup(screen_width: int, screen_height: int) -> None:
    s.bgcolor("black")
    s.title("Fractal Tree")
    s.setup(width=screen_width, height=screen_height)
    s.setworldcoordinates(llx=0, lly=0, urx=screen_width, ury=screen_height)

    w.resizable(width=False, height=False)
    w.attributes("-alpha", 0.85)

    t.speed("fastest")
    t.pensize(3)
    t.hideturtle()


class Branch:
    x = 0.0
    y = 0.0
    length = 0.0
    angle = 0.0
    depth = 0

    def make_child(self, scale: float, rotation: float) -> Branch:
        rad = math.radians(self.angle)
        cosA = math.cos(rad)
        sinA = math.sin(rad)
        child = Branch()
        child.x = self.x + self.length*cosA
        child.y = self.y + self.length*sinA
        child.length = self.length*scale
        child.angle = self.angle + rotation
        child.depth = self.depth + 1
        return child


def draw_tree(x: float, y: float, length: float, angle: float) -> None:
    # Disable animations, need to manually update later
    turtle.tracer(0)

    trunk = Branch()
    trunk.x = x
    trunk.y = y
    trunk.length = length
    trunk.angle = angle
    tree: Queue[Branch] = Queue()
    tree.put(trunk)
    max_depth = 6
    colors = ["red", "orange", "yellow", "lime", "cyan", "blue", "magenta"]
    # Previous depth for updating the drawing periodically
    # previous_depth = trunk.depth
    # Branch counter for updating the drawing periodically
    b = 0
    while not tree.empty():
        branch = tree.get()
        t.penup()
        t.setpos(branch.x, branch.y)
        t.setheading(branch.angle)
        t.pencolor(colors[branch.depth % len(colors)])
        t.pendown()
        t.forward(branch.length)
        t.penup()
        if branch.depth < max_depth:
            # Preset child count, scaling & rotation (version 1)
            # scale = 0.6
            # rotation = 60.0
            # tree.put(branch.make_child(scale, rotation))
            # tree.put(branch.make_child(scale, -rotation))

            # Preset child count, scaling & rotation (version 2)
            child_count = 4
            begin_angle = -70.0
            end_angle = 70.0
            delta_angle = (end_angle - begin_angle) / (child_count - 1)
            scale = 0.52
            for c in range(child_count):
                rotation = begin_angle + delta_angle*c
                tree.put(branch.make_child(scale, rotation))

            # Random child count, scaling & rotation
            # child_count = random.randint(2, 8)
            # for _ in range(child_count):
            #     scale = random.randint(50, 70) / 100.0
            #     rotation = random.randint(-60, 60) / 1.0
            #     tree.put(branch.make_child(scale, rotation))
        
        # Update drawing periodically based on branch depth
        # if branch.depth > previous_depth:
        #     previous_depth = branch.depth
        #     turtle.update()

        # Update drawing periodically based on branch count
        b += 1
        if b % child_count == 0:
            turtle.update()


def main() -> None:
    screen_width = 400
    screen_height = 400
    setup(screen_width, screen_height)
    x = screen_width / 2.0
    y = 0.0
    length = min(screen_width, screen_height) / 2.2
    angle = 90.0
    draw_tree(x, y, length, angle)
    print("Done")
    if sys.flags.interactive != 1 and sys.flags.inspect != 1:
        turtle.done()


if __name__ == "__main__":
    sys.tracebacklimit = 0
    try:
        main()
    except TclError as e:
        print(f"Operation aborted: {e}", file=sys.stderr)
