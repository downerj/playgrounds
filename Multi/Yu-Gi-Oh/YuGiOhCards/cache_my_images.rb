#!/usr/bin/env ruby

require "json"
require "fileutils"

my_cards = nil
source_folder = "json"
source_file_name = "#{source_folder}/my_cards.json"
File.open(source_file_name) { |file|
  my_cards = JSON.parse(file.read)
}

images_folder = "images"
cache_folder = "my_images_cache"
if !File.directory?(cache_folder) then
  FileUtils.mkdir(cache_folder)
end

my_cards.keys.each { |id|
  chomped_id = id.gsub(/^0+/, '')
  puts id
  src_path = "#{images_folder}/#{chomped_id}.jpg"
  dest_path = "#{cache_folder}/#{id}.jpg"
  FileUtils.cp(src_path, dest_path)
}
