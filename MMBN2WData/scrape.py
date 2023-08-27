from csv import DictWriter
import re
from re import Pattern
import sys
from typing import Any, Dict, List, Optional
import urllib.request
import xml
from xml.etree.ElementTree import Element, ElementTree


REGEX_IMAGE_FILE_NAME: Pattern = re.compile(r"[a-zA-Z0-9-]+\.((gif)|(png)|(jpg)|(jpeg)|(bmp)|(tiff))")
REGEX_SCRIPT_TAG: Pattern = re.compile(r"\<script\>.*\</script\>")


class Chip:
    CSV_HEADER: List[str] = [
        "ID",
        "Source URL",
        "Source File Name",
        "Destination File Name",
        "Name",
        "Damage",
        "Letter Codes",
        "Memory (MB)",
        "Description",
    ]

    def __init__(
        self,
        chip_id: int,
        src_url: str,
        src_alt: str,
        dest_file: str,
        name: str,
        damage: Optional[str],
        letter_codes: List[str],
        memory_mb: int,
        description: str
    ) -> None:
        self.chip_id: int = chip_id
        self.src_url: str = src_url
        self.src_alt: str = src_alt
        self.dest_file: str = dest_file
        self.name: str = name
        self.damage: Optional[str] = damage
        self.letter_codes: List[str] = letter_codes
        self.memory_mb: int = memory_mb
        self.description: str = description

    @property
    def csv(self) -> Dict[str, Any]:
        return {
            "ID": self.chip_id,
            "Source URL": self.src_url,
            "Source File Name": self.src_alt,
            "Destination File Name": self.dest_file,
            "Name": self.name,
            "Damage": self.damage,
            "Letter Codes": "".join(self.letter_codes),
            "Memory (MB)": self.memory_mb,
            "Description": self.description,
        }


class ChipCollection:
    def __init__(
        self,
        standard_chips: List[Chip],
        mega_chips: List[Chip],
        giga_chips: List[Chip]
    ) -> None:
        self.standard_chips: List[Chip] = standard_chips
        self.mega_chips: List[Chip] = mega_chips
        self.giga_chips: List[Chip] = giga_chips


class Application:
    def __init__(self) -> None:
        self._html_file_name: str = "chips.html"
        self._standard_csv_file_name: str = "standard_chips.csv"
        self._mega_csv_file_name: str = "mega_chips.csv"
        self._giga_csv_file_name: str = "giga_chips.csv"
        self._image_directory: str = "chip_images"

    def _get_and_parse_table(self) -> ChipCollection:
        print("Loading HTML file...")
        tree: ElementTree = xml.etree.ElementTree.parse(self._html_file_name)

        print("Getting tables...")
        tables: List[Element] = tree.findall(".//table")[0:3]
        standard_table: Element = tables[0]
        mega_table: Element = tables[1]
        giga_table: Element = tables[2]

        standard_rows: List[Element] = standard_table.findall(".//tr")[1:]
        mega_rows: List[Element] = mega_table.findall(".//tr")[1:]
        giga_rows: List[Element] = [
            *giga_table.findall(".//tr")[1:17],
            *giga_table.findall(".//tr")[18:23]
        ]

        print("Loading standard chips...")
        standard_chips: List[Chip] = self._parse_rows(standard_rows, "Standard")

        print("Loading mega chips...")
        mega_chips: List[Chip] = self._parse_rows(mega_rows, "Mega")

        print("Loading giga chips...")
        giga_chips: List[Chip] = self._parse_rows(giga_rows, "Giga")

        return ChipCollection(
            standard_chips=standard_chips,
            mega_chips=mega_chips,
            giga_chips=giga_chips
        )
    
    def _parse_rows(self, rows: List[Element], table_type: str) -> List[Chip]:
        chips: List[Chip] = []
        
        for row in rows:
            cells: List[Element] = row.findall(".//td")
            
            chip_id_cell: Element = cells[0]
            image_anchor_cell: Element = cells[1].find(".//a")
            image_cell: Element = image_anchor_cell.find(".//img")
            name_cell: Element = cells[2]
            damage_cell: Element = cells[3]
            letter_codes_cell: Element = cells[4]
            memory_cell: Element = cells[5]
            description_cell: Element = cells[6]

            try:
                chip_id_literal: str = chip_id_cell.text.strip()
                chip_id: int = int(chip_id_literal) 
            # If the ID is invalid, then it must be a sub-header row.
            except ValueError:
                print(f"\tError: Chip ID {chip_id_literal} is not an integer.")
                continue
            chip_id_literal = chip_id_literal.zfill(3)

            src_url: str = image_anchor_cell.attrib["href"]
            src_alt: str = image_cell.attrib["data-image-name"]
            alt_ext: str = src_alt.split(".")[-1]
            try:
                name: str = name_cell.text.strip()
            # If the name is empty, then it must be an invalid row.
            except AttributeError:
                name: str = name_cell.find(".//a").text.strip()
            dest_file: str = f"{table_type}_{chip_id_literal}_{name}.{alt_ext}"
            damage: Optional[str] = damage_cell.text.strip()
            if len(damage) == 0:
                damage = None
            letter_codes: List[str] = [
                code.replace(" ", "")
                for code in letter_codes_cell.text.split(",")
            ]
            letter_codes.sort()
            memory_mb: int = int(memory_cell.text.split(" ")[0])
            description: str = description_cell.text

            # Pull the image down.
            print(f"\tGetting {table_type} #{chip_id_literal} {name} ({src_alt}) -> {dest_file}")
            with urllib.request.urlopen(src_url) as response:
                image: bytes = response.read()
                with open(f"{self._image_directory}/{dest_file}", "wb+") as file:
                    file.write(image)

            chips.append(Chip(
                chip_id=chip_id,
                src_url=src_url,
                src_alt=src_alt,
                dest_file=dest_file,
                name=name,
                damage=damage,
                letter_codes=letter_codes,
                memory_mb=memory_mb,
                description=description
            ))
    
        return chips
    
    @staticmethod
    def write_chips_to_csv(chips: List[Chip], file_name: str) -> None:
        with open(file_name, "w+") as file:
            writer: DictWriter = DictWriter(file, Chip.CSV_HEADER)
            writer.writeheader()
            for chip in chips:
                writer.writerow(chip.csv)

    def main(self, args: List[str]) -> None:
        chips: ChipCollection = self._get_and_parse_table()

        print("Writing standard chips CSV...")
        Application.write_chips_to_csv(chips.standard_chips, self._standard_csv_file_name)

        print("Writing mega chips CSV...")
        Application.write_chips_to_csv(chips.mega_chips, self._mega_csv_file_name)

        print("Writing giga chips CSV...")
        Application.write_chips_to_csv(chips.giga_chips, self._giga_csv_file_name)

if __name__ == "__main__":
    Application().main(sys.argv[1:])
