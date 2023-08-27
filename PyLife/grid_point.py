class GridPoint:
    def __init__(self, x: int = 0, y: int = 0):
        self._x = x
        self._y = y

    @property
    def x(self) -> int:
        return self._x

    @property
    def y(self) -> int:
        return self._y

    @x.setter
    def x(self, rhs: int):
        self._x = rhs

    @y.setter
    def y(self, rhs: int):
        self._y = rhs

    def clone(self):
        return GridPoint(self._x, self._y)
