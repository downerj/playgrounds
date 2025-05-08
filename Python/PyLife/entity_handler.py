from grid import Grid
from moveable import Moveable


class EntityHandler:
    def __init__(self, grid: Grid, entities: list):
        self._grid = grid
        self._entities = entities

    def update(self):
        for entity in self._entities:
            # check for collision with neighbors
            # TODO: get all 8 neighbors and check collisions in order

            # move entity
            if isinstance(entity, Moveable):
                entity.move()
                entity.position = self._grid.wrap_point(entity.position)
