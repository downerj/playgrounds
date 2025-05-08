from grid_point import GridPoint


class Grid:
    def __init__(self, scr_w: int, scr_h: int, grid_w: int, grid_h: int):
        self._w = grid_w
        self._h = grid_h
        self._cell_w = scr_w // self._w
        self._cell_h = scr_h // self._h

    def compute_pixel(self, x: int, y: int) -> list:
        px_x = x * self._cell_w
        px_y = y * self._cell_h

        return [px_x, px_y]

    def compute_pixels(self, points: list) -> list:
        pixels = []

        for pt in points:
            px_x = pt.x * self._cell_w
            px_y = pt.y * self._cell_h
            pixels.append([px_x, px_y])

        return pixels

    def is_in_bounds(self, point: GridPoint) -> bool:
        x = point.x
        y = point.y

        return (0 <= x < self._w) and (0 <= y < self._h)

    def wrap_point(self, point: GridPoint) -> GridPoint:
        point.x %= self._w
        point.y %= self._h

        return point

    @property
    def width(self) -> int:
        return self._w

    @property
    def height(self) -> int:
        return self._h

    @property
    def cell_width(self) -> int:
        return self._cell_w

    @property
    def cell_height(self) -> int:
        return self._cell_h
