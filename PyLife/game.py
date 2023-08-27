from random import randint

import pygame

from draw_handler import DrawHandler
from entity_handler import EntityHandler
from grid import Grid
from grid_point import GridPoint
from plant import Plant
from wanderer import Wanderer


class Game:
    def __init__(self):
        # display settings
        self._scr_w = 600
        self._scr_h = 600
        self._grid_w = 30
        self._grid_h = 30
        scr_dims = (self._scr_w, self._scr_h)
        self._screen = pygame.display.set_mode(scr_dims)
        self._grid = Grid(self._scr_w, self._scr_h, self._grid_w, self._grid_h)
        pygame.display.set_caption("Senora Colonies")

        # game settings
        self._entities = []
        num_wanderers = 20
        for w in range(0, num_wanderers):
            x = randint(0, self._grid_w - 1)
            y = randint(0, self._grid_h - 1)
            prob = randint(0, 20)
            self._entities.append(Wanderer(GridPoint(x, y), prob))
        num_plants = 30
        for p in range(0, num_plants):
            x = randint(0, self._grid_w - 1)
            y = randint(0, self._grid_h - 1)
            self._entities.append(Plant(GridPoint(x, y)))

        # handlers
        self._hdl_entities = EntityHandler(self._grid, self._entities)
        self._hdl_draw = DrawHandler(self._screen, self._grid, self._entities)

        # timer settings
        self._framerate = 20
        self._interval = 1000 // self._framerate
        self._paused = False

    def _handle_input(self) -> bool:
        for event in pygame.event.get():
            # X window button -> quit
            if event.type == pygame.QUIT:
                return False

            # discrete keyboard input
            elif event.type == pygame.KEYUP:
                if event.mod & pygame.KMOD_CTRL:
                    # Ctrl + Q or Ctrl + W -> quit
                    if event.key == pygame.K_q or event.key == pygame.K_w:
                        return False
                elif event.mod & pygame.KMOD_ALT:
                    # Alt + F4 -> quit
                    if event.key == pygame.K_F4:
                        return False

                # P -> pause
                elif event.key == pygame.K_p:
                    self._paused = not self._paused

        return True

    def run(self):
        while True:
            # wait a bit before proceeding in order to give a more
            # arcade-like animation effect
            pygame.time.delay(self._interval)

            # get input
            running = self._handle_input()
            if not running:
                break

            # update the grid
            self._hdl_entities.update()

            # draw the grid and characters
            self._hdl_draw.update()


if __name__ == "__main__":
    game = Game()
    game.run()
