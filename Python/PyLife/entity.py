from draw_handler import DrawData
from grid_point import GridPoint


class Entity:
    def __init__(self, pos: GridPoint = None):
        if pos is None:
            self._position = GridPoint()
        else:
            self._position = pos.clone()

    def draw(self) -> DrawData:
        pass

    @property
    def position(self) -> GridPoint:
        return self._position.clone()

    @property
    def x(self) -> int:
        return self._position.x

    @property
    def y(self) -> int:
        return self._position.y

    @position.setter
    def position(self, rhs: GridPoint):
        self._position = rhs.clone()

    @x.setter
    def x(self, rhs: int):
        self._position.x = rhs

    @y.setter
    def y(self, rhs: int):
        self._position.y = rhs
