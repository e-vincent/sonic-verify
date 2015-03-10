require 'parser/current'
require_relative './../builder'

path = "assets/sp/"
filename = path + "nested_loop.txt"
#filename = path + "simple_sequence.txt"
#filename = path + "simple_chord.txt"
#filename = path + "simple_loop.txt"

file = File.open(filename, "rb")
contents = file.read

parser = Parser::CurrentRuby.new
parser.diagnostics.consumer = lambda do |diag|
  puts diag.render
end

buffer = Parser::Source::Buffer.new(filename)
buffer.source = contents
p = parser.parse(buffer)

#p p
builder = Builder.new
builder.entry(5)

file.close