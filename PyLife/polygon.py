class Polygon:
    def __init__(self, *points):
        self._points = (*points,)

    def __iter__(self):
        return self._points.__iter__()

    @property
    def points(self) -> tuple:
        return self._points

    def clone(self):
        return Polygon(*self._points)


SQUARE = Polygon(
    (-1.0, -1.0), (1.0, -1.0), (1.0, 1.0), (-1.0, 1.0),
)
DIAMOND = Polygon(
    (0.0, -1.0), (1.0, 0.0), (0.0, 1.0), (-1.0, 0.0),
)
TRIANGLE_N = Polygon(
    (0.0, -1.0), (1.0, 1.0), (-1.0, 1.0),
)
TRIANGLE_E = Polygon(
    (1.0, 0.0), (-1.0, 1.0), (-1.0, -1.0),
)
TRIANGLE_S = Polygon(
    (0.0, 1.0), (-1.0, -1.0), (1.0, -1.0),
)
TRIANGLE_W = Polygon(
    (-1.0, 0.0), (1.0, -1.0), (1.0, 1.0),
)
