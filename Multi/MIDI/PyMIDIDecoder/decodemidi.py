#!/usr/bin/env python3
# Python 3.9+

from enum import Enum
from io import BufferedReader
import sys
from typing import Dict, List, Tuple


EVENT_NOTE_OFF = 0x80
EVENT_NOTE_ON = 0x90
EVENT_POLYPHONIC_KEY_PRESSURE = 0xA0
EVENT_CONTROL_CHANGE = 0xB0
EVENT_PROGRAM_CHANGE = 0xC0
EVENT_CHANNEL_PRESSURE = 0xD0
EVENT_PITCH_WHEEL_CHANGE = 0xE0

EVENT_SYSTEM_EXCLUSIVE = 0xF0
EVENT_SONG_POSITION_POINTER = 0xF2
EVENT_SONG_SELECT = 0xF3
EVENT_TUNE_REQUEST = 0xF6
EVENT_END_OF_EXCLUSIVE = 0xF7
EVENT_TIMING_CLOCK = 0xF8
EVENT_START = 0xFA
EVENT_CONTINUE = 0xFB
EVENT_STOP = 0xFC
EVENT_ACTIVE_SENSING = 0xFE
EVENT_META = 0xFF
EVENT_RESET = EVENT_META

META_SEQUENCE_NUMBER = 0x00
META_TEXT = 0x01
META_COPYRIGHT_NOTICE = 0x02
META_SEQUENCE_NAME = 0x03
META_INSTRUMENT_NAME = 0x04
META_LYRIC = 0x05
META_MARKER = 0x06
META_CUE_POINT = 0x07
META_CHANNEL_PREFIX = 0x20
META_END_OF_TRACK = 0x2F
META_SET_TEMPO = 0x51
META_SMPTE_OFFSET = 0x54
META_TIME_SIGNATURE = 0x58
META_KEY_SIGNATURE = 0x59
META_SEQUENCER_SPECIFIC = 0x7F

CHANNEL_DRUMS = 9

instruments: List[str] = [
    "Acoustic Grand Piano",
    "Bright Acoustic Piano",
    "Electric Grand Piano",
    "Honky-tonk Piano",
    "Electric Piano 1 (Rhodes Piano)",
    "Electric Piano 2 (Chorused Piano)",
    "Harpsichord",
    "Clavinet",
    "Celesta",
    "Glockenspiel",
    "Music Box",
    "Vibraphone",
    "Marimba",
    "Xylophone",
    "Tubular Bells",
    "Dulcimer (Santur)",
    "Drawbar Organ (Hammond)",
    "Percussive Organ",
    "Rock Organ",
    "Church Organ",
    "Reed Organ",
    "Accordion (French)",
    "Harmonica",
    "Tango Accordion (Band neon)",
    "Acoustic Guitar (nylon)",
    "Acoustic Guitar (steel)",
    "Electric Guitar (jazz)",
    "Electric Guitar (clean)",
    "Electric Guitar (muted)",
    "Overdriven Guitar",
    "Distortion Guitar",
    "Guitar harmonics",
    "Acoustic Bass",
    "Electric Bass (fingered)",
    "Electric Bass (picked)",
    "Fretless Bass",
    "Slap Bass 1",
    "Slap Bass 2",
    "Synth Bass 1",
    "Synth Bass 2",
    "Violin",
    "Viola",
    "Cello",
    "Contrabass",
    "Tremolo Strings",
    "Pizzicato Strings",
    "Orchestral Harp",
    "Timpani",
    "String Ensemble 1 (strings)",
    "String Ensemble 2 (slow strings)",
    "SynthStrings 1",
    "SynthStrings 2",
    "Choir Aahs",
    "Voice Oohs",
    "Synth Voice",
    "Orchestra Hit",
    "Trumpet",
    "Trombone",
    "Tuba",
    "Muted Trumpet",
    "French Horn",
    "Brass Section",
    "SynthBrass 1",
    "SynthBrass 2",
    "Soprano Sax",
    "Alto Sax",
    "Tenor Sax",
    "Baritone Sax",
    "Oboe",
    "English Horn",
    "Bassoon",
    "Clarinet",
    "Piccolo",
    "Flute",
    "Recorder",
    "Pan Flute",
    "Blown Bottle",
    "Shakuhachi",
    "Whistle",
    "Ocarina",
    "Lead 1 (square wave)",
    "Lead 2 (sawtooth wave)",
    "Lead 3 (calliope)",
    "Lead 4 (chiffer)",
    "Lead 5 (charang)",
    "Lead 6 (voice solo)",
    "Lead 7 (fifths)",
    "Lead 8 (bass + lead)",
    "Pad 1 (new age Fantasia)",
    "Pad 2 (warm)",
    "Pad 3 (polysynth)",
    "Pad 4 (choir space voice)",
    "Pad 5 (bowed glass)",
    "Pad 6 (metallic pro)",
    "Pad 7 (halo)",
    "Pad 8 (sweep)",
    "FX 1 (rain)",
    "FX 2 (soundtrack)",
    "FX 3 (crystal)",
    "FX 4 (atmosphere)",
    "FX 5 (brightness)",
    "FX 6 (goblins)",
    "FX 7 (echoes, drops)",
    "FX 8 (sci-fi, star theme)",
    "Sitar",
    "Banjo",
    "Shamisen",
    "Koto",
    "Kalimba",
    "Bag pipe",
    "Fiddle",
    "Shanai",
    "Tinkle Bell",
    "Agogo",
    "Steel Drums",
    "Woodblock",
    "Taiko Drum",
    "Melodic Tom",
    "Synth Drum",
    "Reverse Cymbal",
    "Guitar Fret Noise",
    "Breath Noise",
    "Seashore",
    "Bird Tweet",
    "Telephone Ring",
    "Helicopter",
    "Applause",
    "Gunshot",
]

