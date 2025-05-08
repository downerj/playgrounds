#!/usr/bin/env ocaml
#load "graphics.cma"
#load "unix.cma"

open Graphics
open Printf
open Sys
open Unix

let display: string = getenv "DISPLAY"
let width: int = 300
let height: int = 300 

let (<|) x y = y |> x

let init_window () : unit =
    sprintf "%s %dx%d" display width height
    |> open_graph;
    set_window_title "Rainbow in OCaml";
    auto_synchronize false

let force_window_size () : unit =
    match (size_x (), size_y ()) with
    | (w, h) when w = width && h = height -> ()
    | _ -> resize_window width height

let clear_window () : unit =
    set_color black;
    fill_rect 0 0 (size_x ()) (size_y ())

let value_to_rgb (value: int) : int =
    let n: int = value mod 0x100 in
    match value mod 0x600 with
    | v when v < 0x100 -> 0xff0000 lor (n lsl 8)
    | v when v < 0x200 -> 0xffff00 lxor (n lsl 16)
    | v when v < 0x300 -> 0x00ff00 lor (n lsl 0)
    | v when v < 0x400 -> 0x00ffff lxor (n lsl 8)
    | v when v < 0x500 -> 0x0000ff lor (n lsl 16)
    | v when v < 0x600 -> 0xff00ff lxor (n lsl 0)
    | v -> 0x000000

let draw_lines (offset: int) : unit =
    let rec loop (counter: int) : unit =
        match counter with
        | c when c < (max width height) * 2 ->
            value_to_rgb (c + offset) |> set_color;
            moveto 0 c;
            lineto c 0;
            loop (c + 1)
        | _ -> ()
    in
    loop 0

let tick_loop () : unit =
    let rec loop (tick: int): unit =
        force_window_size ();
        clear_graph ();
        draw_lines tick;
        synchronize ();
        Unix.sleepf 0.005;
        loop (tick + 1)
    in
    loop 0

let main () : unit =
    try
        init_window ();
        clear_window ();
        tick_loop ()
    with
    | Graphic_failure ("fatal I/O error") -> ()
;;

if !Sys.interactive then () else main ()