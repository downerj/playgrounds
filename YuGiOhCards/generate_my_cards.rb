require "json"

cards_dir = "my_cards"
in_file_names = [
  "extras-fusion.txt",
  "extras-link.txt",
  "extras-ritual.txt",
  "extras-synchro.txt",
  "extras-xyz.txt",
  "monsters-effect.txt",
  "monsters-normal.txt",
  "others.txt",
  "spells.txt",
  "traps.txt",
]
my_card_ids = {}

counter = 0
in_file_names.each { |file_name|
  contents = nil
  File.open("#{cards_dir}/#{file_name}") { |file|
    contents = file.read
  }
  contents.split("\n").each { |line|
    line = line.strip
    next if line.length == 0

    parts = line.split(" ")
    id = parts[0]
    count = 1
    if parts.length > 1
      count = parts[1].to_i
    end
    my_card_ids[id] = count
    counter += count
  }
}
my_card_ids = my_card_ids.keys.sort.map { |k|
  [k, my_card_ids[k]]
}.to_h

print "Parsed #{my_card_ids.keys.length} IDs (#{counter} total cards)\n"

json = JSON.generate(my_card_ids, {
  array_nl: "\n",
  object_nl: "\n",
  indent: "  ",
  space: " ",
})

out_file_name_js = "my_cards.js"
File.open(out_file_name_js, "w") { |file|
  file.write("const my_cards = #{json};\n")
}

out_file_name_json = "my_cards.json"
File.open(out_file_name_json, "w") { |file|
  file.write("#{json}\n")
}