drum_kit: Dict[str, str] = {
    "B1": "Acoustic Bass Drum",
    "C2": "Bass Drum 1",
    "C#2": "Side Stick",
    "D2": "Acoustic Snare",
    "D#2": "Hand Clap",
    "E2": "Electric Snare",
    "F2": "Low Floor Tom",
    "F#2": "Closed Hi Hat",
    "G2": "High Floor Tom",
    "G#2": "Pedal Hi-Hat",
    "A2": "Low Tom",
    "A#2": "Open Hi-Hat",
    "B2": "Low-Mid Tom",
    "C3": "Hi Mid Tom",
    "C#3": "Crash Cymbal 1",
    "D3": "High Tom",
    "D#3": "Ride Cymbal 1",
    "E3": "Chinese Cymbal",
    "F3": "Ride Bell",
    "F#3": "Tambourine",
    "G3": "Splash Cymbal",
    "G#3": "Cowbell",
    "A3": "Crash Cymbal 2",
    "A#3": "Vibraslap",
    "B3": "Ride Cymbal 2",
    "C4": "Hi Bongo",
    "C#4": "Low Bongo",
    "D4": "Mute Hi Conga",
    "D#4": "Open Hi Conga",
    "E4": "Low Conga",
    "F4": "High Timbale",
    "F#4": "Low Timbale",
    "G4": "High Agogo",
    "G#4": "Low Agogo",
    "A4": "Cabasa",
    "A#4": "Maracas",
    "B4": "Short Whistle",
    "C5": "Long Whistle",
    "C#5": "Short Guiro",
    "D5": "Long Guiro",
    "D#5": "Claves",
    "E5": "Hi Wood Block",
    "F5": "Low Wood Block",
    "F#5": "Mute Cuica",
    "G5": "Open Cuica",
    "G#5": "Mute Triangle",
    "A5": "Open Triangle",
}


def vlq_to_int(vlq: bytes) -> int:
    accumulator: int = 0
    for b in vlq:
        accumulator = (accumulator << 7) | (b & 0x7f)
    return accumulator


