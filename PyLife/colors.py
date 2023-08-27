BLACK = (0, 0, 0)
GREY = (127, 127, 127)
GRAY = GREY
WHITE = (255, 255, 255)

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

YELLOW = (255, 255, 0)
CYAN = (0, 255, 255)
MAGENTA = (255, 0, 255)

ORANGE = (255, 127, 0)
CHATREUSE = (127, 255, 0)
SPRING = (0, 255, 127)
AZURE = (0, 127, 255)
VIOLET = (127, 0, 255)
PINK = (255, 0, 127)

DARK_RED = (127, 0, 0)
DARK_GREEN = (0, 127, 0)
DARK_BLUE = (0, 0, 127)

DARK_YELLOW = (127, 127, 0)
DARK_CYAN = (0, 127, 127)
DARK_MAGENTA = (127, 0, 127)

PASTEL_RED = (255, 127, 127)
PASTEL_GREEN = (127, 255, 127)
PASTEL_BLUE = (127, 127, 255)

PASTEL_YELLOW = (255, 255, 127)
PASTEL_CYAN = (127, 255, 255)
PASTEL_MAGENTA = (255, 127, 255)


def int_to_rgb(color: int) -> tuple:
    r = (color >> 16) % 0x100
    g = (color >> 8) % 0x100
    b = (color >> 0) % 0x100

    return r, g, b


def rgb_to_int(rgb: tuple) -> int:
    r = rgb[0] << 16
    g = rgb[1] << 8
    b = rgb[2] << 0

    return r + g + b
