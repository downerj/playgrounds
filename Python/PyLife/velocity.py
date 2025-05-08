DIR_NONE = 0
DIR_UP = 1
DIR_RIGHT = 2
DIR_DOWN = 3
DIR_LEFT = 4


def is_list(val):
    return isinstance(val, list) or isinstance(val, tuple)


class Velocity:
    def __init__(self, dx: int = 0, dy: int = 0):
        self._dx = dx
        self._dy = dy

    @property
    def dx(self) -> int:
        return self._dx

    @property
    def dy(self) -> int:
        return self._dy

    @dx.setter
    def dx(self, rhs: int):
        self._dx = rhs

    @dy.setter
    def dy(self, rhs: int):
        self._dy = rhs

    def __eq__(self, rhs):
        if is_list(rhs):
            return rhs[0] == self._dx and rhs[1] == self._dy
        else:
            return rhs.dx == self._dx and rhs.dy == self._dy

    def __neg__(self):
        return Velocity(-self._dx, -self._dy)

    def __add__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx += rhs[0]
            dy += rhs[1]
        else:
            dx += rhs
            dy += rhs

        return Velocity(int(dx), int(dy))

    def __sub__(self, rhs):
        return self.__add__(-rhs)

    def __mul__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx *= rhs[0]
            dy *= rhs[1]
        else:
            dx *= rhs
            dy *= rhs

        return Velocity(int(dx), int(dy))

    def __floordiv__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx //= rhs[0]
            dy //= rhs[1]
        else:
            dx //= rhs
            dy //= rhs

        return Velocity(int(dx), int(dy))

    def __truediv__(self, rhs):
        return self.__floordiv__(rhs)

    def __pow__(self, rhs, modulo=None):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx **= rhs[0]
            dy **= rhs[1]
        else:
            dx **= rhs
            dy **= rhs

        return Velocity(int(dx), int(dy))

    def __iadd__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx += rhs[0]
            dy += rhs[1]
        else:
            dx += rhs
            dy += rhs

        self._dx = int(dx)
        self._dy = int(dy)

    def __isub__(self, rhs):
        self.__iadd__(-rhs)

    def __imul__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx *= rhs[0]
            dy *= rhs[1]
        else:
            dx *= rhs
            dy *= rhs

        self._dx = int(dx)
        self._dy = int(dy)

    def __ifloordiv__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx //= rhs[0]
            dy //= rhs[1]
        else:
            dx //= rhs
            dy //= rhs

        self._dx = int(dx)
        self._dy = int(dy)

    def __itruediv__(self, rhs):
        self.__ifloordiv__(rhs)

    def __ipow__(self, rhs):
        dx = self._dx
        dy = self._dy

        if is_list(rhs):
            dx **= rhs[0]
            dy **= rhs[1]
        else:
            dx **= rhs
            dy **= rhs

        self._dx = int(dx)
        self._dy = int(dy)

    def clone(self):
        return Velocity(self._dx, self._dy)
