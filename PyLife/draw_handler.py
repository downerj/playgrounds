import pygame

from colors import *
from grid import Grid
from polygon import Polygon


class DrawData:
    def __init__(self, polygon: Polygon, color: tuple = WHITE, filled: bool = False):
        self._polygon = polygon
        self._color = color
        self._filled = filled

    @property
    def polygon(self) -> Polygon:
        return self._polygon

    @property
    def color(self) -> tuple:
        return self._color

    @property
    def filled(self) -> bool:
        return self._filled

    @polygon.setter
    def polygon(self, rhs: Polygon):
        self._polygon = rhs

    @color.setter
    def color(self, rhs: tuple):
        self._color = rhs

    @filled.setter
    def filled(self, rhs: bool):
        self._filled = rhs

    def clone(self):
        return DrawData(self._polygon, self._color, self._filled)


class DrawHandler:
    def __init__(self, screen: pygame.Surface, grid: Grid, entities: list, **kwargs):
        self._screen = screen
        self._grid = grid
        self._entities = entities
        self._bg_color = BLACK
        self._line_width = 2

        for key, value in kwargs.items():
            if key == "bg_color":
                self._bg_color = value
            elif key == "line_width":
                self._line_width = value
            else:
                raise KeyError(f'Unknown keyword argument "{key}"')

    def update(self):
        # draw background
        self._screen.fill(self._bg_color)

        # draw entities
        for entity in self._entities:
            pos = entity.position
            draw_data = entity.draw()
            poly = draw_data.polygon
            color = draw_data.color
            filled = draw_data.filled

            # get cell center
            xc = pos.x + 0.5
            yc = pos.y + 0.5

            # get pixel points
            pixels = []
            for pt in poly:
                # compute poly points within cell
                xp = xc + 0.5 * pt[0]
                yp = yc + 0.5 * pt[1]

                # scale to display
                px = self._grid.compute_pixel(xp, yp)
                pixels.append(px)

            if filled:
                line_w = 0
            else:
                line_w = self._line_width

            pygame.draw.polygon(self._screen, color, pixels, line_w)

        pygame.display.flip()
