require "json"
require "net/http"

$EL = "\e[2K"
$CHA = "\e[0G"
$RED = "\e[1;31m"
$GREEN = "\e[1;32m"
$YELLOW = "\e[1;33m"
$BLUE = "\e[1;34m"
$MAGENTA = "\e[1;35m"
$CYAN = "\e[1;36m"
$WHITE = "\e[1;37m"
$DEFAULT = "\e[1;39m"
$RESET = "\e[0m"

cards = {}
json_folder = "json"
json_file_in = "all_cards.json"
puts "Reading source JSON file (#{json_file_in})..."
File.open("#{json_folder}/#{json_file_in}") { |file|
  j = JSON.parse(file.read)["data"]
  j.each { |card|
    cards[card["id"]] = card
  }
}

json_file_out = "all_cards_fmt.json"
puts "Writing reformatted JSON file (#{json_file_out})..."
File.open("#{json_folder}/#{json_file_out}", "w") { |file|
  json = JSON.generate(cards, {
    array_nl: "\n",
    object_nl: "\n",
    indent: "  ",
    space: " ",
  })
  file.write "#{json}\n"
}

puts "Creating images folders..."
images_dir = "images"
if !Dir.exists? images_dir
  Dir.mkdir images_dir
end
small_images_dir = "images_small"
if !Dir.exists? small_images_dir
  Dir.mkdir small_images_dir
end

host = "storage.googleapis.com"
images_api = "/ygoprodeck.com/pics"
small_images_api = "/ygoprodeck.com/pics_small"
counter = 0
num_cards = cards.length
puts "Getting images for each card..."
begin
  cards.keys.sort.each { |key|
    card = cards[key]
    card["card_images"].each { |image|
      id = image["id"]
      
      file_name_a = "#{images_dir}/#{id}.jpg"
      file_a_exists = File.exists? file_name_a
      
      file_name_b = "#{small_images_dir}/#{id}.jpg"
      file_b_exists = File.exists? file_name_b
      
      id_str = id.to_s.rjust 9
      count_str = counter.to_s.rjust 5
      percent_str = (counter.to_f / num_cards.to_f * 100.0).round(2).to_s.rjust(6)
      
      print "#{$EL}#{$CHA}"
      print "[#{$RED}#{id_str}#{$RESET}] "
      print "[#{$CYAN}#{count_str}#{$RESET}/#{$CYAN}#{num_cards}#{$RESET}] "
      print "[#{$YELLOW}#{percent_str}%#{$RESET}] "
      
      if !file_a_exists
        response_a = Net::HTTP.get(host, "#{images_api}/#{id}.jpg")
        File.open(file_name_a, "wb") { |file|
          file.write response_a
        }
        print "NORMAL:#{$MAGENTA}new#{$RESET}  "
      else
        print "NORMAL:#{$GREEN}skip#{$RESET} "
      end
    
      if !file_b_exists
        response_b = Net::HTTP.get(host, "#{small_images_api}/#{id}.jpg")
        File.open(file_name_b, "wb") { |file|
          file.write response_b
        }
        print "SMALL:#{$MAGENTA}new#{$RESET}  "
      else
        print "SMALL:#{$GREEN}skip#{$RESET} "
      end
    
      sleep 0.1
    }
    counter += 1
  }
rescue Interrupt
  puts "\nStopped by user action."
  exit
end

print "#{$EL}#{$CHA}"
print "[#{$RED}=========#{$RESET}] "
print "[#{$CYAN}#{num_cards}#{$RESET}/#{$CYAN}#{num_cards}#{$RESET}] "
print "[#{$YELLOW}100.00%#{$RESET}] "
puts "#{$GREEN}Done#{$RESET}"