def read_vlq_to_int(file: BufferedReader) -> Tuple[int, int]:
    accumulator: int = 0
    counter: int = 0
    datum: int
    while (datum := file.read(1)[0]) >= 0x80:
        accumulator = (accumulator << 7) | (datum & 127)
        counter += 1
    # Convert the last byte since it broke the loop.
    accumulator = (accumulator << 7) | (datum & 127)
    counter += 1
    return (accumulator, counter)


def parse_key_signature(sharps_flats: int, is_minor: int) -> str:
    if is_minor == 0:
        if sharps_flats == -7:
            return "Cb_maj"
        if sharps_flats == -6:
            return "Gb_maj"
        if sharps_flats == -5:
            return "Db_maj"
        if sharps_flats == -4:
            return "Ab_maj"
        if sharps_flats == -3:
            return "Eb_maj"
        if sharps_flats == -2:
            return "Bb_maj"
        if sharps_flats == -1:
            return "F_maj"
        if sharps_flats == 0:
            return "C_maj"
        if sharps_flats == 1:
            return "G_maj"
        if sharps_flats == 2:
            return "D_maj"
        if sharps_flats == 3:
            return "A_maj"
        if sharps_flats == 4:
            return "E_maj"
        if sharps_flats == 5:
            return "B_maj"
        if sharps_flats == 6:
            return "F#_maj"
        if sharps_flats == 7:
            return "C#_maj"

        raise Exception(f'Invalid sharps/flats value "{sharps_flats}"')

    if is_minor == 1:
        if sharps_flats == -7:
            return "Ab_min"
        if sharps_flats == -6:
            return "Eb_min"
        if sharps_flats == -5:
            return "Bb_min"
        if sharps_flats == -4:
            return "F_min"
        if sharps_flats == -3:
            return "C_min"
        if sharps_flats == -2:
            return "G_min"
        if sharps_flats == -1:
            return "D_min"
        if sharps_flats == 0:
            return "A_min"
        if sharps_flats == 1:
            return "E_min"
        if sharps_flats == 2:
            return "B_min"
        if sharps_flats == 3:
            return "F#_min"
        if sharps_flats == 4:
            return "C#_min"
        if sharps_flats == 5:
            return "G#_min"
        if sharps_flats == 6:
            return "D#_min"
        if sharps_flats == 7:
            return "A#_min"

        raise Exception(f'Invalid sharps/flats value "{sharps_flats}"')

    raise Exception(f'Invalid key signature mi value "{is_minor}"')


