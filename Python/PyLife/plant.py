from draw_handler import DrawData, GREEN
from entity import Entity
from grid_point import GridPoint
from polygon import SQUARE


class Plant(Entity):
    DRAW_DATA = DrawData(
        SQUARE,
        GREEN,
        False
    )

    def __init__(self, position: GridPoint):
        super().__init__(position)

    def draw(self) -> DrawData:
        return Plant.DRAW_DATA
