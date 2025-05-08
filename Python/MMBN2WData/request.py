import sys
from typing import List
import urllib.request


class Application:
    def __init__(self) -> None:
        self._page_url: str = "https://megaman.fandom.com/wiki/List_of_Mega_Man_Battle_Network_3_Battle_Chips"
        self._html_file_name: str = "chips.html"

    def main(self, args: List[str]) -> None:
        with urllib.request.urlopen(self._page_url) as response:
            html: bytes = response.read()
            with open(self._html_file_name, "w+") as file:
                file.write(str(html, "UTF-8"))
            

if __name__ == "__main__":
    Application().main(sys.argv[1:])