def byte_to_note(value: int) -> str:
    names: List[str] = [
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B",
    ]
    if value < 0 or value > 127:
        raise Exception(f'Invalid note value "{value}"')

    name: str = names[value % len(names)]
    octave: int = -1 + (value // len(names))

    return f"{name}{octave}"


def read_header_chunk(file: BufferedReader) -> int:
    id: bytes = file.read(4)
    if id != b"MThd":
        raise Exception(f'Invalid header chunk type "{id}"')
    print("Header", end=" ")

    chunk_length: int = int.from_bytes(file.read(4), "big")
    print(f"chunk_length={chunk_length}", end=" ")

    chunk_data: bytes = file.read(chunk_length)

    file_format: int = int.from_bytes(chunk_data[:2], "big")
    if file_format not in [0, 1, 2]:
        raise Exception(f'Invalid MIDI format "{file_format}"')
    print(f"format={file_format}", end=" ")

    track_count: int = int.from_bytes(chunk_data[2:4], "big")
    print(f"track_count={track_count}", end=" ")

    tick_division: int = int.from_bytes(chunk_data[4:6], "big")
    print(f"tick_division={tick_division}")

    return 8 + chunk_length


def read_event(file: BufferedReader) -> int:
    delta_time, read_counter = read_vlq_to_int(file)

    event_type: int = file.read(1)[0]
    read_counter += 1
    if event_type == EVENT_META:
        meta_event_type: int = file.read(1)[0]
        read_counter += 1
        (event_length, d_counter) = read_vlq_to_int(file)
        read_counter += d_counter
        event_data: bytes = file.read(event_length)
        read_counter += event_length

        if meta_event_type == META_SEQUENCE_NUMBER:
            sequence_number: int = int.from_bytes(event_data, "big")
            print(f"Sequence_Number dt={delta_time} number={sequence_number}")
        elif meta_event_type == META_TEXT:
            text: str = event_data.decode("latin_1")
            print(f'Text dt={delta_time} text="{text}"')
        elif meta_event_type == META_COPYRIGHT_NOTICE:
            copyright: str = event_data.decode("latin_1")
            print(f'Copyright_Notice dt={delta_time} notice="{copyright}"')
        elif meta_event_type == META_SEQUENCE_NAME:
            name: str = event_data.decode("latin_1")
            print(f'Sequence_Name dt={delta_time} name="{name}"')
        elif meta_event_type == META_INSTRUMENT_NAME:
            instrument: str = event_data.decode("latin_1")
            print(f'Instrument_Name dt={delta_time} instrument="{instrument}"')
        elif meta_event_type == META_LYRIC:
            lyric: str = event_data.decode("latin_1")
            print(f'Lyric dt={delta_time} lyric="{lyric}"')
        elif meta_event_type == META_MARKER:
            marker: str = event_data.decode("latin_1")
            print(f'Marker dt={delta_time} marker="{marker}"')
        elif meta_event_type == META_CUE_POINT:
            cue_point: str = event_data.decode("latin_1")
            print(f'Cue_Point dt={delta_time} cue="{cue_point}"')
        elif meta_event_type == META_CHANNEL_PREFIX:
            prefix: int = int.from_bytes(event_data, "big")
            print(f"Channel_Prefix dt={delta_time} prefix={prefix}")
        elif meta_event_type == META_END_OF_TRACK:
            print(f"End_Of_Track dt={delta_time}")
        elif meta_event_type == META_SET_TEMPO:
            tempo: int = int.from_bytes(event_data, "big")
            print(f"Set_Tempo dt={delta_time} tempo={tempo}")
        elif meta_event_type == META_SMPTE_OFFSET:
            hr: int = event_data[0]
            mn: int = event_data[1]
            se: int = event_data[2]
            fr: int = event_data[3]
            ff: int = event_data[4]
            print(f"SMPTE_Offset dt={delta_time} hr={hr} mn={mn} se={se} fr={fr} ff={ff}")
        elif meta_event_type == META_TIME_SIGNATURE:
            numerator: int = event_data[0]
            denominator: int = int(2 ** event_data[1])
            clocks_per_click: int = event_data[2]
            beats_per_quarter: int = event_data[3]
            print(f"Time_Signature dt={delta_time} numerator={numerator} denominator={denominator} clocks_per_click={clocks_per_click} beats_per_quarter={beats_per_quarter}")
        elif meta_event_type == META_KEY_SIGNATURE:
            sharps_flats: int = event_data[0]
            is_minor: int = event_data[1]
            key_signature: str = parse_key_signature(sharps_flats, is_minor)
            print(f"Key_Signature dt={delta_time} key={key_signature}")
        elif meta_event_type == META_SEQUENCER_SPECIFIC:
            data_string: str = " ".join(f"{b:-02X}" for b in event_data)
            print(f"Sequencer_Specific dt={delta_time} data=[{data_string}]")
        else:
            data_string: str = " ".join(f"{b:-02X}h" for b in event_data)
            print(f"{event_type:-02X}h {meta_event_type:-02X}h dt={delta_time:X}h {event_length:-02X}h {data_string}")
    elif event_type == EVENT_SYSTEM_EXCLUSIVE:
        print(f"System_Exclusive dt={delta_time}", end=" ")
        datum: int
        while (datum := file.read(1)[0]) != 0xF7:
            read_counter += 1
            print(f"{datum:-02X}", end=" ")
        # Print the last 0xF7 since it broke the loop.
        print(f"{datum:-02X}")

        # Include a byte for the final F7.
        read_counter += 1
    elif event_type == EVENT_SONG_POSITION_POINTER:
        pointer: int = int.from_bytes(file.read(2), "little")
        print(f"Song_Position_Pointer dt={delta_time} position={pointer}")
        read_counter += 2
    elif event_type == EVENT_SONG_SELECT:
        song: int = file.read(1)[0]
        print(f"Song_Select dt={delta_time} song={song}")
        read_counter += 1
    elif event_type == EVENT_TUNE_REQUEST:
        print(f"Tune_Request dt={delta_time}")
    elif event_type == EVENT_END_OF_EXCLUSIVE:
        print(f"End_Of_Exclusive dt={delta_time}")
    elif event_type == EVENT_TIMING_CLOCK:
        print(f"Timing_Clock dt={delta_time}")
    elif event_type == EVENT_START:
        print(f"Start dt={delta_time}")
    elif event_type == EVENT_CONTINUE:
        print(f"Continue dt={delta_time}")
    elif event_type == EVENT_STOP:
        print(f"Stop dt={delta_time}")
    elif event_type == EVENT_ACTIVE_SENSING:
        print(f"Active_Sensing dt={delta_time}")
    else:
        # Check for common MIDI messages/events by separating the
        # first and second nibbles.
        event_type_a: int = event_type & 0xf0
        channel: int = event_type & 0x0f
        if event_type_a in [EVENT_NOTE_OFF, EVENT_NOTE_ON, EVENT_POLYPHONIC_KEY_PRESSURE]:
            note: str = byte_to_note(file.read(1)[0])
            if channel == CHANNEL_DRUMS and note in drum_kit:
                note = f'"{drum_kit[note]}"'
            velocity: int = file.read(1)[0]
            read_counter += 2
            if event_type_a == EVENT_NOTE_OFF:
                print(f"Note_Off dt={delta_time} channel={channel} note={note} velocity={velocity}")
            elif event_type_a == EVENT_NOTE_ON:
                print(f"Note_On dt={delta_time} channel={channel} note={note} velocity={velocity}")
            # event_type_a == EVENT_POLYPHONIC_KEY_PRESSURE
            else:
                print(f"Key_Pressure dt={delta_time} channel={channel} note={note} velocity={velocity}")
        elif event_type_a == EVENT_CONTROL_CHANGE:
            controller: int = file.read(1)[0]
            value: int = file.read(1)[0]
            print(f"Control_Change dt={delta_time} channel={channel} controller={controller} value={value}")
            read_counter += 2
        elif event_type_a == EVENT_PROGRAM_CHANGE:
            program: str = instruments[file.read(1)[0]]
            if channel == CHANNEL_DRUMS:
                program = "N/A (Drums)"
            print(f'Program_Change dt={delta_time} channel={channel} program="{program}"')
            read_counter += 1
        elif event_type_a == EVENT_CHANNEL_PRESSURE:
            pressure: int = file.read(1)[0]
            print(f"Channel_Pressure dt={delta_time} channel={channel} pressure={pressure}")
            read_counter += 1
        elif event_type_a == EVENT_PITCH_WHEEL_CHANGE:
            pitch: int = int.from_bytes(file.read(2), "little")
            print(f"Pitch_Wheel_Change dt={delta_time} channel={channel} pitch={pitch}")
            read_counter += 2
        else:
            raise Exception(f'Unknown MIDI event @ dt={delta_time}: "{event_type:-02x}"')

    return read_counter


def read_track_chunk(file: BufferedReader) -> int:
    id: bytes = file.read(4)
    if id != b"MTrk":
        raise Exception(f'Invalid track chunk type "{id}"')
    print("Track", end=" ")

    chunk_length: int = int.from_bytes(file.read(4), "big")
    print(f"chunk_length={chunk_length}")

    read_counter: int = 0
    while read_counter < chunk_length:
        read_counter += read_event(file)

    return 8 + chunk_length


def main(file_name_in: str) -> None:
    with open(file_name_in, "rb") as file:
        read_header_chunk(file)
        while len(file.peek()) > 0:
            read_track_chunk(file)
    print()


if __name__ == "__main__":
    file_name_in = sys.argv[1]
    main(file_name_in)
