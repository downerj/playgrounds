from entity import Entity
from grid_point import GridPoint
from velocity import Velocity


class Moveable(Entity):
    def __init__(self, pos: GridPoint = None, vel: Velocity = None):
        super().__init__(pos)
        if vel is None:
            self._velocity = Velocity()
        else:
            self._velocity = vel.clone()

    def move(self):
        self._position.x += self._velocity.dx
        self._position.y += self._velocity.dy

    def stop(self):
        self._velocity.dx = 0
        self._velocity.dy = 0
