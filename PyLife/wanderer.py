from random import randint

from colors import ORANGE
from draw_handler import DrawData
from grid_point import GridPoint
from moveable import Moveable
from polygon import DIAMOND, TRIANGLE_N, TRIANGLE_E, TRIANGLE_S, TRIANGLE_W
from velocity import DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_NONE


class Wanderer(Moveable):
    def __init__(self, pos: GridPoint = None, wait_prob=1):
        super().__init__(pos, None)
        self._max_rand = 3
        self._direction = DIR_NONE
        self._draw_data = DrawData(DIAMOND, ORANGE, False)

        if wait_prob > 1:
            self._max_rand += wait_prob

    def draw(self) -> DrawData:
        if self._direction == DIR_UP:
            poly = TRIANGLE_N
        elif self._direction == DIR_RIGHT:
            poly = TRIANGLE_E
        elif self._direction == DIR_DOWN:
            poly = TRIANGLE_S
        elif self._direction == DIR_LEFT:
            poly = TRIANGLE_W
        else:
            poly = DIAMOND

        self._draw_data.polygon = poly

        return self._draw_data

    def move(self):
        self._direction = randint(0, self._max_rand)

        if self._direction == DIR_UP:
            dx = 0
            dy = -1
        elif self._direction == DIR_RIGHT:
            dx = +1
            dy = 0
        elif self._direction == DIR_DOWN:
            dx = 0
            dy = +1
        elif self._direction == DIR_LEFT:
            dx = -1
            dy = 0
        else:
            dx = 0
            dy = 0

        self._velocity.dx = dx
        self._velocity.dy = dy
        super().move()
