#!/usr/bin/env python3

# Disable pylint "missing docstring" warnings
# pylint: disable=C0114
# pylint: disable=C0115
# pylint: disable=C0116

import dataclasses
from enum import Enum
import itertools
from queue import Queue
import sys
from tkinter import TclError
import turtle
from turtle import Screen, Terminator, Turtle, TurtleGraphicsError
from typing import List


class BoxType(Enum):
    HORIZONTAL = 0
    VERTICAL = 1


@dataclasses.dataclass
class Line:
    x0 = 0.0
    y0 = 0.0
    x1 = 0.0
    y1 = 0.0


@dataclasses.dataclass
class Box:
    x0 = 0.0
    y0 = 0.0
    x1 = 0.0
    y1 = 0.0
    box_type = BoxType.HORIZONTAL
    depth = 0


class App:
    screen = Screen()
    window = screen.getcanvas().winfo_toplevel()
    turtle = Turtle()
    screen_width = 400
    screen_height = 400
    max_depth = 11

    def __init__(self) -> None:
        self.screen.bgcolor("black")
        self.screen.title("Fractal Box")
        self.screen.setup(width=self.screen_width, height=self.screen_height)
        self.screen.setworldcoordinates(llx=0, lly=0, urx=self.screen_width, ury=self.screen_height)

        self.window.resizable(width=False, height=False)
        self.window.attributes("-alpha", 0.85)

        self.turtle.speed("fastest")
        self.turtle.pensize(3)
        self.turtle.hideturtle()

    def make_top_box(self) -> Box:
        box = Box()
        box.x0 = 0
        box.y0 = 0
        box.x1 = self.screen_width
        box.y1 = self.screen_height
        box.box_type = BoxType.VERTICAL
        box.depth = 0
        return box

    def draw_top_box(self, box: Box, color: str) -> None:
        self.turtle.penup()
        self.turtle.goto(box.x0, box.y0)
        self.turtle.pencolor(color)
        self.turtle.pendown()
        self.turtle.goto(box.x1, box.y0)
        self.turtle.goto(box.x1, box.y1)
        self.turtle.goto(box.x0, box.y1)
        self.turtle.goto(box.x0, box.y0)

    @staticmethod
    def make_box_line(box: Box) -> Line:
        line = Line()
        if box.box_type == BoxType.HORIZONTAL:
            line.x0 = box.x0 + (box.x1 - box.x0)/2.0
            line.y0 = box.y0
            line.x1 = line.x0
            line.y1 = box.y1
        else:
            line.x0 = box.x0
            line.y0 = box.y0 + (box.y1 - box.y0)/2.0
            line.x1 = box.x1
            line.y1 = line.y0
        return line

    def draw_line(self, line: Line, color: str) -> None:
        self.turtle.penup()
        self.turtle.goto(line.x0, line.y0)
        self.turtle.pendown()
        self.turtle.pencolor(color)
        self.turtle.goto(line.x1, line.y1)

    @staticmethod
    def make_box_child_a(box: Box, line: Line) -> Box:
        box_child = Box()
        box_child.x0 = box.x0
        box_child.y0 = box.y0
        box_child.x1 = line.x1
        box_child.y1 = line.y1
        if box.box_type == BoxType.HORIZONTAL:
            box_child.box_type = BoxType.VERTICAL
        else:
            box_child.box_type = BoxType.HORIZONTAL
        box_child.depth = box.depth + 1
        return box_child

    @staticmethod
    def make_box_child_b(box: Box, line: Line) -> Box:
        box_child = Box()
        box_child.x0 = line.x0
        box_child.y0 = line.y0
        box_child.x1 = box.x1
        box_child.y1 = box.y1
        if box.box_type == BoxType.HORIZONTAL:
            box_child.box_type = BoxType.VERTICAL
        else:
            box_child.box_type = BoxType.HORIZONTAL
        box_child.depth = box.depth + 1
        return box_child

    def handle_box_horizontal(self, box: Box, color: str) -> List[Box]:
        line = self.make_box_line(box)
        self.draw_line(line, color)
        if box.depth < self.max_depth:
            return [self.make_box_child_a(box, line), self.make_box_child_b(box, line)]
            # return [self.make_box_child_b(box, line)]
        return []

    def handle_box_vertical(self, box: Box, color: str) -> List[Box]:
        line = self.make_box_line(box)
        self.draw_line(line, color)
        if box.depth < self.max_depth:
            # return [self.make_box_child_a(box, line), self.make_box_child_b(box, line)]
            return [self.make_box_child_a(box, line)]
        return []

    def draw_boxes(self) -> None:
        colors = [
            "#ff0000", "#ff7700", "#ffff00", "#77ff00",
            "#00ff00", "#00ff77", "#00ffff", "#0077ff",
            "#0000ff", "#7700ff", "#ff00ff", "#ff0077"
        ]
        colors_iter = itertools.cycle(colors)
        color = next(colors_iter)

        boxes = Queue[Box]()
        top_box = self.make_top_box()
        boxes.put(top_box)
        self.draw_top_box(top_box, color)

        previous_depth = -1
        while not boxes.empty():
            box = boxes.get()
            if box.depth > previous_depth:
                color = next(colors_iter)
                previous_depth = box.depth
            if box.box_type == BoxType.HORIZONTAL:
                child_boxes = self.handle_box_horizontal(box, color)
                for child_box in child_boxes:
                    boxes.put(child_box)
            else:
                child_boxes = self.handle_box_vertical(box, color)
                for child_box in child_boxes:
                    boxes.put(child_box)

    def main(self) -> None:
        self.draw_boxes()
        print("Done")
        if sys.flags.interactive != 1 and sys.flags.inspect != 1:
            turtle.done()


if __name__ == "__main__":
    sys.tracebacklimit = 0
    app = App()
    try:
        app.main()
    except (TclError, Terminator, TurtleGraphicsError) as e:
        print(f"Operation aborted: {e}", file=sys.stderr)
